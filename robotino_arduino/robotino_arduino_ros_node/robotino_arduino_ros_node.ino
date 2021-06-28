#include "Bumper.h"
#include "IRsensor.h"
#include "Motors_V3.h"
#include "Encoder.h"

#include <math.h>
#include <ros.h>
#include <ros/time.h>
#include <std_msgs/String.h>
#include <std_msgs/Int16.h>
#include <std_msgs/Float32.h>
#include <std_msgs/UInt8MultiArray.h>
#include <std_msgs/Int16MultiArray.h>
#include <geometry_msgs/Twist.h>

ros::NodeHandle nh;

std_msgs::Int16 rwheel_int;
std_msgs::Int16 lwheel_int;
std_msgs::Int16 bwheel_int;
std_msgs::UInt8MultiArray ir_sensor_array;

void cmdVelCB(const std_msgs::Int16MultiArray& vspeed) { 
  Motors::rMotor(vspeed.data[0]);
  Motors::lMotor(vspeed.data[1]);
  Motors::bMotor(vspeed.data[2]);

}

// defining publishers and subscribers
ros::Publisher rwheel_encoder("rwheel_encoder",&rwheel_int);
ros::Publisher lwheel_encoder("lwheel_encoder",&lwheel_int);
ros::Publisher bwheel_encoder("bwheel_encoder",&bwheel_int);
ros::Publisher ir_sensors("ir_sensors",&ir_sensor_array);

ros::Subscriber<std_msgs::Int16MultiArray> cmd("motor_cmds", &cmdVelCB);

void setup() {
  // Initialise sensors and motors
  IRsensor::initSensors();
  Motors::initMotors();

  // Set baudrate
  nh.getHardware()->setBaud(57600);
  // Initialise ros node
  nh.initNode();
  Encoder::initEncoder();
  
  nh.advertise(rwheel_encoder);
  nh.advertise(lwheel_encoder);
  nh.advertise(bwheel_encoder);
  nh.advertise(ir_sensors);

  // Subscribe to motor commands
  nh.subscribe(cmd);
    
}

void loop() {
  IRsensor::updateState();
  Motors::updateState();
  Encoder::updateState();
  
  // Encoder Data 
  rwheel_int.data = Encoder::get_motors_pulse_r(); // Right Wheel Encoder Data
  rwheel_encoder.publish(&rwheel_int);
  lwheel_int.data = Encoder::get_motors_pulse_l(); // Left Wheel Encoder Data
  lwheel_encoder.publish(&lwheel_int);
  bwheel_int.data = Encoder::get_motors_pulse_b(); // Back Wheel Encoder Data
  bwheel_encoder.publish(&bwheel_int);

  // IR sensors Data
  ir_sensor_array.data = IRsensor::distances;
  ir_sensor_array.data_length = 9;
  ir_sensors.publish(&ir_sensor_array); // Publish IR sensor data
 
  nh.spinOnce();
  delay(50);
}
