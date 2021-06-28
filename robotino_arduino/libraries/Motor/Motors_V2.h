#include <Wire.h>
#include <math.h>

namespace Motors {

	const int pwm_l = 6 ; //initializing pin 2 as pwm
	const int dir_l = 7 ;
	const int pwm_b = 9 ; 
	const int dir_b = 8 ;
	const int pwm_r = 5;
	const int dir_r = 4;

	int current_pulser;
	int current_pulsel;
	int current_pulseb;
	uint8_t motordir[3] = {LOW, LOW, LOW};
	unsigned long statestamp[3] = {0, 0, 0};

	int motordata[3] = {0, 0, 0};
	int motors_pulse_r;
	int motors_pulse_l;
	int motors_pulse_b;
    
	void motors_count_pulse_r() {
		if (motordir[0] == HIGH){
			current_pulser--;
		}
		else {
			current_pulser++;
		}
	}
	void motors_count_pulse_l() {
		if (motordir[1] == HIGH){
			current_pulsel--;
		}
		else {
			current_pulsel++;
		}
	}
	void motors_count_pulse_b() {
		if (motordir[2] == HIGH){
			current_pulseb++;
		}
		else {
			current_pulseb--;
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

		pinMode(2, INPUT_PULLUP); //Enc R
		pinMode(3, INPUT_PULLUP); // Enc L
		pinMode(18, INPUT_PULLUP); // Enc B

		attachInterrupt(0, motors_count_pulse_r, RISING);
		attachInterrupt(1, motors_count_pulse_l, RISING);
		attachInterrupt(5, motors_count_pulse_b, RISING);
		interrupts(); 

		initMotorState();
	}
  
	void updateMotorState(byte i, int mdir, int mvrm) {
		
		if ((millis()-statestamp[i]) > 10) {
			if (motordata[i] < 0) {

				digitalWrite(mdir, motordir[i]= LOW);
				analogWrite(mvrm, byte(abs(motordata[i])));
				statestamp[i] = millis();
			  
			}
			
			else if (motordata[i] > 0){

				digitalWrite(mdir, motordir[i] = HIGH);
				analogWrite(mvrm, byte(abs(motordata[i])));
				statestamp[i] = millis();
			 
			}
			else {
			  
			 	analogWrite(mvrm, 0);
			}
		}
	}
  
	void updateState() {
		motors_pulse_r += current_pulser;
		current_pulser = 0;

		motors_pulse_l += current_pulsel;
		current_pulsel = 0;

		motors_pulse_b += current_pulseb;
		current_pulseb = 0;

		updateMotorState(0, dir_r, pwm_r);
		updateMotorState(1, dir_l, pwm_l);
		updateMotorState(2, dir_b, pwm_b);
	}

}
