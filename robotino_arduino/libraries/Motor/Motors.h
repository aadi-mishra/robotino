#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include <utility/Adafruit_MS_PWMServoDriver.h>
#include <math.h>
#include <MatrixMath.h>
#include <BasicLinearAlgebra.h>

using namespace BLA;

namespace Motors {

  Adafruit_MotorShield AFMS = Adafruit_MotorShield();
  Adafruit_DCMotor *leftMotor = AFMS.getMotor(1);
  Adafruit_DCMotor *backMotor = AFMS.getMotor(2);
  Adafruit_DCMotor *rightMotor = AFMS.getMotor(3);

  int current_pulser;
  int current_pulsel;
  int current_pulseb;
  uint8_t motordir[3] = {FORWARD, FORWARD, FORWARD};
  unsigned long statestamp[3] = {0, 0, 0};

  int motordata[3] = {0, 0, 0};
  int motors_pulse_r;
  int motors_pulse_l;
  int motors_pulse_b;
  float dx;
  float dr;
  float dy;
  BLA::Matrix<3,1> motor_pwm;
  BLA::Matrix<3,1> command = {dx, dy, dr};
  BLA::Matrix<3,3> A = {cos(30*(M_PI/180)), cos(150*(M_PI/180)), cos(90*(M_PI/180)),
      -sin(30*(M_PI/180)), -sin(150*(M_PI/180)), sin(90*(M_PI/180)),
      1, 1, 1};
      
  
  void kinematics(){
  
  Multiply(A.Inverse(),command,motor_pwm);
  
  motordata[0] = (int) motor_pwm(0)*512;
  motordata[1] = (int) motor_pwm(1)*512;
  motordata[2] = (int) motor_pwm(2)*512;
  
  }
  
  void motors_count_pulse_r() {
  if (motordir[0] == FORWARD){
    current_pulser++;
  }
  else {
    current_pulser--;
    }
}
  void motors_count_pulse_l() {
  if (motordir[1] == FORWARD){
    current_pulsel++;
  }
  else {
    current_pulsel--;
    }
}
  void motors_count_pulse_b() {
  if (motordir[2] == FORWARD){
    current_pulseb--;
  }
  else {
    current_pulseb++;
    }
  
}
  
  int get_motors_pulse_r() {
    return motors_pulse_r;
  }
  int get_motors_pulse_l() {
    return motors_pulse_l;
  }
  int get_motors_pulse_b() {
    return motors_pulse_b;
  }
  
  float get_motors_data_r() {
    return dx;
  }
  float get_motors_data_l() {
    return dy;
  }
  float get_motors_data_b() {
    return dr;
  }
  
  
  /*
  	void rMotor(int speeddata) {
	  motordata[0] = speeddata;
	}
	void lMotor(int speeddata) {
		motordata[1] = speeddata;
	} 
	void bMotor(int speeddata) {
	  motordata[2] = speeddata;
	}
	*/
	
	void x_vel(int data) {
	  dx = data;
	}
	void ang_vel(int data) {
	  dr = data;
	}
	void y_vel(int data) {
	  dy = data;
	}
  
  void initMotorState() {
	  AFMS.begin();
	  leftMotor->setSpeed(0);
	  leftMotor->run(motordir[0]);
	  backMotor->setSpeed(0);
	  backMotor->run(motordir[1]);
	  rightMotor->setSpeed(0);
	  rightMotor->run(motordir[2]);
  
}

  void initMotors() {
    pinMode(2, INPUT_PULLUP); //Enc R
   	pinMode(3, INPUT_PULLUP); // Enc L
  	pinMode(18, INPUT_PULLUP); // Enc B
  
  	attachInterrupt(0, motors_count_pulse_r, RISING);
  	attachInterrupt(1, motors_count_pulse_l, RISING);
  	attachInterrupt(5, motors_count_pulse_b, RISING);
    interrupts(); 

    initMotorState();
  }
  
  
  void updateMotorState(byte i, Adafruit_DCMotor *motor) {
  	
    
    if (motordata[i] < 0) {
      motor->setSpeed(byte(abs(motordata[i])));
      motor->run(motordir[i]= FORWARD);
      
      //digitalWrite(mdir, motordir[i]= BACKWARD);
      //analogWrite(mvrm, byte(abs(motordata[i])));
    }
    
    else if (motordata[i] > 0){
     motor->setSpeed(byte(abs(motordata[i])));
     motor->run(motordir[i]= BACKWARD); 
     
     //digitalWrite(mdir, motordir[i] = FORWARD);
     //analogWrite(mvrm, byte(abs(motordata[i])));

    }
    //}
    else {
      motor->setSpeed(0);
      
      //analogWrite(mvrm, 0);
    }
}
  
  void updateState() {
  	kinematics();
    motors_pulse_r += current_pulser;
    current_pulser = 0;
  
    motors_pulse_l += current_pulsel;
    current_pulsel = 0;
    
    motors_pulse_b += current_pulseb;
    current_pulseb = 0;
  
    updateMotorState(0, rightMotor);
  	updateMotorState(1, leftMotor);
  	updateMotorState(2, backMotor);
  }

}
