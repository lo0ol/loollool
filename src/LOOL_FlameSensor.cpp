/**
 * @par Copyright (C), 2012-2015, loollool
 * @class LOOL_FlameSensor
 * @brief    Driver for lool flame snesor device.
 * @file    LOOL_FlameSensor.cpp
 * @author  sean
 * @version V1.0.0
 * @date    2015/09/09
 * @brief   Driver for lool flame snesor device.
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
 * This file is a drive for flame snesor device.
 *
 * @par Method List:
 *
 *    1. void LOOL_FlameSensor::setpin(uint8_t digital_pin,uint8_t analog_pin)
 *    2. uint8_t LOOL_FlameSensor::readDigital(void)
 *    3. int16_t LOOL_FlameSensor::readAnalog(void)
 *
 * @par History:
 * <pre>
 * `<Author>`         `<Time>`        `<Version>`        `<Descr>`
 * sean         2015/09/09     1.0.0            Rebuild the old lib.
 * </pre>
 *
 * @example LOOL_FlameSensorTest.ino
 */
#include "LOOL_FlameSensor.h"

volatile uint8_t       LOOL_FlameSensor::_digital_pin    = 0;
volatile uint8_t       LOOL_FlameSensor::_analog_pin     = 0;

#ifdef LOOL_PORT_DEFINED
/**
 * Alternate Constructor which can call your own function to map the flame snesor to arduino port,
 * no pins are used or initialized here.
 * param[in]
 *   None
 */
LOOL_FlameSensor::LOOL_FlameSensor(void) : LOOL_Port(0)
{

}

/**
 * Alternate Constructor which can call your own function to map the flame snesor to arduino port
 * param[in]
 *   port - RJ25 port from PORT_1 to M2
 */
LOOL_FlameSensor::LOOL_FlameSensor(uint8_t port) : LOOL_Port(port)
{

}
#else // LOOL_PORT_DEFINED
/**
 * Alternate Constructor which can call your own function to map the flame snesor to arduino port,
 * it will assigned the input pin for flame snesor.
 * param[in]
 *   digital_pin - arduino port for digital signal input
 * param[in]
 *   analog_pin - arduino port for analog signal input
 */
LOOL_FlameSensor::LOOL_FlameSensor(uint8_t digital_pin,uint8_t analog_pin)
{
  _digital_pin = digital_pin;
  _analog_pin = analog_pin;
  pinMode(_digital_pin, INPUT);
}
#endif // LOOL_PORT_DEFINED
/**
 * @par Function
 *   setpin
 * @par Description
 *   Reset the flame snesor available PIN by its arduino port.
 * param[in]
 *   digital_pin - arduino port for digital signal input
 * param[in]
 *   analog_pin - arduino port for analog signal input
 * @par Output
 *   None
 * return
 *   None
 * @par Others
 *   None
 */
void LOOL_FlameSensor::setpin(uint8_t digital_pin,uint8_t analog_pin)
{
  _digital_pin = digital_pin;
  _analog_pin = analog_pin;
  pinMode(_digital_pin, INPUT);
#ifdef LOOL_PORT_DEFINED
  s1 = _analog_pin;
  s2 = _digital_pin;
#endif // LOOL_PORT_DEFINED
}

/**
 * @par Function
 *   readDigital
 * @par Description
 *   Read the digital signal of flame snesor, It is the result of comparison between the threshold
 *   value and the analog output. The threshold value can be adjusted using a rheostat
 * @par Output
 *   None
 * return
 *   true - The fire is detected \n
 *   false - No fire is detected
 * @par Others
 *   None
 */
uint8_t LOOL_FlameSensor::readDigital(void)
{
#ifdef LOOL_PORT_DEFINED
  return( LOOL_Port::dRead2() );
#else //LOOL_PORT_DEFINED
  return digitalRead(_digital_pin);
#endif //LOOL_PORT_DEFINED
}

/**
 * @par Function
 *   readAnalog
 * @par Description
 *   Read the analog signal of flame snesor.
 * @par Output
 *   None
 * return
 *   The vlaue from flame snesor's analog output
 * @par Others
 *   None
 */
int16_t LOOL_FlameSensor::readAnalog(void)
{
#ifdef LOOL_PORT_DEFINED
  return( LOOL_Port::aRead1() );
#else //LOOL_PORT_DEFINED
  return analogRead(_analog_pin);
#endif //LOOL_PORT_DEFINED
}
