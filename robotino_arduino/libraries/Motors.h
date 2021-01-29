#include "Arduino.h"

#define m_strstp1 A15
#define m_rnbrk1 A14
#define m_dir1 4
#define m_intr_extr1 A12
#define m_alrm_rst1 A11
#define m_encoder1 2
#define m_pwm1 5

#define m_strstp2 23
#define m_rnbrk2 25
#define m_dir2 8
#define m_intr_extr2 29
#define m_alrm_rst2 31
#define m_encoder2 3
#define m_pwm2 9

/*
#define m_strstp2 23
#define m_rnbrk2 25
#define m_dir3 13
#define m_intr_extr2 29
#define m_alrm_rst2 31
#define m_encoder3 3
#define m_pwm3 11
*/

namespace Motors {

  byte motorstate[2] = {1, 1};
  uint8_t motordir[2] = {LOW, HIGH};
  int motordata[2] = {0, 0};
  unsigned long statestamp[2] = {0, 0};
  
  int current_pulse1;
  int current_pulse2;
  int current_pulse3;
  
  int motors_pulse1;
  int motors_pulse2;
  int motors_pulse3;
  
  void motors_count_pulse1() {
		if(digitalRead(2) == HIGH)
		  current_pulse1++;
		else
		  current_pulse1--;
  }
  
	void motors_count_pulse2() {
		if(digitalRead(3) == HIGH)
			current_pulse2++;
		else
			current_pulse2--;
	  }
	  
	void motors_count_pulse3() {
		if(digitalRead(xxx) == HIGH)
			current_pulse3++;
		else
			current_pulse3--;
	  }
  
  int get_motors_pulse1() {
    return motors_pulse1;
  }
  
  int get_motors_pulse2() {
    return motors_pulse2;
  }
  
  int get_motors_pulse3() {
    return motors_pulse3;
  }
  
void initMotorState() {
    digitalWrite(m_dir1, motordir[0]);
    digitalWrite(m_dir2, motordir[1]);
    digitalWrite(m_dir3, motordir[1]);
    delay(10);
  }
void initMotors() {
	pinMode(m_dir1, OUTPUT);
	pinMode(m_dir2, OUTPUT);
	pinMode(m_vrm1, OUTPUT);
	pinMode(m_vrm2, OUTPUT);
	pinMode(m_rnbrk1, OUTPUT);
	pinMode(m_rnbrk2, OUTPUT);
	pinMode(m_strstp1, OUTPUT);
	pinMode(m_strstp2, OUTPUT);
	pinMode(m_alrm_rst1, OUTPUT);
	pinMode(m_alrm_rst2, OUTPUT);
	pinMode(m_intr_extr1, OUTPUT);
	pinMode(m_intr_extr2, OUTPUT);
	pinMode(m_encoder1, INPUT_PULLUP);
	pinMode(m_encoder2, INPUT_PULLUP);
  
	attachInterrupt(4, motors_count_pulse1, RISING);
	attachInterrupt(5, motors_count_pulse2, RISING);
	//attachInterrupt(5, motors_count_pulse3, RISING);
	interrupts();  

	initMotorState();
  }	
void stopMotors() {
if(motorstate[0]==0) {
   digitalWrite(m_strstp1, HIGH);
   analogWrite(m_vrm1, 0);
   motordata[0] = 0;
   motorstate[0] = 1;
   statestamp[0] = millis();
}

if(motorstate[1]==0) {
   digitalWrite(m_strstp2, HIGH);
   analogWrite(m_vrm2, 0);
   motordata[1] = 0;
   motorstate[1] = 1;
   statestamp[1] = millis();
}
}

void breakMotors() {
    if(motorstate[0]==0) {
      digitalWrite(m_rnbrk1, HIGH);
      motordata[0] = 0;
      motorstate[0] = 2;
      analogWrite(m_vrm1, 0);
      statestamp[0] = millis();
    }

    if(motorstate[1]==0) {
      digitalWrite(m_rnbrk2, HIGH);
      motordata[1] = 0;
      motorstate[1] = 2;
      analogWrite(m_vrm2, 0);
      statestamp[1] = millis();
    }
  }
