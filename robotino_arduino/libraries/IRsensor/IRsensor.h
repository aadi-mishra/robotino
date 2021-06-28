#include "Arduino.h"
#include "SharpIR.h"


#define MAX_DISTANCE 30

// Sharp IR GP2Y0A41SK0F (4-30cm, analog)
#define IR1 A0 
#define IR2 A1 
#define IR3 A2
#define IR4 A3
#define IR5 A8
#define IR6 A9
#define IR7 A10
#define IR8 A11
#define IR9 A12

#define model1 430
#define model2 430
#define model3 430
#define model4 430
#define model5 430
#define model6 430
#define model7 430
#define model8 430
#define model9 430


namespace IRsensor {
	//int IR_NUM = 9;
	unsigned char distances[9] = { };
	SharpIR SharpIR1(IR1, model1);
	SharpIR SharpIR2(IR2, model2);
	SharpIR SharpIR3(IR3, model3);
	SharpIR SharpIR4(IR4, model4);
	SharpIR SharpIR5(IR5, model5);
	SharpIR SharpIR6(IR6, model6);
	SharpIR SharpIR7(IR7, model7);
	SharpIR SharpIR8(IR8, model8);
	SharpIR SharpIR9(IR9, model9);
	

	void initSensors() {
	
	}
	
	void updateState() {
  		unsigned long startTime = millis();

  		distances[0] = SharpIR1.distance();
	  	distances[1] = SharpIR2.distance();
	  	distances[2] = SharpIR3.distance();
	  	distances[3] = SharpIR4.distance();
	  	distances[4] = SharpIR5.distance();
	  	distances[5] = SharpIR6.distance();
	  	distances[6] = SharpIR7.distance();
	  	distances[7] = SharpIR8.distance();
	  	distances[8] = SharpIR9.distance();
	  	
	  	for (int i = 0 ; i< 9; i++){
	  	
		  	if (distances[i] >=30){
		  		distances[i] = 30;
		  	}
	  	} 	
	}
}


