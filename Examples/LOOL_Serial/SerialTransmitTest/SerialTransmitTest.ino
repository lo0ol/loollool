/**
 * \par Copyright (C), 2012-2015, LOOLLOOL
 * @file    SerialTest.ino
 * @author  Sean
 * @version V1.0.0
 * @date    2015/09/09
 * @brief   Description: this file is sample code for hardware/software Serial.
 *
 * Function List:
 * 1. void LOOL_Serial::begin(long baudrate)
 * 2. void LOOL_Serial::printf(char *fmt,...)
 *
 * \par History:
 * <pre>
 * <Author>     <Time>        <Version>      <Descr>
 *  Sean   2015/09/09    1.0.0          rebuild the old lib
 * </pre>
 */
#include "LOOL_Smart.h"
#include <SoftwareSerial.h>

LOOL_Serial mySerial(PORT_8);

void setup()
{
  mySerial.begin(9600);
}

void loop()
{
  mySerial.println("just for test");
  mySerial.printf("%d,0x%x \r\n",123,0x123);
  delay(100);
}

