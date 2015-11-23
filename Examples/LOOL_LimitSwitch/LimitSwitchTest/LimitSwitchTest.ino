/**
 * \par Copyright (C), 2012-2015, LOOL
 * @file    MicroSwitchTest.ino
 * @author  Sean
 * @version V1.0.0
 * @date    2015/09/010
 * @brief   Description: this file is sample program for Limit Switch module.
 *
 * Function List:
 *    1. void    bool LOOL_LimitSwitch::touched();
 *
 * @par History:
 * <pre>
 * `<Author>`         `<Time>`        `<Version>`        `<Descr>`
 * sean         2015/11/18     1.0.0            Rebuild the old lib.
 * </pre>
 */
/* Includes ------------------------------------------------------------------*/
#include "LOOL_Smart.h"

/* Private variables ---------------------------------------------------------*/
// LOOL_LimitSwitch module can only be connected to PORT_3, PORT_4, PORT_6, PORT_7, 

LOOL_LimitSwitch limitSwitch(PORT_6);

/* Private functions ---------------------------------------------------------*/
void setup()
{
  Serial.begin(9600);
  Serial.println("Start.");
}

void loop()
{
  if(limitSwitch.touched() )      // If the limit switch is touched, the  return value is true.
  {
    Serial.println("State: DOWN.");
    delay(1);
    while(limitSwitch.touched() )
    {
      ;// Repeat check the switch state, until released.
    }
    delay(2);
  }
  if(!limitSwitch.touched() )
  {
    Serial.println("State: UP.");
    delay(1);
    while(!limitSwitch.touched() )
    {
      ;
    }
    delay(2);
  }
}
