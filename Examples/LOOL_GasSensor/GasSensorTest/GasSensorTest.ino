/**
 * @par Copyright (C), 2012-2015, LOOLLOOL
 * @file    GasSensorTest.ino
 * @author  Sean
 * @version V1.0.0
 * @date    2015/09/09
 * @brief   Description: this file is sample code for gas snesor device.
 *
 * Function List:
 *    1. uint8_t LOOL_GasSensor::readDigital(void)
 *    2. int16_t LOOL_GasSensor::readAnalog(void)
 *
 * @par History:
 * <pre>
 * `<Author>`         `<Time>`        `<Version>`        `<Descr>`
 * sean         2015/11/19     1.0.0            Rebuild the old lib.
 * </pre>
 */
#include "LOOL_Smart.h"

LOOL_GasSensor GasSensor(PORT_8);

void setup() 
{
  Serial.begin(115200);
}

void loop() 
{
  Serial.print("Analog Value is: ");
  Serial.print(GasSensor.readAnalog());
  Serial.print("----Status: ");
  if(GasSensor.readDigital() == Gas_Exceeded)
  {
    Serial.println("The concentration exceeds");
  }
  else if(GasSensor.readDigital() == Gas_not_Exceeded)
  {
    Serial.println("The concentration of the gas in the range");
  }
  delay(200);
}
