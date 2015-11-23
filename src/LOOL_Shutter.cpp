/**
 * @par Copyright (C), 2012-2015, loollool
 * @class LOOL_Shutter
 * @brief    Driver for LOOL Shutter device.
 * @file    LOOL_Shutter.cpp
 * @author  sean
 * @version V1.0.0
 * @date    2015/11/18
 * @brief   Driver for LOOL Shutter device.
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
 * This file is a drive for LOOL Shutter device, It supports LOOL Shutter device
 * V1.0 provided by the loollool.
 *
 * @par Method List:
 *
 *    1. void LOOL_Shutter::setpin(uint8_t ShotPin, uint8_t FocusPin)
 *    2. uint8_t LOOL_Shutter::shotOn()
 *    3. uint8_t LOOL_Shutter::shotOff()
 *    4. uint8_t LOOL_Shutter::focusOn()
 *    5. uint8_t LOOL_Shutter::focusOff()
 *
 * @par History:
 * <pre>
 * `<Author>`         `<Time>`        `<Version>`        `<Descr>`
 * sean         2015/11/18     1.0.0            Rebuild the old lib.
 * </pre>
 *
 * @example Shutter.ino
 */
#include "LOOL_Shutter.h"

volatile uint8_t       LOOL_Shutter::_ShotPin             = 0;
volatile uint8_t       LOOL_Shutter::_FocusPin            = 0;

#ifdef LOOL_PORT_DEFINED
/**
 * Alternate Constructor which can call your own function to map the LOOL_Shutter to arduino port,
 * no pins are used or initialized here.
 * param[in]
 *   None
 */
LOOL_Shutter::LOOL_Shutter(void) : LOOL_Port(0)
{

}

/**
 * Alternate Constructor which can call your own function to map the LOOL_Shutter to arduino port,
 * and the shot and focus PIN will be set LOW
 * param[in]
 *   port - RJ25 port from PORT_1 to M2
 */
LOOL_Shutter::LOOL_Shutter(uint8_t port) : LOOL_Port(port)
{
  LOOL_Port::dWrite1(LOW);
  LOOL_Port::dWrite2(LOW);
}
#else //LOOL_PORT_DEFINED
/**
 * Alternate Constructor which can call your own function to map the LOOL_Shutter to arduino port,
 * it will assigned the shot PIN and focus pin.
 * param[in]
 *   ShotPin - arduino port for shot PIN(should digital pin)
 * param[in]
 *   FocusPin - arduino port for focus PIN(should digital pin)
 */
LOOL_Shutter::LOOL_Shutter(uint8_t ShotPin, uint8_t FocusPin)
{
  _ShotPin = ShotPin;
  _FocusPin = FocusPin;

  //set pinMode OUTPUT
  pinMode(_ShotPin, OUTPUT);
  pinMode(_FocusPin, OUTPUT);
  digitalWrite(_ShotPin, LOW);
  digitalWrite(_FocusPin, LOW);
}
#endif // LOOL_PORT_DEFINED

/**
 * @par Function
 *   setpin
 * @par Description
 *   Reset the shutter available PIN by its arduino port.
 * param[in]
 *   ShotPin - arduino port for shot PIN(should digital pin)
 * param[in]
 *   FocusPin - arduino port for focus PIN(should digital pin)
 * @par Output
 *   None
 * return
 *   None
 * @par Others
 *   None
 */
void LOOL_Shutter::setpin(uint8_t ShotPin, uint8_t FocusPin)
{
  _ShotPin = ShotPin;
  _FocusPin = FocusPin;

  //set pinMode OUTPUT
  pinMode(_ShotPin, OUTPUT);
  pinMode(_FocusPin, OUTPUT);
  digitalWrite(_ShotPin, LOW);
  digitalWrite(_FocusPin, LOW);
#ifdef LOOL_PORT_DEFINED
  s1 = _ShotPin;
  s2 = _FocusPin;
#endif
}

/**
 * @par Function
 *   shotOn
 * @par Description
 *   Set the shot PIN on
 * @par Output
 *   None
 * return
 *   None
 * @par Others
 *   None
 */
void LOOL_Shutter::shotOn(void)
{
#ifdef LOOL_PORT_DEFINED
  LOOL_Port::dWrite1(HIGH);
#else //LOOL_PORT_DEFINED
  digitalWrite(_ShotPin, HIGH);
#endif //LOOL_PORT_DEFINED
}

/**
 * @par Function
 *   shotOff
 * @par Description
 *   Set the shot PIN off
 * @par Output
 *   None
 * return
 *   None
 * @par Others
 *   None
 */
void LOOL_Shutter::shotOff(void)
{
#ifdef LOOL_PORT_DEFINED
  LOOL_Port::dWrite1(LOW);
#else //LOOL_PORT_DEFINED
  digitalWrite(_ShotPin, LOW);
#endif //LOOL_PORT_DEFINED
}

/**
 * @par Function
 *   focusOn
 * @par Description
 *   Set the focus PIN on
 * @par Output
 *   None
 * return
 *   None
 * @par Others
 *   None
 */
void LOOL_Shutter::focusOn(void)
{
#ifdef LOOL_PORT_DEFINED
  LOOL_Port::dWrite2(HIGH);
#else //LOOL_PORT_DEFINED
  digitalWrite(_FocusPin, HIGH);
#endif //LOOL_PORT_DEFINED
}

/**
 * @par Function
 *   focusOff
 * @par Description
 *   Set the focus PIN off
 * @par Output
 *   None
 * return
 *   None
 * @par Others
 *   None
 */
void LOOL_Shutter::focusOff(void)
{
#ifdef LOOL_PORT_DEFINED
  LOOL_Port::dWrite2(LOW);
#else //LOOL_PORT_DEFINED
  digitalWrite(_FocusPin, LOW);
#endif //LOOL_PORT_DEFINED
}

