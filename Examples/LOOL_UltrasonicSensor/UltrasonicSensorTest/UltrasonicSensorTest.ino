/**
 * \par Copyright (C), 2012-2015, LOOLLOOL
 * @file    UltrasonicSensorTest.ino
 * @author  Sean
 * @version V1.0.0
 * @date    2015/09/01
 * @brief   Description: this file is sample code for  ultrasonic sensor module.
 *
 * Function List:
 * 1. double LOOL_UltrasonicSensor::distanceCm(uint16_t MAXcm)
 *
 * \par History:
 * <pre>
 * <Author>     <Time>        <Version>      <Descr>
 * Sean    2015/11/19    1.0.0          rebuild the old lib
 * </pre>
 */
#include "LOOL_Smart.h"

LOOL_UltrasonicSensor ultraSensor(PORT_7); /* Ultrasonic module can ONLY be connected to port 3, 4, 6, 7, 8 of base shield. */

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  Serial.print("Distance : ");
  Serial.print(ultraSensor.distanceCm() );
  Serial.println(" cm");
  delay(100); /* the minimal measure interval is 100 milliseconds */
}

