#include "Bumper.h"
#include "IRsensor.h"
#include "Motors_V3.h"
#include "Encoder_V1.h"

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

void rcmdVelCB(const std_msgs::Int16& tspeed) { 
  Motors::rMotor(tspeed.data);
}
void lcmdVelCB(const std_msgs::Int16& tspeed) {
  Motors::lMotor(tspeed.data);
}
void bcmdVelCB(const std_msgs::Int16& tspeed) { 
  Motors::bMotor(tspeed.data);
}

// defining publishers and subscribers
ros::Publisher rwheel_encoder("rwheel_encoder",&rwheel_int);
ros::Publisher lwheel_encoder("lwheel_encoder",&lwheel_int);
ros::Publisher bwheel_encoder("bwheel_encoder",&bwheel_int);
ros::Publisher ir_sensors("ir_sensors",&ir_sensor_array);

ros::Subscriber<std_msgs::Int16> rmotor_cmd("rmotor_cmd", &rcmdVelCB);
ros::Subscriber<std_msgs::Int16> lmotor_cmd("lmotor_cmd", &lcmdVelCB);
ros::Subscriber<std_msgs::Int16> bmotor_cmd("bmotor_cmd", &bcmdVelCB);

void setup() {
  
  // Set baudrate
  nh.getHardware()->setBaud(115200);
  // Initialise ros node
  nh.initNode();
  Encoder::initEncoder();
   // Initialise sensors and motors
  IRsensor::initSensors();
  Motors::initMotors();

  nh.advertise(rwheel_encoder);
  nh.advertise(lwheel_encoder);
  nh.advertise(bwheel_encoder);
  nh.advertise(ir_sensors);

  // Subscribe to motor commands
  nh.subscribe(rmotor_cmd);  // right motor
  nh.subscribe(lmotor_cmd);  // left motor
  nh.subscribe(bmotor_cmd);  // back motor
}

void loop() {
  IRsensor::updateState();
  Encoder::updateState(); 
  Motors::updateState();
  Serial.println(Encoder::get_motors_pulse_r() );
 
  lwheel_int.data = Encoder::get_motors_pulse_l(); // Left Wheel Encoder Data
  lwheel_encoder.publish(&lwheel_int);
  bwheel_int.data = Encoder::get_motors_pulse_b(); // Back Wheel Encoder Data
  bwheel_encoder.publish(&bwheel_int);
  rwheel_int.data = Encoder::get_motors_pulse_r(); // Right Wheel Encoder Data
  rwheel_encoder.publish(&rwheel_int);

  ir_sensor_array.data = IRsensor::distances;
  ir_sensor_array.data_length = 9;
  ir_sensors.publish(&ir_sensor_array); // Publish IR sensor data
 
  nh.spinOnce();
  delay(30);
}
