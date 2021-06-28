#include <Wire.h>
#include <math.h>

namespace Motors {

	const int pwm_l = 6 ; //initializing pin 2 as pwm
	const int dir_l = 7 ;
	const int pwm_b = 9 ; 
	const int dir_b = 8 ;
	const int pwm_r = 5;
	const int dir_r = 4;

	uint8_t motordir[3] = {LOW, LOW, LOW};
	unsigned long statestamp[3] = {0, 0, 0};

	int motordata[3] = {0, 0, 0};
      
  	void rMotor(int speeddata) {
	  motordata[0] = speeddata;

	  statestamp[0] = millis();
	}
	void lMotor(int speeddata) {
		motordata[1] = speeddata;
		statestamp[1] = millis();
	} 
	void bMotor(int speeddata) {
	  motordata[2] = speeddata;
	  statestamp[2] = millis();
	}

	void stop_motors(){
		motordata[0] = 0;
		motordata[1] = 0;
		motordata[2] = 0;
	}

  
	void initMotorState() {

		digitalWrite(dir_r,LOW) ;
		analogWrite(pwm_r,0) ;

		digitalWrite(dir_l,LOW) ;
		analogWrite(pwm_l,0) ;

		digitalWrite(dir_b,LOW) ;
		analogWrite(pwm_b,0) ;

	}

	void initMotors() {

		pinMode(pwm_r,OUTPUT) ; //we have to set PWM pin as output
		pinMode(dir_r,OUTPUT) ; //Logic pins are also set as

		pinMode(pwm_l,OUTPUT) ; //we have to set PWM pin as output
		pinMode(dir_l,OUTPUT) ; //Logic pins are also set as output

		pinMode(pwm_b,OUTPUT) ; //we have to set PWM pin as output
		pinMode(dir_b,OUTPUT) ; //Logic pins are also set as output

		initMotorState();
	}
  
  
	void updateMotorState(byte i, int mdir, int mvrm) {
		
		if ((millis()-statestamp[i]) > 10) {
			if (motordata[i] < 0) {

			  digitalWrite(mdir, motordir[i]= HIGH);
			  analogWrite(mvrm, byte(abs(motordata[i])));
			  statestamp[i] = millis();
			  
			}
			
			else if (motordata[i] > 0){

			 digitalWrite(mdir, motordir[i] = LOW);
			 analogWrite(mvrm, byte(abs(motordata[i])));
			 statestamp[i] = millis();
			 
			}

			else {
			  //digitalWrite(mdir, motordir[i] = HIGH);
			  analogWrite(mvrm, 0);
			  //statestamp[i] = millis();

			}
		}
	}
  
	void updateState() {
		updateMotorState(0, dir_r, pwm_r);
		updateMotorState(1, dir_l, pwm_l);
		updateMotorState(2, dir_b, pwm_b);
	}

}
