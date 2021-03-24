#!/usr/bin/env python
import rospy
#import roslib
#roslib.load_manifest('differential_drive')
from math import sin, cos, pi

from geometry_msgs.msg import Quaternion
from geometry_msgs.msg import Twist
from nav_msgs.msg import Odometry
from tf.broadcaster import TransformBroadcaster
from std_msgs.msg import Int16, Int64 , Int32
from sensor_msgs.msg import Imu
from tf.transformations import euler_from_quaternion,quaternion_from_euler


class DiffTf:
    def __init__(self):
        rospy.init_node("diff_tf")
        self.nodename = rospy.get_name()
        rospy.loginfo("-I- %s started" % self.nodename)
        self.rate = rospy.get_param('~rate',2)  # the rate at which to publish the transform
        self.ticks_meter = float(rospy.get_param('ticks_meter', 3185))  # The number of wheel encoder ticks per meter of travel
        self.base_width = float(rospy.get_param('~base_width', 0.34)) # The wheel base width in meters
        
        self.base_frame_id = rospy.get_param('~base_frame_id','base_footprint') # the name of the base frame of the robot
        self.odom_frame_id = rospy.get_param('~odom_frame_id', 'odom') # the name of the odometry reference frame
        
        self.encoder_min = rospy.get_param('encoder_min', -32768)
        self.encoder_max = rospy.get_param('encoder_max', 32768)
        self.encoder_low_wrap = rospy.get_param('wheel_low_wrap', (self.encoder_max - self.encoder_min) * 0.3 + self.encoder_min )
        self.encoder_high_wrap = rospy.get_param('wheel_high_wrap', (self.encoder_max - self.encoder_min) * 0.7 + self.encoder_min )
 
        self.t_delta = rospy.Duration(1.0/self.rate)
        self.t_next = rospy.Time.now() + self.t_delta
        
        # internal data
        self.enc_left = None        # wheel encoder readings
        self.enc_right = None
        self.left = 0               # actual values coming back from robot
        self.right = 0
        self.lmult = 0
        self.rmult = 0
        self.prev_lencoder = 0
        self.prev_rencoder = 0
        self.x = 0                  # position in xy plane 
        self.y = 0
        self.th = 0
        self.dx = 0                 # speeds in x/rotation
        self.dr = 0
        self.then = rospy.Time.now()
        
        # subscriptions
        rospy.Subscriber("imu", Imu, self.imuCallback)
        rospy.Subscriber("lwheel_encoder", Int16, self.lwheelCallback)
        rospy.Subscriber("rwheel_encoder", Int16, self.rwheelCallback)
        self.odomPub = rospy.Publisher("odom", Odometry,queue_size=10)
        self.odomBroadcaster = TransformBroadcaster()
    def spin(self):
        r = rospy.Rate(self.rate)
        while not rospy.is_shutdown():
            self.update()
            r.sleep()
    def update(self):
        now = rospy.Time.now()
        if now > self.t_next:
            elapsed = now - self.then
            self.then = now
            elapsed = elapsed.to_sec()
            

            # calculate odometry
            if self.enc_left == None: ##################Why not check both#################################################################???????????????
                d_left = 0             #######Initialise at Zero########
                d_right = 0
            else:
                d_left = (self.left - self.enc_left) / self.ticks_meter
                d_right = (self.right - self.enc_right) / self.ticks_meter
                #print d_left, d_right ################
            self.enc_left = self.left
            self.enc_right = self.right
           
            # distance traveled is the average of the two wheels 
            d = ( d_left + d_right ) / 2
            # this approximation works (in radians) for small angles
            th = ( d_right - d_left ) / self.base_width      ############approximation#############
            # calculate velocities
            self.dx = d / elapsed
            self.dr = th / elapsed

            #print "----------------------------------"
            #print "Now :", now
            # "T_next", self.t_next
            #print "Condition :", now > self.t_next
            #print "Elapsed :", elapsed
            #print "Distance :", d
            #print self.enc_left
            #print "Yaw :", th
            #print "Linear Velocity :", self.dx
            #print "Angular Velocity :", self.dr

             
            if (d != 0):
                # calculate distance traveled in x and y
                x = cos( th ) * d  
                y = -sin( th ) * d         ##########sign###############
                # calculate the final position of the robot
                self.x = self.x + ( cos( self.th ) * x - sin( self.th ) * y )
                self.y = self.y + ( sin( self.th ) * x + cos( self.th ) * y )
                
                #print self.x , "=============", self.y
            if( th != 0):
                self.th = self.th + th
                #print self.th
            # publish the odom information
            quaternion = Quaternion()
            quaternion.x = 0.0
            quaternion.y = 0.0
            quaternion.z = sin( self.th / 2 ) #########change this jugaad ########
            quaternion.w = cos( self.th / 2 )
            self.odomBroadcaster.sendTransform(
                (self.x, self.y, 0),
                (quaternion.x, quaternion.y, quaternion.z, quaternion.w),
                rospy.Time.now(),
                self.base_frame_id,
                self.odom_frame_id
                )
            
            odom = Odometry()
            odom.header.stamp = now
            odom.header.frame_id = self.odom_frame_id
            odom.pose.pose.position.x = self.x                         # Swapped again from y to x
            odom.pose.pose.position.y = self.y
            odom.pose.pose.position.z = 0
            odom.pose.pose.orientation = quaternion
            odom.child_frame_id = self.base_frame_id
            odom.twist.twist.linear.x = self.dx                          # Swapped again from y to x
            odom.twist.twist.linear.y = 0                   
            odom.twist.twist.angular.z = self.dr
            self.odomPub.publish(odom)

    def lwheelCallback(self, msg):
        enc = msg.data
        if (enc < self.encoder_low_wrap and self.prev_lencoder > self.encoder_high_wrap):
            self.lmult = self.lmult + 1
            
        if (enc > self.encoder_high_wrap and self.prev_lencoder < self.encoder_low_wrap):
            self.lmult = self.lmult - 1
            
        self.left = 1.0 * (enc + self.lmult * (self.encoder_max - self.encoder_min)) 


        self.prev_lencoder = enc

    def rwheelCallback(self, msg):
        enc = msg.data
        if(enc < self.encoder_low_wrap and self.prev_rencoder > self.encoder_high_wrap):
            self.rmult = self.rmult + 1
        
        if(enc > self.encoder_high_wrap and self.prev_rencoder < self.encoder_low_wrap):
            self.rmult = self.rmult - 1
            
        self.right = 1.0 * (enc + self.rmult * (self.encoder_max - self.encoder_min))


        self.prev_rencoder = enc

    def imuCallback(self,msg):
        imu_read = msg
        self.orientation = [imu_read.orientation.x,imu_read.orientation.y,imu_read.orientation.z,imu_read.orientation.w]
        self.euler_angles = euler_from_quaternion(self.orientation)
        self.theta = self.euler_angles[2]


if __name__ == '__main__':
    """ main """
    diffTf = DiffTf()
    diffTf.spin()
