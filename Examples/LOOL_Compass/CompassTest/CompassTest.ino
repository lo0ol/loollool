/**
 * \par Copyright (C), 2012-2015, LOOLLOOL
 * @file    Compass.ino
 * @author  Sean
 * @version V1.0.0
 * @date    2015/11/19
 * @brief   Description: this file is sample code for Compass device.
 *
 * Function List:
 * 1. void LOOL_Compass::init(void)
 * 2. double LOOL_Compass::getAngle(void)
 *
 * @par History:
 * <pre>
 * `<Author>`         `<Time>`        `<Version>`        `<Descr>`
 * Sean         2015/11/18           1.0.0       Rebuild the old lib.
 * </pre>
 *
 */
#include "LOOL_Smart.h"
#include <Wire.h>

LOOL_Compass Compass(PORT_4);

void setup()
{
  Serial.begin(9600);
  Serial.println("Initializing I2C devices...");
  Compass.begin();
  Serial.println("Testing device connections...");
  Serial.println(Compass.testConnection() ? "HMC5883L connection successful" : "HMC5883L connection failed");
}

void loop()
{
  int16_t head_X, head_Y, head_Z;
  double angle_number = 0;
  
  head_X = Compass.getHeadingX();
  head_Y = Compass.getHeadingY();
  head_Z = Compass.getHeadingZ();

  angle_number = Compass.getAngle();
  Serial.println(angle_number, 1);
  delay(500);
}
