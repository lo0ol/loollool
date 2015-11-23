/**
 * \par Copyright (C), 2012-2015, LOOLLOOL
 * @file    RJ25AdapterTest.ino
 * @author  Sean
 * @version V1.0.0
 * @date    2015/09/02
 * @brief   Description: this file is sample code for RJ25 adapter module
 *
 * Function List:
 * 1. bool LOOL_RGBLed::dWrite1(bool value)
 * 2. bool LOOL_RGBLed::dRead2()
 * \par History:
 * <pre>
 * <Author>     <Time>        <Version>      <Descr>
 * Sean    2015/09/02    1.0.0          rebuild the old lib
 * </pre>
 */

#include "LOOL_Smart.h"

LOOL_Port output(PORT_4);


LOOL_Port input(PORT_3);


int val;
void setup()
{
  Serial.begin(9600);
}

void loop()
{
  output.dWrite1(HIGH);   /* SLOT1 HIGH */
  delay(500);
  output.dWrite1(LOW);    /* SLOT1 LOW */
  delay(500);

  val = input.dRead1();   /* read SLOT1 level */
  Serial.print("val=");
  Serial.println(val);
}

