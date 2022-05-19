#ifndef ULTRASONIC_H
#define ULTRASONIC_H

#include "Arduino.h"

class Ultrasonic {
  private:
    int echoPin;
    int trigPin;
    double duration = 0;
    double distance = 0;
    
  public:
    Ultrasonic(int echoPin, int trigPin);
    double getDistance();
};

#endif
