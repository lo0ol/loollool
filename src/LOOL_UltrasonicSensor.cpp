/**
 * @par Copyright (C), 2012-2015, loollool
 * @class LOOL_UltrasonicSensor
 * @brief    Driver for LOOL ultrasonic sensor device.
 * @file    LOOL_UltrasonicSensor.cpp
 * @author  sean
 * @version V1.0.0
 * @date    2015/11/18
 * @brief   Driver for LOOL ultrasonic sensor device.
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
 * This file is a drive for LOOL ultrasonic sensor device, It supports ultrasonic sensor
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
 *
 * @example UltrasonicSensorTest.ino
 */
#include "LOOL_UltrasonicSensor.h"

volatile uint8_t       LOOL_UltrasonicSensor::_SignalPin        = 0;

#ifdef LOOL_PORT_DEFINED
/**
 * Alternate Constructor which can call your own function to map the ultrasonic sensor to arduino port,
 * no pins are used or initialized here.
 * param[in]
 *   None
 */
LOOL_UltrasonicSensor::LOOL_UltrasonicSensor(void) : LOOL_Port(0)
{

}

/**
 * Alternate Constructor which can call your own function to map the ultrasonic Sensor to arduino port
 * param[in]
 *   port - RJ25 port from PORT_1 to M2
 */
LOOL_UltrasonicSensor::LOOL_UltrasonicSensor(uint8_t port) : LOOL_Port(port)
{

}
#else // LOOL_PORT_DEFINED
/**
 * Alternate Constructor which can call your own function to map the ultrasonic Sensor to arduino port,
 * it will assigned the signal pin.
 * param[in]
 *   port - arduino port(should analog pin)
 */
LOOL_UltrasonicSensor::LOOL_UltrasonicSensor(uint8_t port)
{
  _SignalPin = port;
}
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
void LOOL_UltrasonicSensor::setpin(uint8_t SignalPin)
{
  _SignalPin = SignalPin;
#ifdef LOOL_PORT_DEFINED
  s2 = _SignalPin;
#endif // LOOL_PORT_DEFINED
}

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
double LOOL_UltrasonicSensor::distanceCm(uint16_t MAXcm)
{
  long distance = measure(MAXcm * 55 + 200);
  return( (double)distance / 58.0);
}

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
double LOOL_UltrasonicSensor::distanceInch(uint16_t MAXinch)
{
  long distance = measure(MAXinch * 145 + 200);
  return( (double)(distance / 148.0) );
}

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
long LOOL_UltrasonicSensor::measure(unsigned long timeout)
{
  long duration;
  LOOL_Port::dWrite2(LOW);
  delayMicroseconds(2);
  LOOL_Port::dWrite2(HIGH);
  delayMicroseconds(10);
  LOOL_Port::dWrite2(LOW);
  pinMode(s2, INPUT);
  duration = pulseIn(s2, HIGH, timeout);
  return(duration);
}

