#include <Servo.h>

int emgPin = A0; // Analog pin for EMG
int emgValue = 0; // EMG Sensor Value
Servo servo1;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  servo1.attach(6);
}

void loop() {
  // put your main code here, to run repeatedly:
  emgValue = analogRead(emgPin);
  int servo1POS = map(emgValue, 0, 1023, 0, 180);
  servo1.write(servo1POS);
  Serial.println(emgValue);
  delay(50);
}
