/**
 * \par Copyright (C), 2012-2015, LOOLLOOL
 * @file    HumitureSensorTest.ino
 * @author  Sean
 * @version V1.0.0
 * @date    2015/09/07
 * @brief   Description: this file is sample code for humiture sensor device.
 *
 * Function List:
 *    1. void LOOL_Humiture::update(void)
 *    2. uint8_t LOOL_Humiture::getHumidity(void)
 *    3. uint8_t LOOL_Humiture::getTemperature(void)
 *
 * \par History:
 * <pre>
 * <Author>     <Time>        <Version>      <Descr>
 * Sean     2015/09/07    1.0.0          rebuild the old lib
 * </pre>
 */
#include <LOOL_Smart.h>

LOOL_Humiture humiture(PORT_6);

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  humiture.update();
  Serial.print("Humidity=");
  Serial.print( humiture.getHumidity() );
  Serial.print(",Temperature=");
  Serial.println( humiture.getTemperature() );
  delay(300);
}

