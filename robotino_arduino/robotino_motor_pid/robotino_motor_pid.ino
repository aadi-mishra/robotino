#include "Bumper.h"
#include "IRsensor.h"
#include "Motors.h"

#include <math.h>
#include <ros.h>
#include <ros/time.h>
#include <std_msgs/String.h>
#include <std_msgs/Int16.h>
#include <std_msgs/Int8.h>
#include <std_msgs/Float32.h>
#include <std_msgs/UInt8MultiArray.h>
#include <std_msgs/Int16MultiArray.h>
#include <geometry_msgs/Twist.h>
#include <PID_v1.h>

ros::NodeHandle nh;

std_msgs::Int16 rwheel_int;
std_msgs::Int16 lwheel_int;
std_msgs::Int16 bwheel_int;
std_msgs::Float32 right;
std_msgs::Float32 left;
std_msgs::Float32 back;
std_msgs::Float32 bumper_float;
std_msgs::UInt8MultiArray ir_sensor_array;

void rcmdVelCB(const std_msgs::Int16& tspeed) { 
  Motors::rMotor(tspeed.data);
  //Motors::rMotor(200);
}
void lcmdVelCB(const std_msgs::Int16& tspeed) {
  Motors::lMotor(tspeed.data);
  //Motors::lMotor(200);
}
void bcmdVelCB(const std_msgs::Int16& tspeed) { 
  Motors::bMotor(tspeed.data);
  //Motors::bMotor(200);
}



// defining publishers and subscribers
ros::Publisher rwheel_encoder("rwheel_encoder",&rwheel_int);
ros::Publisher lwheel_encoder("lwheel_encoder",&lwheel_int);
ros::Publisher bwheel_encoder("bwheel_encoder",&bwheel_int);

ros::Publisher bumper("bumper",&bumper_float);
ros::Publisher ir_sensors("ir_sensors",&ir_sensor_array);

ros::Subscriber<std_msgs::Int16> rmotor_cmd("rmotor_cmd", &rcmdVelCB);
ros::Subscriber<std_msgs::Int16> lmotor_cmd("lmotor_cmd", &lcmdVelCB);
ros::Subscriber<std_msgs::Int16> bmotor_cmd("bmotor_cmd", &bcmdVelCB);

void setup() {
  // Initialise sensors and motors
  IRsensor::initSensors();
  Bumper::initBumper();
  Motors::initMotors();

  // Set baudrate
  nh.getHardware()->setBaud(74880);
  // Initialise ros node
  nh.initNode();

  nh.advertise(rwheel_encoder);
  nh.advertise(lwheel_encoder);
  nh.advertise(bwheel_encoder);
  nh.advertise(bumper);
  nh.advertise(ir_sensors);

  // Subscribe to motor commands
  nh.subscribe(rmotor_cmd);  // right motor
  nh.subscribe(lmotor_cmd);  // left motor
  nh.subscribe(bmotor_cmd);  // back motor
  //nh.negotiateTopics();
  
}

void loop() {
  Bumper::updateState();
  IRsensor::updateState();
  Motors::updateState();

  // Right Wheel Encoder Data
  rwheel_int.data = Motors::get_motors_pulse_r();
  rwheel_encoder.publish(&rwheel_int);
  // Left Wheel Encoder Data
  lwheel_int.data = Motors::get_motors_pulse_l();
  lwheel_encoder.publish(&lwheel_int);
  // Back Wheel Encoder Data
  bwheel_int.data = Motors::get_motors_pulse_b();
  bwheel_encoder.publish(&bwheel_int);
  // Bumper Sensor Data
  bumper_float.data = Bumper::bump;
  bumper.publish(&bumper_float); // Publish Bumper sensor data
  // IR sensors Data
  ir_sensor_array.layout.dim = 
    (std_msgs::MultiArrayDimension *)malloc(sizeof(std_msgs::MultiArrayDimension));
  ir_sensor_array.layout.dim[0].label = "distance";
  ir_sensor_array.data = IRsensor::distances;
  ir_sensor_array.data_length = 9;
  ir_sensors.publish(&ir_sensor_array); // Publish IR sensor data
 
  nh.spinOnce();
  //delay(50);
}
