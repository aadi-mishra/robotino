#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include <utility/Adafruit_MS_PWMServoDriver.h>
#include <math.h>

namespace Motors {

	Adafruit_MotorShield AFMS = Adafruit_MotorShield();
	Adafruit_DCMotor *leftMotor = AFMS.getMotor(1);
	Adafruit_DCMotor *backMotor = AFMS.getMotor(2);
	Adafruit_DCMotor *rightMotor = AFMS.getMotor(4);

	int current_pulser;
	int current_pulsel;
	int current_pulseb;
	 
	uint8_t motordir[3] = {FORWARD, FORWARD, FORWARD};
	unsigned long statestamp[3] = {0, 0, 0};

	int motordata[3] = {0, 0, 0};
	int motors_pulse_r;
	int motors_pulse_l;
	int motors_pulse_b;      

	// Counts encoder ticks
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
	
	// returns encoder values corresponding to each motors
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
	}
	void lMotor(int speeddata) {
		motordata[1] = speeddata;
	} 
	void bMotor(int speeddata) {
		motordata[2] = speeddata;
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
	// Initialse Motors
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

	// Update Motor state ( Forward, Backward, Stop)
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
	// Update Encoder State (Encoder Position)
	void updateState() {
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
