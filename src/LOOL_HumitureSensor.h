/**
 * @par Copyright (C), 2012-2015, loollool
 * @class LOOL_Humiture
 * @brief    Driver for humiture sensor device.
 * @file    LOOL_HumitureSensor.h
 * @author  sean
 * @version V1.0.0
 * @date    2015/11/18
 * @brief   Header for for Humiture module
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
 * This file is a drive for humiture sensor device, It supports humiture sensor
 * provided by the loollool.
 *
 * @par Method List:
 *
 *    1. void LOOL_Humiture::setpin(uint8_t port)
 *    2. void LOOL_Humiture::update(void)
 *    3. uint8_t LOOL_Humiture::getHumidity(void)
 *    4. uint8_t LOOL_Humiture::getTemperature(void)
 *    5. uint8_t LOOL_Humiture::getValue(uint8_t index)
 *
 * @par History:
 * <pre>
 * `<Author>`         `<Time>`        `<Version>`        `<Descr>`
 * sean         2015/11/18     1.0.0            Rebuild the old lib.
 * </pre>
 */
#ifndef LOOL_HumitureSensor_H
#define LOOL_HumitureSensor_H

#include <stdint.h>
#include <stdbool.h>
#include <arduino.h>
#include "LOOL_Config.h"

#ifdef LOOL_PORT_DEFINED
#include "LOOL_Port.h"
#endif // LOOL_PORT_DEFINED

/**
 * Class: LOOL_Humiture
 * @par Description
 * Declaration of Class LOOL_Humiture.
 */
#ifndef LOOL_PORT_DEFINED  
class LOOL_Humiture
#else // !LOOL_PORT_DEFINE
class LOOL_Humiture : public LOOL_Port
#endif // !LOOL_PORT_DEFINED
{
public:
#ifdef LOOL_PORT_DEFINED
/**
 * Alternate Constructor which can call your own function to map the humiture sensor to arduino port,
 * no pins are used or initialized here.
 * param[in]
 *   None
 */
  LOOL_Humiture(void);
 
/**
 * Alternate Constructor which can call your own function to map the temperature sensor to arduino port,
 * the slot2 pin will be used here since specify slot is not be set.
 * param[in]
 *   port - RJ25 port from PORT_1 to M2
 */
  LOOL_Humiture(uint8_t port);
#else // LOOL_PORT_DEFINED
/**
 * @par Function
 *   setpin
 * @par Description
 *   Reset available PIN for temperature sensor by its arduino port.
 * param[in]
 *   port - arduino port(should digital pin)
 * @par Output
 *   None
 * return
 *   None
 * @par Others
 *   None
 */
  LOOL_Humiture(uint8_t port);
#endif // LOOL_PORT_DEFINED
  
/**
 * @par Function
 *   setpin
 * @par Description
 *   Reset available PIN for temperature sensor by its arduino port.
 * param[in]
 *   port - arduino port(should digital pin)
 * @par Output
 *   None
 * return
 *   None
 * @par Others
 *   None
 */
  void setpin(uint8_t port);
  
/**
 * @par Function
 *   update
 * @par Description
 *   Use this function to update the sensor data
 * @par Output
 *   None
 * return
 *   None
 * @par Others
 *   None
 */
  void update(void);

/**
 * @par Function
 *   getHumidity
 * @par Description
 *   Use this function to Get the Humidity data
 * @par Output
 *   None
 * return
 *   The value of Humidity
 * @par Others
 *   None
 */
  uint8_t getHumidity(void);

/**
 * @par Function
 *   getTemperature
 * @par Description
 *   Use this function to Get the Temperature data
 * @par Output
 *   None
 * return
 *   The value of Temperature
 * @par Others
 *   None
 */
  uint8_t getTemperature(void);

/**
 * @par Function
 *   getValue
 * @par Description
 *   Use this function to Get the Temperature data or Humidity data
 * param[in]
 *   index - The value '0' means get the value of Humidity data and '1' used to get the
 *   Temperature data.
 * @par Output
 *   None
 * return
 *   The value of Temperature
 * @par Others
 *   None
 */
  uint8_t getValue(uint8_t index);

private:
  uint8_t Humidity;
  uint8_t Temperature;
  static volatile uint8_t  _DataPin;
};

#endif

