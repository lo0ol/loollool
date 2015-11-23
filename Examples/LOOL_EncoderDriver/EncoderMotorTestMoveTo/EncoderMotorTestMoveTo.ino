#include "LOOL_Smart.h"
#include <Wire.h>
#include <SoftwareSerial.h>

LOOL_EncoderMotor motor1(0x09, SLOT1);   //  Motor at slot1
LOOL_EncoderMotor motor2(0x09, SLOT2);   //  motor at slot2

void setup()
{
  motor1.begin();
  motor2.begin();
  Serial.begin(9600);
}

void loop()
{
  motor2.moveTo(360, 200);
  motor1.moveTo(360, 200);
  delay(2000);
  motor2.moveTo(0, 100);
  motor1.moveTo(0, 100);
  delay(2000);
}

