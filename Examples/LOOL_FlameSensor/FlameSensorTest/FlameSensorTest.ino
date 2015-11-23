/**
 * \par Copyright (C), 2012-2015, LOOLLOOL
 * @file    FlameSensorTest.ino
 * @author  Sean
 * @version V1.0.0
 * @date    2015/09/09
 * @brief   Description: this file is sample code for flame snesor device.
 *
 * Function List:
 *    1. uint8_t LOOL_FlameSensor::readDigital(void)
 *    2. LOOL_FlameSensor::readAnalog(void)
 *
 * @par History:
 * <pre>
 * `<Author>`         `<Time>`        `<Version>`        `<Descr>`
 * sean         2015/09/09     1.0.0            Rebuild the old lib.
 * </pre>
 */
#include "LOOL_Smart.h"

LOOL_FlameSensor FlameSensor(PORT_8);

void setup() 
{
  Serial.begin(115200);
}

void loop() 
{
  // put your main code here, to run repeatedly:
  Serial.print("Analog Value is: ");
  Serial.print(FlameSensor.readAnalog());
  Serial.print("----Status: ");
  if(FlameSensor.readDigital() == Fire)
  {
    Serial.println("Fire");
  }
  else if(FlameSensor.readDigital() == NoFire)
  {
    Serial.println("NoFire");
  }
  delay(200);
}

