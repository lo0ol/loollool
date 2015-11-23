/**
 * \par Copyright (C), 2012-2015, LOOLLOOL
 * @file    WifiTest.ino
 * @author  Sean
 * @version V1.0.0
 * @date    2015/09/09
 * @brief   Description: this file is sample code for  WiFi module.
 *          The wifi inherited the Serial class from SoftwareSerial.
 *
 * Function List:
 * 1. void LOOL_Wifi::begin()
 * 2. int16_t LOOL_Wifi::available()
 * 3. size_t LOOL_Wifi::write(uint8_t byte)
 * 4. int16_t LOOL_Wifi::read(void)
 *
 * @par History:
 * <pre>
 * `<Author>`         `<Time>`        `<Version>`        `<Descr>`
 * sean         2015/11/18     1.0.0            Rebuild the old lib.
 * </pre>
 */
#include "LOOL_Smart.h"
#include <SoftwareSerial.h>

LOOL_Wifi Wifi(PORT_4);

void setup()
{
  Serial.begin(9600);
  Wifi.begin(9600);
  Serial.println("Wifi Start!");
}

void loop()
{
  char inDat;
  char outDat;
  if(Wifi.available() )
  {
    char c = Wifi.read();
    Serial.print(c);
  }
  if(Serial.available() )
  {
    outDat = Serial.read();
    Wifi.write(outDat);
  }
}

