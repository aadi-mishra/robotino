#include "Arduino.h"

#define GRAPH     "graph"
#define NOGRAPH   "nograph"
#define VERBOSE   "verbose"
#define NOVERBOSE "noverbose"

namespace PIDController {

  unsigned long lastTime;
  double output;
  double lastErr;
  double timeChanged;
  double error;
  double errSum;
  double dErr;
  bool doLimit;
  bool doConstrain;
  bool init;
  double Kp;
  double Ki;
  double Kd;
  double divisor;
  double minOut;
  double maxOut;
  double setPoint;

  void begin () {
    Kp = 1;
    Ki = 1;
    Kd = 1;
    divisor = 10;
    doLimit = false;
    init = true;
  }

  void setpoint (double newSetpoint) {
    setPoint = newSetpoint;
  }

  void tune (double _Kp, double _Ki, double _Kd) {
    if (_Kp < 0 || _Ki < 0 || _Kd < 0) return;
    Kp = _Kp;
    Ki = _Ki;
    Kd = _Kd;
  }

  void limit(double min, double max) {
    minOut = min;
    maxOut = max;
    doLimit = true;
  }

  void printGraph (double sensorInput, String verbose) {
    Serial.print(sensorInput);
    if (verbose == VERBOSE) {
      Serial.print(",");
      Serial.print(output);
    }
    Serial.print(",");
    Serial.println(setPoint);
  }


  void minimize (double newMinimize) {
    divisor = newMinimize;
  }

  // Getters
  double getOutput () {
    return output;
  }


  double compute (double sensor, String graph = GRAPH, String verbose = VERBOSE) {
  // Return false if it could not execute;
  // This is the actual PID algorithm executed every loop();

  // Failsafe, return if the begin() method hasn't been called
    if (!init) return 0;

    // Calculate time difference since last time executed
    unsigned long now = millis();
    double timeChange = (double)(now - lastTime);

    // Calculate error (P, I and D)
    double error = setPoint - sensor;
    errSum += error * timeChange;
    if (doLimit) {
      errSum = constrain(errSum, minOut * 1.1, maxOut * 1.1); 
    }
    double dErr = (error - lastErr) / timeChange;

    // Calculate the new output by adding all three elements together
    double newOutput = (Kp * error + Ki * errSum + Kd * dErr) / divisor;

    // If limit is specifyed, limit the output
    if (doLimit) {
      output = constrain(newOutput, minOut, maxOut);
    } else {
      output = newOutput;  
    }

    // Update lastErr and lastTime to current values for use in next execution
    lastErr = error;
    lastTime = now;

    // Draw the garph if GRAPH mode
    if (graph == GRAPH) {
      printGraph(sensor, verbose);
    }

    // Return the current output
    return output;
  }
}
