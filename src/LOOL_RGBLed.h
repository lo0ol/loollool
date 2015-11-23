/**
 * @par Copyright (C), 2012-2015, loollool
 * @class LOOL_RGBLed
 * @brief    Driver for W2812 full-color LED lights.
 * @file    LOOL_RGBLed.h
 * @author  sean
 * @version V1.0.0
 * @date    2015/11/18
 * @brief   Header for LOOL_RGBLed.cpp module
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
 * this file is a drive for WS2811/2812 full-color LED lights, It supports
 * W2812B full-color LED lights device provided by the loollool.
 *
 * @par Method List:
 *
 *    1. void LOOL_RGBLed::reset(uint8_t port)
 *    2. void LOOL_RGBLed::reset(uint8_t port,uint8_t slot)
 *    3. void LOOL_RGBLed::setpin(uint8_t port)
 *    4. uint8_t LOOL_RGBLed::getNumber()
 *    5. cRGB LOOL_RGBLed::getColorAt(uint8_t index)
 *    6. bool LOOL_RGBLed::setColorAt(uint8_t index, uint8_t red, uint8_t green, uint8_t blue)
 *    7. bool LOOL_RGBLed::setColor(uint8_t index, uint8_t red, uint8_t green, uint8_t blue)
 *    8. bool LOOL_RGBLed::setColor(uint8_t red, uint8_t green, uint8_t blue)
 *    9. bool LOOL_RGBLed::setColor(uint8_t index, long value)
 *    10. void LOOL_RGBLed::show()
 *
 * @par History:
 * <pre>
 * `<Author>`         `<Time>`        `<Version>`        `<Descr>`
 * sean         2015/11/18     1.0.0            Rebuild the old lib.
 * </pre>
 *
 */
#ifndef LOOL_RGBLed_h
#define LOOL_RGBLed_h
#include <stdint.h>
#include <stdbool.h>
#include <arduino.h>
#include "LOOL_Config.h"

#ifdef LOOL_PORT_DEFINED
#include "LOOL_Port.h"
#endif // LOOL_PORT_DEFINED

#define DEFAULT_MAX_LED_NUMBER  (32)

/// @brief Class for RGB Led Module
struct cRGB
{
  uint8_t g;
  uint8_t r;
  uint8_t b;
};

/**
 * Class: LOOL_RGBLed
 *
 * @par Description
 * Declaration of Class LOOL_RGBLed
 */
#ifndef LOOL_PORT_DEFINED
class LOOL_RGBLed
#else // !LOOL_PORT_DEFINED
class LOOL_RGBLed : public LOOL_Port
#endif // !LOOL_PORT_DEFINED
{
public:
#ifdef LOOL_PORT_DEFINED
/**
 * Alternate Constructor which can call your own function to map the LOOL_RGBLed to arduino port,
 * no pins are used or initialized here, it only assigned the LED display buffer. The default
 *number of light strips is 32.
 * param[in]
 *   None
 */
  LOOL_RGBLed(void);

/**
 * Alternate Constructor which can call your own function to map the LOOL_RGBLed to arduino port,
 * it will assigned the LED display buffer and initialization the GPIO of LED lights. The slot2
 * will be used here, and the default number of light strips is 32.
 * param[in]
 *   port - RJ25 port from PORT_1 to M2
 */
  LOOL_RGBLed(uint8_t port);

/**
 * Alternate Constructor which can call your own function to map the LOOL_RGBLed to arduino port,
 * it will assigned the LED display buffer and initialization the GPIO of LED lights. The slot2
 * will be used here, you can reset the LED number by this constructor.
 * param[in]
 *   port - RJ25 port from PORT_1 to M2
 * param[in]
 *   led_num - The LED number
 */
  LOOL_RGBLed(uint8_t port, uint8_t led_num);

/**
 * Alternate Constructor which can call your own function to map the LOOL_RGBLed to arduino port,
 * it will assigned the LED display buffer and initialization the GPIO of LED lights. You can
 * set any slot for the LED data PIN, and reset the LED number by this constructor.
 * param[in]
 *   port - RJ25 port from PORT_1 to M2
 * param[in]
 *   slot - SLOT1 or SLOT2
 * param[in]
 *   led_num - The LED number
 */

  LOOL_RGBLed(uint8_t port, uint8_t slot, uint8_t led_num);
#else //LOOL_PORT_DEFINED
/**
 * Alternate Constructor which can call your own function to map the LOOL_RGBLed to arduino port,
 * it will assigned the LED display buffer and initialization the GPIO of LED lights. You can
 * set any arduino digital pin for the LED data PIN, The default number of light strips is 32.
 * param[in]
 *   port - arduino port
 */
  LOOL_RGBLed(uint8_t port);

/**
 * Alternate Constructor which can call your own function to map the LOOL_RGBLed to arduino port,
 * it will assigned the LED display buffer and initialization the GPIO of LED lights. You can
 * set any slot for the LED data PIN, and reset the LED numberby this constructor.
 * param[in]
 *   port - arduino port
 * param[in]
 *   led_num - The LED number
 */
  LOOL_RGBLed(uint8_t port, uint8_t led_num);
#endif //LOOL_PORT_DEFINED
/**
 * Destructor which can call your own function, it will release the LED buffer
 */
  ~LOOL_RGBLed(void);

#ifdef LOOL_PORT_DEFINED
/**
 * @par Function 
 *   reset
 * @par Description
 *   Reset the LED available data PIN by its RJ25 port, and slot2 will be used as default.
 * param[in]
 *   port - RJ25 port from PORT_1 to M2
 * @par Output
 *   None
 * return
 *   None
 * @par Others
 *   None
 */
  void reset(uint8_t port);

/**
 * @par Function
 *   reset
 * @par Description
 *   Reset the LED available data PIN by its RJ25 port and slot.
 * param[in]
 *   port - RJ25 port from PORT_1 to M2
 * param[in]
 *   slot - SLOT1 or SLOT2
 * @par Output
 *   None
 * return
 *   None
 * @par Others
 *   None
 */
  void reset(uint8_t port,uint8_t slot);
#endif //LOOL_PORT_DEFINED
/**
 * @par Function
 *   setpin
 * @par Description
 *   Reset the LED available data PIN by its arduino port.
 * param[in]
 *   port - arduino port(should digital pin)
 * @par Output
 *   None
 * return
 *   None
 * @par Others
 *   None
 */
  void setpin(uint8_t port);

/**
 * @par Function
 *   getNumber
 * @par Description
 *   Get the LED number you can light it.
 * @par Output
 *   None
 * return
 *   The total number of LED's
 * @par Others
 *   The index value from 1 to the max
 */
  uint8_t getNumber(void);

/**
 * @par Function
 *   getColorAt
 * @par Description
 *   Get the LED color value from its index
 * param[in]
 *   index - The LED index number you want to read its value
 * @par Output
 *   None
 * return
 *   The LED color value, include the R,G,B
 * @par Others
 *   The index value from 1 to the max
 */
  cRGB getColorAt(uint8_t index);

/**
 * @par Function
 *   setColorAt
 * @par Description
 *   Set the LED color for any LED.
 * param[in]
 *   index - The LED index number you want to set its color
 * param[in]
 *   red - Red values
 * param[in]
 *   green - green values
 * param[in]
 *   blue - blue values
 * @par Output
 *   None
 * return
 *   TRUE: Successful implementation
 *   FALSE: Wrong execution
 * @par Others
 *   The index value from 0 to the max.
 */
bool setColorAt(uint8_t index, uint8_t red, uint8_t green, uint8_t blue);

/**
 * @par Function
 *   setColor
 * @par Description
 *   Set the LED color for any LED.
 * param[in]
 *   index - The LED index number you want to set its color
 * param[in]
 *   red - Red values
 * param[in]
 *   green - green values
 * param[in]
 *   blue - blue values
 * @par Output
 *   None
 * return
 *   TRUE: Successful implementation
 *   FALSE: Wrong execution
 * @par Others
 *   The index value from 1 to the max, if you set the index 0, all the LED will be lit
 */
  bool setColor(uint8_t index, uint8_t red, uint8_t green, uint8_t blue);

/**
 * @par Function
 *   setColor
 * @par Description
 *   Set the LED color for all LED.
 * param[in]
 *   red - Red values
 * param[in]
 *   green - green values
 * param[in]
 *   blue - blue values
 * @par Output
 *   None
 * return
 *   TRUE: Successful implementation
 *   FALSE: Wrong execution
 * @par Others
 *   All the LED will be lit.
 */
  bool setColor(uint8_t red, uint8_t green, uint8_t blue);

/**
 * @par Function
 *   setColor
 * @par Description
 *   Set the LED color for any LED.
 * param[in]
 *   value - the LED color defined as long type, for example (white) = 0xFFFFFF
 * @par Output
 *   None
 * return
 *   TRUE: Successful implementation
 *   FALSE: Wrong execution
 * @par Others
 *   The index value from 1 to the max, if you set the index 0, all the LED will be lit
 */
  bool setColor(uint8_t index, long value);

/**
 * @par Function
 *   show
 * @par Description
 *   Transmission the data to WS2812
 * @par Output
 *   None
 * return
 *   None
 * @par Others
 *   None
 */
  void show(void);

private:
  uint16_t count_led;
  uint8_t *pixels;

/**
 * @par Function
 *   rgbled_sendarray_mask
 * @par Description
 *   Set the LED color for any LED.
 * param[in]
 *   *data - the LED color store memory address
 * param[in]
 *   datlen - the data length need to be transmitted.
 * param[in]
 *   maskhi - the gpio pin mask
 * param[in]
 *   *port - the gpio port address
 * @par Output
 *   None
 * return
 *   TRUE: Successful implementation
 *   FALSE: Wrong execution
 * @par Others
 *   None
 */
  void rgbled_sendarray_mask(uint8_t *array, uint16_t length, uint8_t pinmask, uint8_t *port);

/**
 * @par Function
 *   setNumber
 * @par Description
 *   Assigned the LED display buffer by the LED number
 * param[in]
 *   num_leds - The LED number you used
 * @par Output
 *   None
 * return
 *   None
 * @par Others
 *   None
 */
  void setNumber(uint8_t num_led);

  const volatile uint8_t *ws2812_port;
  volatile uint8_t *ws2812_port_reg;
  uint8_t pinMask;
};
#endif
