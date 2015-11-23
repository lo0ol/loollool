/**
 * \par Copyright (C), 2012-2015, LOOLLOOL
 * @file    SoundSensorTest.ino
 * @author  Sean
 * @version V1.0.0
 * @date    2015/09/01
 * @brief   Description: this file is sample code for  sound sensor device.
 *
 * Function List:
 * 1. int16_t LOOL_SoundSensor::strength()
 *
 * \par History:
 * <pre>
 * <Author>     <Time>        <Version>      <Descr>
 * Sean     2015/09/01    1.0.0          rebuild the old lib
 * </pre>
 */
#include "LOOL_Smart.h"

LOOL_SoundSensor mySound(PORT_6);

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  Serial.print("value=");
  Serial.println(mySound.strength() );
  delay(100);
}

