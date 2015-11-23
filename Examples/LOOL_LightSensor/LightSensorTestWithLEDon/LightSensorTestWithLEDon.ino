/**
 * @par Copyright (C), 2012-2015, LOOLLOOL
 * @file    LightSensorTestWithLEDon.ino
 * @author  Sean
 * @version V1.0.0
 * @date    2015/09/18
 * @brief   Description: this file is sample program for LOOL Light Sensor module.
 *
 * Function List:
 *    1. void    LightSensor::lightOn();
 *    2. int16_t LightSensor::read();
 *
 * @par History:
 * <pre>
 * `<Author>`         `<Time>`        `<Version>`        `<Descr>`
 * sean         2015/11/18     1.0.0            Rebuild the old lib.
 * </pre>
 */

/* Includes ------------------------------------------------------------------*/
#include "LOOL_Smart.h"

/* Private variables ---------------------------------------------------------*/
LOOL_LightSensor lightSensor(PORT_6);
int value = 0;      // a variable for the lightSensor's value


/* Private functions ---------------------------------------------------------*/
/**
 * \par Function
 *    setup
 * \par Description
 *    Run once, initialize serial port.
 * \param[in]
 *    None
 * \par Output
 *    None
 * \return
 *    None.
 * \par Others
 *    None
 */
void setup()
{
  // initialize serial communications at 9600 bps
  Serial.begin(9600);
  lightSensor.lightOn();
}


/**
 * \par Function
 *    loop
 * \par Description
 *    Run continuously, print light sensor's DAC value .
 * \param[in]
 *    None
 * \par Output
 *    None
 * \return
 *    None.
 * \par Others
 *    None
 */
void loop()
{
  // read the lightSensor value:
  value = lightSensor.read();

  // print the results to the serial monitor:
  Serial.print("value = ");
  Serial.println(value);
  // wait 100 milliseconds before the next loop
  delay(100);
}
