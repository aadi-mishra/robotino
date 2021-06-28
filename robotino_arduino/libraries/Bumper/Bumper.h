/*#if ARDUINO>=100
  #include <Arduino.h>  // Arduino 1.0
#else
  #include <WProgram.h>  // Arduino 0022
#endif
*/

//#define inPin A15   // choose the input pin MEGA
#define inPin A5   // choose the input pin MEGA

namespace Bumper {

	float bump = 0;
	unsigned long last_read_stamp = 0;
	
	
	void initBumper() {
		pinMode(inPin, INPUT);
	}
	
	void updateState() {
		if((millis()-last_read_stamp)>10) {
			bump = analogRead(inPin);
			last_read_stamp = millis();
		}
	}
}


