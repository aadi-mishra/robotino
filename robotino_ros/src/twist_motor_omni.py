#!/usr/bin/env python
import rospy
import roslib
import math
from std_msgs.msg import Float32,Int32, UInt8MultiArray, Bool, String
from geometry_msgs.msg import Twist 
from sensor_msgs.msg import Range
import numpy as np
from numpy import linalg as al

class TwistToMotors():
    def __init__(self):
        rospy.init_node("twist_to_motors")
        nodename = rospy.get_name()
        rospy.loginfo("%s started" % nodename)
        self.M_PI = math.pi
        self.motor_velocities = []
    	
    	# Create publishers that publishes target velocity to the PID controller
        self.pub_lmotor = rospy.Publisher('lwheel_vtarget', Float32,queue_size=10)
        self.pub_rmotor = rospy.Publisher('rwheel_vtarget', Float32,queue_size=10)
        self.pub_bmotor = rospy.Publisher('bwheel_vtarget', Float32,queue_size=10)
		
		# Subscribe to the velocity commands from teleop
        rospy.Subscriber('/robotino/cmd_vel', Twist, self.twistCallback, queue_size=10)
    	
        self.rate = rospy.get_param("~rate", 100)
        self.timeout_ticks = rospy.get_param("~timeout_ticks", 100)
        self.left = 0
        self.right = 0
        self.back = 0
        
    def spin(self):
        r = rospy.Rate(self.rate)
        idle = rospy.Rate(100)
        self.ticks_since_target = self.timeout_ticks

        while not rospy.is_shutdown():
        
            while not rospy.is_shutdown() and self.ticks_since_target < self.timeout_ticks:
                self.spinOnce()
                r.sleep()
            idle.sleep()
            
    def spinOnce(self):
  		# Calculating the individual motor velocity for a motion command
        angle_mat = np.array([[math.cos(30*(self.M_PI/180)), math.cos(150*(self.M_PI/180)), math.cos(90*(self.M_PI/180))], 
        						[-math.sin(30*(self.M_PI/180)), -math.sin(150*(self.M_PI/180)),math.sin(90*(self.M_PI/180))],
        						[1, 1, 1]])
        angle_mat_inv = al.inv(angle_mat)

        [v_r, v_l, v_b] = np.dot(angle_mat_inv, np.array([self.dx, self.dy, self.dr]))
        
        # Assigning the calculated velocities to each motors
        self.right = v_r
        self.left = v_l
        self.back = v_b
                    
        self.pub_lmotor.publish(self.left)
        self.pub_rmotor.publish(self.right)
        self.pub_bmotor.publish(self.back)
        self.ticks_since_target += 1

	# Callback function 
    def twistCallback(self,msg):
        self.ticks_since_target = 0
        self.dx = msg.linear.x
        self.dr = msg.angular.z
        self.dy = msg.linear.y
     
if __name__ == '__main__':
    """ main """
    twistToMotors = TwistToMotors()
    twistToMotors.spin()
