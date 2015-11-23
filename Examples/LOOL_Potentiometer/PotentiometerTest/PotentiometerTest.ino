/**
 * @par Copyright (C), 2012-2015, LOOLLOOL
 * @file    PotentiometerTest.ino
 * @author  Sean
 * @version V1.0.0
 * @date    2015/11/18
 * @brief   Description: this file is sample program for Potentiometer module.
 *
 * Function List:
 * 1. uint16_t LOOL_Potentiometer::read(); 
 *
 * \par History:
 * <pre>
 * `<Author>`         `<Time>`        `<Version>`        `<Descr>`
 *  Sean         2015/07/24     1.0.0            Rebuild the old lib.
 * </pre>
 */

/* Includes ------------------------------------------------------------------*/
#include "LOOL_Smart.h"

/* Private variables ---------------------------------------------------------*/
LOOL_Potentiometer Potentiometer(PORT_6);

/* Private functions ---------------------------------------------------------*/
void setup()
{
  Serial.begin(9600);
}

void loop()
{
  Serial.print("value=");
  Serial.println(Potentiometer.read() );
  delay(100);
}
