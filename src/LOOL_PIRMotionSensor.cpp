/**
 * @par Copyright (C), 2012-2015, loollool
 * @class   LOOL_PIRMotionSensor
 * @brief    Driver for LOOL PIR Motion Sensor module.
 * @file    LOOL_PIRMotionSensor.cpp
 * @author  sean
 * @version V1.0.0
 * @date    2015/11/18
 * @brief   Driver for LOOL PIR Motion Sensor module.
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
 *    1. void    LOOL_PIRMotionSensor::setpin(uint8_t ModePin,uint8_t SensorPin)
 *    2. void    LOOL_PIRMotionSensor::SetPirMotionMode(uint8_t ModePin)
 *    3. bool    LOOL_PIRMotionSensor::isHumanDetected();
 *
 * @par History:
 * <pre>
 * `<Author>`         `<Time>`        `<Version>`        `<Descr>`
 * sean         2015/11/18     1.0.0            Rebuild the old lib.
 * </pre>
 *
 * @example PIRMotionSensorTest.ino
 */

/* Includes ------------------------------------------------------------------*/
#include "LOOL_PIRMotionSensor.h"

volatile uint8_t       LOOL_PIRMotionSensor::_SensorPin        = 0;
volatile uint8_t       LOOL_PIRMotionSensor::_ModePin          = 0;

/* Private functions ---------------------------------------------------------*/

/**
 * Alternate Constructor which can call your own function to map the Motion Sensor device to arduino port,
 * no pins are used or initialized here.
 * param[in]
 *   None
 */
#ifdef LOOL_PORT_DEFINED
LOOL_PIRMotionSensor::LOOL_PIRMotionSensor(void) : LOOL_Port(0)
{

}

/**
 * Alternate Constructor which can call your own function to map the Motion Sensor device to arduino port
 * param[in]
 *   port - RJ25 port from PORT_1 to M2
 */
LOOL_PIRMotionSensor::LOOL_PIRMotionSensor(uint8_t port) : LOOL_Port(port)
{

}
#else // LOOL_PORT_DEFINED
/**
 * Alternate Constructor which can call your own function to map the Motion Sensor device to arduino port
 * param[in]
 *   ModePin - arduino port for BIS0001's A port
 * param[in]
 *   SensorPin - arduino port for BIS0001's Vo port
 */
LOOL_PIRMotionSensor::LOOL_PIRMotionSensor(uint8_t ModePin,uint8_t SensorPin)
{
  _ModePin = ModePin;
  _SensorPin = SensorPin;
  pinMode(_ModePin, OUTPUT);
  pinMode(_sensorPin, INPUT);
}
#endif // LOOL_PORT_DEFINED

/**
 * @par Function
 *    setpin
 * @par Description
 *    Reset the PIR motion sensor available PIN by its arduino port.
 * param[in]
 *   ModePin - arduino port for BIS0001's A port
 * param[in]
 *   SensorPin - arduino port for BIS0001's Vo port
 * @par Output
 *    None
 * @par Return
 *    None
 * @par Others
 *    Set global variable _KeyPin and s2
 */
void LOOL_PIRMotionSensor::setpin(uint8_t ModePin,uint8_t SensorPin)
{
  _ModePin = ModePin;
  _SensorPin = SensorPin;
  pinMode(_ModePin, OUTPUT);
  pinMode(_SensorPin, INPUT);
#ifdef LOOL_PORT_DEFINED
  s1 = _ModePin;
  s2 = _SensorPin;
#endif // LOOL_PORT_DEFINED
}

/**
 * @par Function
 *    SetPirMotionMode
 * @par Description
 *    Set PIR motion sensor's trigger mode.
 * param[in]
 *    ModePin - 1: Retriggerable,   0: Unrepeatable trigger
 * @par Output
 *    None
 * @par Return
 *    None
 * @par Others
 *    None
 */
void LOOL_PIRMotionSensor::SetPirMotionMode(uint8_t ModePin)
{
#ifdef LOOL_PORT_DEFINED
  LOOL_Port::dWrite1(ModePin);
#else // LOOL_PORT_DEFINED
  digitalWrite(_ModePin, ModePin);
#endif // LOOL_PORT_DEFINED
}

/**
 * @par Function
 *    isHumanDetected
 * @par Description
 *    Is human been detected.
 * param[in]
 *    None
 * @par Output
 *    None
 * @par Return
 *    ture: human is detected 
 *    false: no human been detected 
 * @par Others
 *    None
 */
bool LOOL_PIRMotionSensor::isHumanDetected()
{
#ifdef LOOL_PORT_DEFINED
  return(LOOL_Port::dRead2());
#else // LOOL_PORT_DEFINED
  return digitalRead(_SensorPin);
#endif // LOOL_PORT_DEFINED
}

