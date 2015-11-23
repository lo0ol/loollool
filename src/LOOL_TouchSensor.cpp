/**
 * @par Copyright (C), 2012-2015, loollool
 * @class LOOL_TouchSensor
 * @brief    Driver for LOOL touch sensor device.
 * @file    LOOL_TouchSensor.cpp
 * @author  sean
 * @version V1.0.0
 * @date    2015/11/18
 * @brief   Driver for LOOL touch sensor device.
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
 * This file is a drive for LOOL touch sensor device, It supports touch sensor
 * provided by the loollool.
 *
 * @par Method List:
 *
 *    1. void LOOL_TouchSensor::setpin(uint8_t ShotPin, uint8_t FocusPin)
 *    2. bool LOOL_TouchSensor::touched()
 *    3. void LOOL_TouchSensor::SetTogMode(uint8_t TogMode)
 *
 * @par History:
 * <pre>
 * `<Author>`         `<Time>`        `<Version>`        `<Descr>`
 * sean         2015/11/18     1.0.0            Rebuild the old lib.
 * </pre>
 *
 * @example TouchSensorTest.ino
 */

#include "LOOL_TouchSensor.h"

volatile uint8_t       LOOL_TouchSensor::_TogPin             = 0;
volatile uint8_t       LOOL_TouchSensor::_OutputPin          = 0;

#ifdef LOOL_PORT_DEFINED
/**
 * Alternate Constructor which can call your own function to map the touch Sensor to arduino port,
 * no pins are used or initialized here.
 * param[in]
 *   None
 */
LOOL_TouchSensor::LOOL_TouchSensor(void) : LOOL_Port(0)
{

}

/**
 * Alternate Constructor which can call your own function to map the touch Sensor to arduino port
 * param[in]
 *   port - RJ25 port from PORT_1 to M2
 */
LOOL_TouchSensor::LOOL_TouchSensor(uint8_t port) : LOOL_Port(port)
{

}
#else // LOOL_PORT_DEFINED
/**
 * Alternate Constructor which can call your own function to map the touch Sensor to arduino port,
 * it will assigned the TogPin PIN and OutputPin pin.
 * param[in]
 *   TogPin - arduino port for output type option pin(should digital pin)
 * param[in]
 *   OutputPin - arduino port for output pin(should digital pin)
 */
LOOL_TouchSensor::LOOL_TouchSensor(uint8_t TogPin, uint8_t OutputPin)
{
  _TogPin = TogPin;
  _OutputPin = OutputPin;
  pinMode(_TogPin,OUTPUT);
  pinMode(_OutputPin,INPUT);
}
#endif // LOOL_PORT_DEFINED

/**
 * @par Function
 *   setpin
 * @par Description
 *   Reset the touch Sensor available PIN by its arduino port.
 * param[in]
 *   TogPin - arduino port for output type option pin(should digital pin)
 * param[in]
 *   OutputPin - arduino port for output pin(should digital pin)
 * @par Output
 *   None
 * return
 *   None
 * @par Others
 *   None
 */
void LOOL_TouchSensor::setpin(uint8_t TogPin, uint8_t OutputPin)
{
  _TogPin = TogPin;
  _OutputPin = OutputPin;
  pinMode(_TogPin,OUTPUT);
  pinMode(_OutputPin,INPUT);
#ifdef LOOL_PORT_DEFINED
  s1 = _TogPin;
  s2 = _OutputPin;
#endif // LOOL_PORT_DEFINED
}

/**
 * @par Function
 *   touched
 * @par Description
 *   Read and return the output signal.
 * @par Output
 *   None
 * return
 *   The output signal of touch sensor
 * @par Others
 *   None
 */
bool LOOL_TouchSensor::touched(void)
{
#ifdef LOOL_PORT_DEFINED
  return(LOOL_Port::dRead2());
#else // LOOL_PORT_DEFINED
  return(digitalRead(_OutputPin))
#endif // LOOL_PORT_DEFINED
}

/**
 * @par Function
 *   SetTogMode
 * @par Description
 *   Set the output type.
 * param[in]
 *   TogMode - 1=> Toggle mode; 0(default)=>Direct mode
 * @par Output
 *   None
 * return
 *   None
 * @par Others
 *   None
 */
void LOOL_TouchSensor::SetTogMode(uint8_t TogMode)
{
#ifdef LOOL_PORT_DEFINED
  LOOL_Port::dWrite1(TogMode);
#else // LOOL_PORT_DEFINED
  digitalWrite(_TogPin,TogMode);
#endif // LOOL_PORT_DEFINED
}


