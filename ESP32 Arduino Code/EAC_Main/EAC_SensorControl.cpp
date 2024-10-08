// Last update: 2024-10-8
// BR09 EAC Code: Comms_4

#include "EAC_SensorControl.h"

long duration1 = 0;
long duration2 = 0;

void initialiseSensors() {
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
}
void readSensors() {
  digitalWrite(trigPin1, LOW);
  digitalWrite(trigPin2, LOW);
  delayMicrosecond(2);

  digitalWrite(trigPin1, LOW);
  delayMicrosecond(10);
  digitalWrite(trigPin1, HIGH);
  duration1 = pulseIn(echoPin1, HIGH);

  digitalWrite(trigPin2, LOW);
  delayMicrosecond(10);
  digitalWrite(trigPin2, HIGH);
  duration2 = pulseIn(echoPin2, HIGH);

  distance1 = speed / 10000 * duration1 / 2;
  distance2 = speed / 10000 * duration2 / 2;
}