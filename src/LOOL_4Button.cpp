/**
 * @par Copyright (C), 2012-2015, loollool
 * @class   LOOL_4Button
 * @brief    Driver for LOOL 4 Button module.
 * @file    LOOL_4Button.cpp
 * @author  sean
 * @version V1.0.0
 * @date    2015/11/18
 * @brief   Driver for LOOL 4 Button module
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
 * This file is a drive for 4 Button module, It supports LOOL-4 Button V1.0 device provided 
 * by loollool.
 *
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
 *
 * @example Me4ButtonTest.ino
 */

/* Includes ------------------------------------------------------------------*/
#include "LOOL_4Button.h"

/* Private variables ---------------------------------------------------------*/
volatile unsigned long LOOL_4Button::previous_time       = 0;
volatile unsigned long LOOL_4Button::key_debounced_count = 0;
volatile unsigned long LOOL_4Button::key_match_count     = 0;
volatile unsigned long LOOL_4Button::key_debounced_value = 0;
volatile int16_t       LOOL_4Button::Pre_Button_Value    = 0;
volatile uint8_t       LOOL_4Button::_KeyPin             = 0;

/* Private functions ---------------------------------------------------------*/
#ifdef LOOL_PORT_DEFINED

/**
 *  Alternate Constructor which can call your own function to map the LOOL_4Button to arduino port, \n
 *  no pins are used or initialized here.
 * param[in]
 *    None
 */
LOOL_4Button::LOOL_4Button(void) : LOOL_Port()
{

}

/**
 *  Alternate Constructor which can call your own function to map the LOOL_4Button to arduino port, \n
 *  the slot2 pin will be used for key pin.
 * param[in]
 *    port - RJ25 port from PORT_1 to M2
 */
LOOL_4Button::LOOL_4Button(uint8_t port) : LOOL_Port()
{
  _KeyPin = s2;
}
#else  // LOOL_PORT_DEFINED

/**
 * Alternate Constructor which can call your own function to map the _KeyPin to arduino port,
 * param[in]
 *    port - arduino gpio number
 */
LOOL_4Button::LOOL_4Button(uint8_t port)
{
  _KeyPin = port;
}
#endif // LOOL_PORT_DEFINED

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
void LOOL_4Button::setpin(uint8_t port)
{
  _KeyPin = port;
#ifdef LOOL_PORT_DEFINED
  s2 = port;
#endif // LOOL_PORT_DEFINED
}

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
uint8_t LOOL_4Button::pressed(void)
{
  uint8_t returnKey      = KEY_NULL;
  int16_t key_temp_value = KEY_NULL;
  int16_t button_key_val = Pre_Button_Value;
  uint32_t current_time  = 0;
  // current_time will be return to 0 after about 50 days
  // 2E32 / (float)(24*3600*1000) = 49.71026
  current_time = millis();
  if (current_time - previous_time > DEBOUNCED_INTERVAL)
  {
    // This statement will handle rollover itself, see more in arduino site.
    // http://playground.arduino.cc/Code/TimingRollover
    // If you want key resbonse faster, you can set DEBOUNCED_INTERVAL to a
    // smaller number in LOOL_4Button.h.
    previous_time = current_time;
#ifdef LOOL_PORT_DEFINED
    key_temp_value = LOOL_Port::aRead2();
#else  // LOOL_PORT_DEFINED
    key_temp_value = analogRead(_KeyPin);
#endif // LOOL_PORT_DEFINED
    if (key_debounced_count == 0)
    {
      key_debounced_value = key_temp_value;
    }
    if (abs(key_temp_value - key_debounced_value) < 20)
    {
      key_match_count++;
    }
    key_debounced_count++;
  }

  if (key_debounced_count == 5)
  {
    key_debounced_count = 0;
    if (key_match_count > 2)
    {
      button_key_val = key_debounced_value;
      Pre_Button_Value = button_key_val;
    }
    else
    {
      button_key_val = Pre_Button_Value;
    }
    key_match_count = 0;
  }

  button_key_val = button_key_val / 100;
  // Division is slow in 8bit MCU, division should be replaced with right shift.
  switch (button_key_val)
  {
    case 3:
      returnKey = KEY_1;
      break;


    case 5:
      returnKey = KEY_2;
      break;

    case 6:
      returnKey = KEY_3;
      break;

    case 7:
      returnKey = KEY_4;
      break;

    case 9:
    case 10:
      returnKey = KEY_NULL;
      break;
  }
  return(returnKey);
}

