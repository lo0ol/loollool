/**
 * \par Copyright (C), 2012-2015, LOOLLOOL
 * @file    ShutterTest.ino
 * @author  Sean
 * @version V1.0.0
 * @date    2015/11/18
 * @brief   Description: this file is sample code for LOOL Shutter device.
 *
 * Function List:
 * 1. void LOOL_Shutter::shotOn()
 * 2. void LOOL_Shutter::shotOff()
 * 3. void LOOL_Shutter::focusOn()
 * 4. void LOOL_Shutter::focusOff()
 *
 * \par History:
 * <pre>
 * <Author>     <Time>        <Version>      <Descr>
 *  Sean       2015/11/18      1.0.0          rebuild the old lib
 * </pre>
 */
#include "LOOL_Smart.h"

// LOOL_Shutter module can only be connected to the PORT_3, PORT_4, PORT_6 on Smart board
LOOL_Shutter shutter(PORT3);

void setup()
{
  /* initialize serial communications at 9600 bps */
  Serial.begin(9600);
}

void loop()
{
  if(Serial.available())
  {
    char a = Serial.read();
    if(a == 's')
    {
      shutter.focusOn();
      delay(1000);
      shutter.shotOn();
      delay(200);
      shutter.shotOff();
      shutter.focusOff();
    }
    if(a == 'f')
    {
      shutter.focusOn();
      delay(1500);
      shutter.focusOff();
    }
  }
}

