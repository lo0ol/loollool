/**
 * \par Copyright (C), 2012-2015, LOOLLOOL
 * @file    USBHostTest.ino
 * @author  Sean
 * @version V1.0.0
 * @date    2015/09/09
 * @brief   This file is a drive for LOOL USBHost device, The USBHost inherited the 
 *            LOOL_Serial class from SoftwareSerial.
 * Function List:
 *    1. void LOOL_USBHost::init(int8_t type)
 *    2. int16_t LOOL_USBHost::initHIDDevice()
 *    3. int16_t LOOL_USBHost::probeDevice()
 *    4. void LOOL_USBHost::resetBus()
 *    5. uint8_t LOOL_USBHost::host_recv()
 *
 *
 * @par History:
 * <pre>
 * `<Author>`         `<Time>`        `<Version>`        `<Descr>`
 * sean         2015/11/18     1.0.0            Rebuild the old lib.
 * </pre>
 */
#include "LOOL_Smart.h"
#include "SoftwareSerial.h"

LOOL_USBHost usbhost(PORT_3);

void parseJoystick(unsigned char *buf)   //Analytic function, print 8 bytes from USB Host
{
  int i = 0;
  for(i = 0; i < 7; i++)
  {
    Serial.print(buf[i]);  //It won't work if you connect to the Makeblock Orion.
    Serial.print('-');
  }
  Serial.println(buf[7]);
  delay(10);
}

void setup()
{
  Serial.begin(57600);
  usbhost.init(USB1_0);  //USB1_0 or USB2_0
}

void loop()
{
  if(!usbhost.device_online)
  {
    usbhost.probeDevice();
    delay(1000);
  }
  else
  {
    int len = usbhost.host_recv();
    parseJoystick(usbhost.RECV_BUFFER);
    delay(5);
  }
}

