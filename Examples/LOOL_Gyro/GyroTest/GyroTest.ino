/**
 * \par Copyright (C), 2012-2015, LOOLLOOL
 * @file    GyroRotation.ino
 * @author  Sean
 * @version V1.0.0
 * @date    2015/09/09
 * @brief   Description: this file is sample code for Gyro device.
 *
 * Function List:
 * 1. void LOOL_Gyro::begin(void)
 * 2. void LOOL_Gyro::update(void) 
 * 3. double LOOL_Gyro::angleX(void)
 * 4. double LOOL_Gyro::angleY(void)
 * 5. double LOOL_Gyro::angleZ(void)
 *
 * @par History:
 * <pre>
 * `<Author>`         `<Time>`        `<Version>`        `<Descr>`
 *  Sean             2015/11/9          1.0.0         rebuild the old lib.
 * </pre>
 *
 */
#include "LOOL_Smart.h"
#include <Wire.h>

LOOL_Gyro gyro;
void setup()
{
  Serial.begin(9600);
  gyro.begin();
}

void loop()
{
  gyro.update();
  Serial.read();
  Serial.print("X:");
  Serial.print(gyro.getAngleX() );
  Serial.print(" Y:");
  Serial.print(gyro.getAngleY() );
  Serial.print(" Z:");
  Serial.println(gyro.getAngleZ() );
  delay(10);
}

