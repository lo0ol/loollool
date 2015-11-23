/**
 * @par Copyright (C), 2012-2015, LOOLLOOL
 * @file     BluetoothTest.ino
 * @author  Sean
 * @version V1.0.0
 * @date    2015/09/09
 * @brief   Description: this file is sample code for  bluetooth device.
 *
 * Function List:
 * 1. void LOOL_Bluetooth::begin()
 * 2. int16_t LOOL_Bluetooth::available()
 * 3. size_t LOOL_Bluetooth::write(uint8_t byte)
 * 4. int16_t LOOL_Bluetooth::read(void)
 *
 * \par History:
 * <pre>
 * <Author>     <Time>        <Version>      <Descr>
 * Sean     2015/11/19    1.0.0          rebuild the old lib
 * </pre>
 */
 
#include "LOOL_Smart.h"
#include <SoftwareSerial.h>

LOOL_Bluetooth bluetooth(PORT_3);

unsigned char table[128] = {0};

void setup()
{
  Serial.begin(115200);
  bluetooth.begin(115200);    //The factory default baud rate is 115200
  Serial.println("Bluetooth Start!");
}

void loop()
{ 
  int readdata = 0,i = 0,count = 0;
  char outDat;
  if (bluetooth.available())
  {
    while((readdata = bluetooth.read()) != (int)-1)
    {
      table[count] = readdata;
      count++;
      delay(1);
    }
    for(i = 0;i<count;i++)
    {
      Serial.write(table[i]);
    }
  }
  if(Serial.available() )
  {
    outDat = Serial.read();
    bluetooth.write(outDat);
  }
}

