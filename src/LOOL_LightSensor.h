/**
 * @par Copyright (C), 2012-2015, loollool
 * @class   LOOL_LightSensor
 * @brief    Driver for LOOL LightSensor module.
 * @file    LOOL_LightSensor.h
 * @author  sean
 * @version V1.0.0
 * @date    2015/11/18
 * @brief   Header file for LOOL Light Sensor module.
 *
 * @par Copyright
 * This software is Copyright (C), 2012-2015, loollool. Use is subject to license \n
 * conditions. The main licensing options available are GPL V2 or Commercial: \n
 *
 * @par Open Source Licensing GPL V2
 * This is the appropriate option if you want to share the source code of your \n
 * application with everyone you distribute it to, and you also want to give them \n
 * the right to share who uses it. If you wish to use this software under Open \n
 * Source Licensing, you must contribute all your source code to the open source \n
 * community in accordance with the GPL Version 2 when your application is \n
 * distributed. See http://www.gnu.org/copyleft/gpl.html
 *
 * @par Description
 *
 * @par Method List:
 *
 *    1. void    LOOL_LightSensor::setpin(uint8_t ledPin, uint8_t sensorPin)
 *    2. int16_t LOOL_LightSensor::read()
 *    3. void    LOOL_LightSensor::lightOn()
 *    4. void    LOOL_LightSensor::lightOff()
 *
 * @par History:
 * <pre>
 * `<Author>`         `<Time>`        `<Version>`        `<Descr>`
 * sean         2015/11/18     1.0.0            Rebuild the old lib.
 * </pre>
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef LOOL_LightSensor_H
#define LOOL_LightSensor_H

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stdbool.h>
#include <arduino.h>
#include "LOOL_Config.h"

#ifdef LOOL_PORT_DEFINED
#include "LOOL_Port.h"
#endif // LOOL_PORT_DEFINED

/**
 * Class: LOOL_LightSensor
 * @par Description
 * Declaration of Class LOOL_LightSensor.
 */
#ifndef LOOL_PORT_DEFINED
class LOOL_LightSensor
#else // !LOOL_PORT_DEFINED
class LOOL_LightSensor : public LOOL_Port
#endif // !LOOL_PORT_DEFINED
{
public:
#ifdef LOOL_PORT_DEFINED
/**
 * Alternate Constructor which can call your own function to map the light sensor to arduino port,
 * no pins are used or initialized here.
 * param[in]
 *   None
 */
  LOOL_LightSensor(void);

/**
 * Alternate Constructor which can call your own function to map the light sensor to arduino port
 * param[in]
 *   port - RJ25 port from PORT_1 to M2
 */
  LOOL_LightSensor(uint8_t port);
#else // LOOL_PORT_DEFINED
/**
 * Alternate Constructor which can call your own function to map the light sensor to arduino port
 * param[in]
 *   ledPin - arduino port for led input
 * param[in]
 *   sensorPin - arduino port for sensor data read
 */
  LOOL_LightSensor(uint8_t ledPin, uint8_t sensorPin);
#endif  // LOOL_PORT_DEFINED
/**
 * @par Function
 *    setpin
 * @par Description
 *    Set I2C data pin, clock pin and clear display. \n
 *    dataPin - the DATA pin for Seven-Segment LED module. \n
 *    clkPin  - the CLK pin for Seven-Segment LED module.
 * param[in]
 *    ledPin - Which pin on board that LEDpin is connecting to.
 * param[in]
 *    sensorPin - Which pin on board that sensorPin is connecting to.
 * @par Output
 *    None
 * @par Return
 *    None
 * @par Others
 *    Set global variable _KeyPin and s2
 */
  void setpin(uint8_t ledPin, uint8_t sensorPin);

/**
 * @par Function
 *    read
 * @par Description
 *    Read analog value of light sensor.
 * param[in]
 *    None
 * @par Output
 *    None
 * @par Return
 *    LOOL_Port::aRead2() - DAC value of current light sensor's output.
 * @par Others
 */
  int16_t read(void);

/**
 * @par Function
 *    lightOn
 * @par Description
 *    Turn on the LED on the light sensor.
 * param[in]
 *    None
 * @par Output
 *    None
 * @par Return
 *    None
 * @par Others
 */
  void lightOn(void);

/**
 * @par Function
 *    lightOff
 * @par Description
 *    Turn off the LED on the light sensor.
 * param[in]
 *    None
 * @par Output
 *    None
 * @par Return
 *    None
 * @par Others
 */
  void lightOff(void);
private:
  uint8_t _ledPin;
  uint8_t _sensorPin;
};

#endif // MeLightSensor_H
