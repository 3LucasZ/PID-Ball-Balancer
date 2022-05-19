#include <Servo.h>
#include "Ultrasonic.h"

Servo servo;
Ultrasonic ultrasonic(2, 3);
//Best so far: 
//P: 0.08
//I: 0
//D: 0.04
//CYCLE_TIME: 100
const double K_P = 0.04;
const double K_I = 0;
const double K_D = 0.02;
const double MIDPOINT = 16;
const int CYCLE_TIME = 50;
const int MAX_CYCLES = 40;
const double MAX_ANGLE_DELTA = 20;
const double INIT_ANGLE = 90;

double angle = INIT_ANGLE;
double lastError = 0;
double error = 0;
double errorDerivative = 0;
double errorIntegral = 0;
double riemannSums[MAX_CYCLES];
int cycles = 0;

bool test = false;

void setup() {
  Serial.begin(9600);

  servo.attach(10);
  servo.write(angle);
}

void loop() {
  if (test){
    Serial.print("Distance: ");
    Serial.println(ultrasonic.getDistance());
  }
  else {
    lastError = error;
    int dist = ultrasonic.getDistance();
    if (dist >35) return;
    
    error = MIDPOINT - dist;
    errorDerivative = (error - lastError) / (CYCLE_TIME/1000.0);
    errorIntegral -= riemannSums[cycles];
    riemannSums[cycles] = error*CYCLE_TIME/1000.0;
    errorIntegral += riemannSums[cycles];

    double P = error*K_P;
    double I = errorIntegral*K_I;
    double D = errorDerivative*K_D;
    
    angle += P+I+D;
    
    if (angle < INIT_ANGLE-MAX_ANGLE_DELTA) angle = INIT_ANGLE-MAX_ANGLE_DELTA;
    if (angle > INIT_ANGLE+MAX_ANGLE_DELTA) angle = INIT_ANGLE+MAX_ANGLE_DELTA;
    servo.write(angle);
    
//    Serial.print("P:");
//    Serial.print(P);
//    Serial.print(",");
//    
//    Serial.print("I:");
//    Serial.print(I);
//    Serial.print(",");
//    
//    Serial.print("D:");
//    Serial.print(D);
//    Serial.print(",");
//    
//    Serial.print("Raw Distance:");
//    Serial.print(dist);
//    Serial.print(",");
    
    Serial.print("Angle:");
    Serial.print(angle);
    Serial.print(",");
    
    Serial.print("Error:");
    Serial.println(error);
    
    cycles=(cycles+1)%MAX_CYCLES;
  }
  delay(CYCLE_TIME);
} 

//Black, Green, Blue, Red
