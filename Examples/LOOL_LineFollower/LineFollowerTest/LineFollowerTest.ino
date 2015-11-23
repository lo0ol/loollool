/**
 * \par Copyright (C), 2012-2015, LOOLLOOL
 * @file    LineFollowerTest.ino
 * @author  Sean
 * @version V1.0.0
 * @date    2015/11/18
 * @brief   Description: this file is sample code for LOOL line follower module.
 *
 * Function List:
 * 1. uint8_t LOOL_LineFollower::readSensors(void)
 *
 * \par History:
 * <pre>
 * `<Author>`         `<Time>`        `<Version>`        `<Descr>`
 * sean         2015/09/07     1.0.0            Rebuild the old lib.
 * </pre>
 */
#include "LOOL_Smart.h"

LOOL_LineFollower lineFinder(PORT_3); /* Line Finder module can only be connected to PORT_3, PORT_4, PORT_5, PORT_6 of base shield. */

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  int sensorState = lineFinder.readSensors();
  switch(sensorState)
  {
    case S1_IN_S2_IN: Serial.println("Sensor 1 and 2 are inside of black line"); break;
    case S1_IN_S2_OUT: Serial.println("Sensor 2 is outside of black line"); break;
    case S1_OUT_S2_IN: Serial.println("Sensor 1 is outside of black line"); break;
    case S1_OUT_S2_OUT: Serial.println("Sensor 1 and 2 are outside of black line"); break;
    default: break;
  }
  delay(200);
}

