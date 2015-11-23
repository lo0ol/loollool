/**
 * @par Copyright (C), 2012-2015, loollool
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
//Instantiate class MeLightSensor
LOOL_LightSensor lightSensor(PORT_6);
//Me Light Sensor can only be connected to PORT_6, PORT_7, PORT_8 on Orion Board of Makeblock.
// lightSensor's value
int value = 0;

/* Private functions ---------------------------------------------------------*/
/**
 * \par Function
 *    setup
 * \par Description
 *    Run once, initialize serial port and reset port.
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
  // Initialize serial communication using 9600 bps
  Serial.begin(9600);
  // Reset the port of instance lightSensor to PORT_8
  lightSensor.reset(PORT_8);
  // Reset lightSensor's port to PORT_8.
}

/**
 * \par Function
 *    loop
 * \par Description
 *    Run continuously, print light sensor's DAC value.
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
  // Read the lightSensor's value
  value = lightSensor.read();

  // Print results to serial monitor
  Serial.print("value = ");
  Serial.println(value);
  // Wait 100 milliseconds before next loop
  delay(100);
}
