/**
 * @par Copyright (C), 2012-2015, loollool
 * @class   LOOL_4Button
 * @brief    Driver for LOOL 4 Button module.
 * @file    LOOL_4Button.h
 * @author  sean
 * @version V1.0.0
 * @date    2015/08/31
 * @brief   Header for  4Button  module
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
 * This file is the drive for 4 Button module, It supports
 *      LOOL-4 Button V1.0 module provided by loollool.
 * @par Method List:
 *
 *    1.  void    LOOL_4Button::setpin(uint8_t port);
 *    2.  uint8_t LOOL_4Button::pressed();
 *
 * @par History:
 * <pre>
 * `<Author>`         `<Time>`        `<Version>`        `<Descr>`
 * sean         2015/11/18     1.0.0            Rebuild the old lib.
 * </pre>
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef LOOL_4Button_H
#define LOOL_4Button_H

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stdbool.h>
#include <arduino.h>
#include "LOOL_Config.h"

#ifdef LOOL_PORT_DEFINED
#include "LOOL_Port.h"
#endif //  LOOL_PORT_DEFINED

/* Exported macro ------------------------------------------------------------*/
#define KEY_NULL   (0)
#define KEY_1      (1)
#define KEY_2      (2)
#define KEY_3      (3)
#define KEY_4      (4)

#define KEY_NULL_VALUE   (962)     // 1023*((5-0.3)/5)
#define KEY_1_VALUE      (0)
#define KEY_2_VALUE      (481)     // 962/2
#define KEY_3_VALUE      (641)     // 962*2/3
#define KEY_4_VALUE      (721)     // 962*3/4

#define DEBOUNCED_INTERVAL (8)
// If you want key response faster, you can set DEBOUNCED_INTERVAL to a
// smaller number.

#define FALSE  (0)
#define TRUE   (1)

/**
 * Class: LOOL_4Button
 * @par Description
 * Declaration of Class LOOL_4Button
 */
#ifndef LOOL_PORT_DEFINED
class LOOL_4Button
#else // !LOOL_PORT_DEFINED
class LOOL_4Button : public LOOL_Port
#endif // !LOOL_PORT_DEFINED
{
public:
#ifdef LOOL_PORT_DEFINED
/**
 *  Alternate Constructor which can call your own function to map the LOOL_4Button to arduino port, \n
 *  no pins are used or initialized here.
 * param[in]
 *    None
 */
  LOOL_4Button(void);
  
/**
 *  Alternate Constructor which can call your own function to map the LOOL_4Button to arduino port, \n
 *  the slot2 pin will be used for key pin.
 * param[in]
 *    port - RJ25 port from PORT_1 to M2
 */
  LOOL_4Button(uint8_t port);
#else //  LOOL_PORT_DEFINED
/**
 * Alternate Constructor which can call your own function to map the _KeyPin to arduino port,
 * param[in]
 *    port - arduino gpio number
 */
  LOOL_4Button(uint8_t port);
#endif  //  LOOL_PORT_DEFINED
/**
 * @par Function
 *    setpin
 * @par Description
 *    Set the PIN for button module.
 * param[in]
 *    port - arduino gpio number
 * @par Output
 *    None
 * return
 *    None
 * @par Others
 *    None
 */
  void setpin(uint8_t port);

/**
 * @par Function
 *    pressed
 * @par Description
 *    Read key ADC value to a variable.
 * param[in]
 *    None
 * @par Output
 *    None
 * return
 *    Return the key vlaue, the value maybe  KEY_1,KEY_2,KEY_3,KEY_4,KEY_NULL.
 * @par Others
 *    The key should periodically read, if it was delayed, It will affect the sensitivity of the keys
 */
  uint8_t pressed(void);
private:
  static volatile unsigned long previous_time;
  static volatile unsigned long key_debounced_count;
  static volatile unsigned long key_match_count;
  static volatile unsigned long key_debounced_value;
  static volatile int16_t  Pre_Button_Value;
  static volatile uint8_t  _KeyPin;
};
#endif // Me4Button_H
