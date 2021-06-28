#!/usr/bin/env python

import rospy 
import roslib

from std_msgs.msg import Int16
from std_msgs.msg import Int16MultiArray

class MotorCommands():

	def __init__(self):
		rospy.init_node('motor_commands')
		self.nodename = rospy.get_name()
		#rospy.loginfo("%s started" % self.nodename)
		
		self.rmotor_cmd = 0
		self.lmotor_cmd = 0
		self.bmotor_cmd = 0
		self.cmds = Int16MultiArray()
		self.cmds.data = []
		
		
		# Subscribers
		rospy.Subscriber("rmotor_cmd", Int16, self.rmotor_callback)
		rospy.Subscriber("lmotor_cmd", Int16, self.lmotor_callback)
		rospy.Subscriber("bmotor_cmd", Int16, self.bmotor_callback)
		
		# Publisher
		self.pub_cmds = rospy.Publisher("motor_cmds", Int16MultiArray, queue_size=10)
		
	
	def rmotor_callback(self, rcmd):
		self.rmotor_cmd = rcmd.data
	
	def lmotor_callback(self, lcmd):
		self.lmotor_cmd = lcmd.data
	
	def bmotor_callback(self, bcmd):
		self.bmotor_cmd = bcmd.data
		
		#rospy.loginfo("%s, %s, %s",self.rmotor_cmd, self.lmotor_cmd, self.bmotor_cmd)
		
		self.cmds.data = [self.rmotor_cmd, self.lmotor_cmd, self.bmotor_cmd]
		self.pub_cmds.publish(self.cmds)
		
	def send_commands(self):
		#rospy.loginfo("%s, %s, %s",self.rmotor_cmd, self.lmotor_cmd, self.bmotor_cmd)
		
		self.cmds.data = [self.rmotor_cmd, self.lmotor_cmd, self.bmotor_cmd]
		
		self.pub_cmds.publish(self.cmds)
		

if __name__ == "__main__":

	#r = rospy.Rate(100)

	while not rospy.is_shutdown():

		cmd = MotorCommands() 
		cmd.send_commands()
		rospy.sleep(0.1)

	
		
		
