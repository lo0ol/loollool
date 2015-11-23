/**
 * \par Copyright (C), 2012-2015, LOOLLOOL
 * @file    TouchSensorTest.ino
 * @author  Sean
 * @version V1.0.0
 * @date    2015/11/19
 * @brief   Description: this file is sample code for touch sensor device.
 *
 * Function List:
 *    1. bool LOOL_TouchSensor::touched()
 *    2. void LOOL_TouchSensor::SetTogMode(uint8_t TogMode)
 *
 * @par History:
 * <pre>
 * `<Author>`         `<Time>`        `<Version>`        `<Descr>`
 * sean         2015/11/18     1.0.0            Rebuild the old lib.
 * </pre>
 *
 */
#include "LOOL_Smart.h"

// Me_LimitSwitch module can only be connected to PORT_3, PORT_4, PORT_6,PORT_7,PORT_8 of base shield
// or from PORT_3 to PORT_8 of baseboard.
LOOL_TouchSensor TouchSensor(PORT_6);

void setup()
{
  Serial.begin(9600);
  Serial.println("Start.");
  TouchSensor.SetTogMode(0);
}

void loop()
{
  if(TouchSensor.touched() )      // If the limit switch is touched, the  return value is true.
  {
    Serial.println("State: DOWN.");
    delay(1);
    while(TouchSensor.touched() )
    {
      ;                             // Repeat check the switch state, until released
    }
    delay(2);
  }
  if(!TouchSensor.touched() )
  {
    Serial.println("State: UP.");
    delay(1);
    while(!TouchSensor.touched() )
    {
      ;
    }
    delay(2);
  }
}

