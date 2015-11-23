/**
 * @par Copyright (C), 2012-2015, loollool
 * @class LOOL_SoundSensor
 * @brief    Driver for LOOL sound sensor device.
 * @file    LOOL_SoundSensor.cpp
 * @author  sean
 * @version V1.0.0
 * @date    2015/11/18
 * @brief   Driver for SoundSensor module.
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
 * This file is a drive for LOOL sound sensor device, It supports sound sensor
 * V1.1 provided by the loollool.
 *
 * @par Method List:
 *
 *    1. void LOOL_SoundSensor::setpin(uint8_t SoundSensorPin)
 *    2. uint8_t LOOL_SoundSensor::strength()
 *
 * @par History:
 * <pre>
 * `<Author>`         `<Time>`        `<Version>`        `<Descr>`
 * sean         2015/11/18     1.0.0            Rebuild the old lib.
 * </pre>
 *
 * @example SoundSensor.ino
 */

#include "LOOL_SoundSensor.h"

volatile uint8_t       LOOL_SoundSensor::_SoundSensorRead        = 0;

#ifdef LOOL_PORT_DEFINED
/**
 * Alternate Constructor which can call your own function to map the Sound Sensor to arduino port,
 * no pins are used or initialized here.
 * param[in]
 *   None
 */
LOOL_SoundSensor::LOOL_SoundSensor(void) : LOOL_Port(0)
{
}

/**
 * Alternate Constructor which can call your own function to map the Sound Sensor to arduino port
 * param[in]
 *   port - RJ25 port from PORT_1 to M2
 */
LOOL_SoundSensor::LOOL_SoundSensor(uint8_t port) : LOOL_Port(port)
{
}
#else // LOOL_PORT_DEFINED
/**
 * Alternate Constructor which can call your own function to map the Sound Sensor to arduino port,
 * it will assigned the output pin.
 * param[in]
 *   port - arduino port(should analog pin)
 */
LOOL_SoundSensor::LOOL_SoundSensor(uint8_t port)
{
  _SoundSensorRead = port;
}
#endif // LOOL_PORT_DEFINED

/**
 * @par Function
 *   setpin
 * @par Description
 *   Reset the Sound Sensor available PIN by its arduino port.
 * param[in]
 *   SoundSensorPin - arduino port for sensor read(should analog pin)
 * @par Output
 *   None
 * return
 *   None
 * @par Others
 *   None
 */
void LOOL_SoundSensor::setpin(uint8_t SoundSensorPin)
{
  _SoundSensorRead = SoundSensorPin;

#ifdef LOOL_PORT_DEFINED
  s2 = _SoundSensorRead;
#endif // LOOL_PORT_DEFINED
}

/**
 * @par Function
 *   strength
 * @par Description
 *   Read and return the sensor value.
 * @par Output
 *   None
 * return
 *   The sensor value of sound sensor
 * @par Others
 *   None
 */
int16_t LOOL_SoundSensor::strength(void)
{
#ifdef LOOL_PORT_DEFINED
  return(LOOL_Port::aRead2());
#else // LOOL_PORT_DEFINED
  return analogRead(_SoundSensorRead);
#endif // LOOL_PORT_DEFINED
}

