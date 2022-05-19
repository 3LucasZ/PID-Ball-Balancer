#include "Arduino.h"
#include "Ultrasonic.h"

Ultrasonic::Ultrasonic(int echoPin, int trigPin) {
  this->echoPin=echoPin;
  this->trigPin=trigPin;
  
  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);
}

double Ultrasonic::getDistance(){
  // Clears the trigPin condition
  digitalWrite(trigPin, LOW);
  
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)

  if (distance > 100) return 0;
  return distance;
}
