/**
 * @par Copyright (C), 2012-2015, loollool
 * @class LOOL_UltrasonicSensor
 * @brief    Driver for LOOL ultrasonic sensor device.
 * @file    LOOL_UltrasonicSensor.h
 * @author  sean
 * @version V1.0.0
 * @date    2015/11/18
 * @brief   Header for for UltrasonicSensormodule
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
 * This file is a drive for Me ultrasonic sensor device, It supports ultrasonic sensor
 * V3.0 provided by the loollool.
 *
 * @par Method List:
 *
 *    1. void LOOL_UltrasonicSensor::setpin(uint8_t SignalPin)
 *    2. double LOOL_UltrasonicSensor::distanceCm(uint16_t MAXcm)
 *    3. double LOOL_UltrasonicSensor::distanceInch(uint16_t MAXinch)
 *    4. long LOOL_UltrasonicSensor::measure(unsigned long timeout)
 *
 * @par History:
 * <pre>
 * `<Author>`         `<Time>`        `<Version>`        `<Descr>`
 * sean         2015/11/18     1.0.0            Rebuild the old lib.
 * </pre>
 */
#ifndef MeUltrasonicSensor_H
#define MeUltrasonicSensor_H

#include <stdint.h>
#include <stdbool.h>
#include <arduino.h>
#include "LOOL_Config.h"

#ifdef LOOL_PORT_DEFINED
#include "LOOL_Port.h"
#endif // LOOL_PORT_DEFINED

/**
 * Class: LOOL_UltrasonicSensor
 * @par Description
 * Declaration of Class LOOL_UltrasonicSensor.
 */
#ifndef LOOL_PORT_DEFINED
class LOOL_UltrasonicSensor
#else // !LOOL_PORT_DEFINED
class LOOL_UltrasonicSensor : public LOOL_Port
#endif // !LOOL_PORT_DEFINED
{
public:
#ifdef LOOL_PORT_DEFINED
/**
 * Alternate Constructor which can call your own function to map the ultrasonic sensor to arduino port,
 * no pins are used or initialized here.
 * param[in]
 *   None
 */
  LOOL_UltrasonicSensor(void);

/**
 * Alternate Constructor which can call your own function to map the ultrasonic Sensor to arduino port
 * param[in]
 *   port - RJ25 port from PORT_1 to M2
 */
  LOOL_UltrasonicSensor(uint8_t port);
#else // LOOL_PORT_DEFINED
/**
 * Alternate Constructor which can call your own function to map the ultrasonic Sensor to arduino port,
 * it will assigned the signal pin.
 * param[in]
 *   port - arduino port(should analog pin)
 */
  LOOL_UltrasonicSensor(uint8_t port);
#endif // LOOL_PORT_DEFINED

/**
 * @par Function
 *   setpin
 * @par Description
 *   Reset the ultrasonic Sensor available PIN by its arduino port.
 * param[in]
 *   SignalPin - arduino port for sensor read(should analog pin)
 * @par Output
 *   None
 * return
 *   None
 * @par Others
 *   None
 */
  void setpin(uint8_t SignalPin);
  
/**
 * @par Function
 *   distanceCm
 * @par Description
 *   Centimeters return the distance
 * param[in]
 *   MAXcm - The Max centimeters can be measured, the default value is 400.
 * @par Output
 *   None
 * return
 *   The distance measurement in centimeters
 * @par Others
 *   None
 */
  double distanceCm(uint16_t = 400);

/**
 * @par Function
 *   distanceInch
 * @par Description
 *   Inch return the distance
 * param[in]
 *   MAXinch - The Max inch can be measured, the default value is 180.
 * @par Output
 *   None
 * return
 *   The distance measurement in inch
 * @par Others
 *   None
 */
  double distanceInch(uint16_t = 180);

/**
 * @par Function
 *   measure
 * @par Description
 *   To get the duration of the ultrasonic sensor
 * param[in]
 *   timeout - This value is used to define the measurement range, The
 *   default value is 30000.
 * @par Output
 *   None
 * return
 *   The duration value associated with distance
 * @par Others
 *   None
 */
  long measure(unsigned long = 30000);
private:
  static volatile uint8_t  _SignalPin;
};

#endif 

