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

/* Private functions ---------------------------------------------------------*/
/* LOOL_LimitSwitch module can only be connected to PORT_3, PORT_4, PORT_6, 
*/
LOOL_LimitSwitch limitSwitch1(PORT_3, SLOT1);      // connecte to Me RJ25 Adapter SLOT1


LOOL_LimitSwitch limitSwitch2(PORT_3, SLOT2);      // connecte to Me RJ25 Adapter SLOT2


void setup()
{
  Serial.begin(9600);
  Serial.println("Start.");
}

void loop()
{
  if(limitSwitch1.touched() )     // If the limit switch is touched, the  return value is true.
  {
    delay(10);
    Serial.println("limitSwitch1 DOWN.");
  }
  if(limitSwitch2.touched() )     // If the limit switch is touched, the  return value is true.
  {
    delay(10);
    Serial.println("limitSwitch2 DOWN.");
  }
}
