/**
 * @par Copyright (C), 2012-2015, loollool
 * @class   LOOL_LimitSwitch
 * @brief    Driver for LOOL LimitSwitch module.
 * @file    LOOL_LimitSwitch.h
 * @author  sean
 * @version V1.0.0
 * @date    2015/11/18
 * @brief   Header for LOOL LimitSwitch module.
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
 *    1. void LOOL_LimitSwitch::setpin(uint8_t switchPin);
 *    2. bool LOOL_LimitSwitch::touched();
 *
 * @par History:
 * <pre>
 * `<Author>`         `<Time>`        `<Version>`        `<Descr>`
 * sean         2015/11/18     1.0.0            Rebuild the old lib.
 * </pre>
 *
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef LOOL_LimitSwitch_H
#define LOOL_LimitSwitch_H

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stdbool.h>
#include <arduino.h>
#include "LOOL_Config.h"

#ifdef LOOL_PORT_DEFINED
#include "LOOL_Port.h"
#endif // LOOL_PORT_DEFINED

/* Exported classes ----------------------------------------------------------*/
/**
 * Class: LOOL_LimitSwitch
 * @par Description
 * Declaration of Class LOOL_LimitSwitch.
 */
#ifndef LOOL_PORT_DEFINED
class LOOL_LimitSwitch
#else // !LOOL_PORT_DEFINED
class LOOL_LimitSwitch : public LOOL_Port
#endif  // !LOOL_PORT_DEFINED
{
public:
#ifdef LOOL_PORT_DEFINED
/**
 * Alternate Constructor which can call your own function to map the limit switch to arduino port,
 * no pins are used or initialized here.
 * param[in]
 *   None
 */
  LOOL_LimitSwitch(void);

/**
 * Alternate Constructor which can call your own function to map the limit switch to arduino port,
 * the slot2 will be used here.
 * param[in]
 *   port - RJ25 port from PORT_1 to M2
 */
  LOOL_LimitSwitch(uint8_t port);

/**
 * Alternate Constructor which can call your own function to map the limit switch to arduino port,
 * you can set any slot for the limit switch device. 
 * param[in]
 *   port - RJ25 port from PORT_1 to M2
 * param[in]
 *   slot - SLOT1 or SLOT2
 */
  LOOL_LimitSwitch(uint8_t port, uint8_t slot);
#else // LOOL_PORT_DEFINED
/**
 * Alternate Constructor which can call your own function to map the limit switch to arduino port,
 * param[in]
 *   switchPin - arduino port for switch detect pin.
 */
  LOOL_LimitSwitch(uint8_t switchPin);
#endif  // LOOL_PORT_DEFINED
/**
 * @par Function
 *    setpin
 * @par Description
 *    Reset the limit switch available PIN by its arduino port.
 * param[in]
 *    switchPin - arduino port for switch detect pin.
 * @par Output
 *    None
 * @par Return
 *    None
 * @par Others
 *    None
 */
  void setpin(uint8_t switchPin);

/**
 * @par Function
 *    touched
 * @par Description
 *    Get switch value from selected _slot defined by LOOL_Port.
 * param[in]
 *    None
 * @par Output
 *    None
 * \Return
 *    True if module is touched.
 * @par Others
 *    None
 */
  bool touched(void);

private:
  uint8_t _switchPin;
};
#endif
