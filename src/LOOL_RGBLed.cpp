/**
 * @par Copyright (C), 2012-2015, loollool
 * @class LOOL_RGBLed
 * @brief    Driver for W2812 full-color LED.
 * @file    LOOL_RGBLed.cpp
 * @author  sean
 * @version V1.0.0
 * @date    2015/11/18
 * @brief   Driver for W2812 full-color LED lights
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
 * This file is a drive for WS2811/2812 full-color LED lights, It supports
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
 * @example ColorLoopTest.ino
 * @example IndicatorsTest.ino
 * @example WhiteBreathLightTest.ino
 */
#include "LOOL_RGBLed.h"

#ifdef LOOL_PORT_DEFINED
/**
 * Alternate Constructor which can call your own function to map the LOOL_RGBLed to arduino port,
 * no pins are used or initialized here, it only assigned the LED display buffer. The default
 *number of light strips is 32.
 * param[in]
 *   None
 */
LOOL_RGBLed::LOOL_RGBLed(void) : LOOL_Port()
{
  setNumber(DEFAULT_MAX_LED_NUMBER);
}

/**
 * Alternate Constructor which can call your own function to map the LOOL_RGBLed to arduino port,
 * it will assigned the LED display buffer and initialization the GPIO of LED lights. The slot2
 * will be used here, and the default number of light strips is 32.
 * param[in]
 *   port - RJ25 port from PORT_1 to M2
 */
LOOL_RGBLed::LOOL_RGBLed(uint8_t port) : LOOL_Port(port)
{
  pinMask       = digitalPinToBitMask(s2);
  ws2812_port   = portOutputRegister(digitalPinToPort(s2) );
  //set pinMode OUTPUT
  pinMode(s2, OUTPUT);
  setNumber(DEFAULT_MAX_LED_NUMBER);
}

/**
 * Alternate Constructor which can call your own function to map the LOOL_RGBLed to arduino port,
 * it will assigned the LED display buffer and initialization the GPIO of LED lights. The slot2
 * will be used here, you can reset the LED number by this constructor.
 * param[in]
 *   port - RJ25 port from PORT_1 to M2
 * param[in]
 *   led_num - The LED number
 */
LOOL_RGBLed::LOOL_RGBLed(uint8_t port, uint8_t led_num) : LOOL_Port(port)
{
  pinMask       = digitalPinToBitMask(s2);
  ws2812_port   = portOutputRegister(digitalPinToPort(s2) );
  //set pinMode OUTPUT */
  pinMode(s2, OUTPUT);
  setNumber(led_num);
}

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
LOOL_RGBLed::LOOL_RGBLed(uint8_t port, uint8_t slot, uint8_t led_num) : LOOL_Port(port)
{
  if(slot == SLOT1)
  {
    pinMask     = digitalPinToBitMask(s1);
    ws2812_port = portOutputRegister(digitalPinToPort(s1) );
    // set pinMode OUTPUT */
    pinMode(s1, OUTPUT);
  }
  else
  {
    pinMask     = digitalPinToBitMask(s2);
    ws2812_port = portOutputRegister(digitalPinToPort(s2) );
    // set pinMode OUTPUT */
    pinMode(s2, OUTPUT);
  }
  setNumber(led_num);
}
#else // LOOL_PORT_DEFINED
/**
 * Alternate Constructor which can call your own function to map the LOOL_RGBLed to arduino port,
 * it will assigned the LED display buffer and initialization the GPIO of LED lights. You can
 * set any arduino digital pin for the LED data PIN, The default number of light strips is 32.
 * param[in]
 *   port - arduino port
 */
LOOL_RGBLed::LOOL_RGBLed(uint8_t port)
{
  pinMask       = digitalPinToBitMask(port);
  ws2812_port   = portOutputRegister(digitalPinToPort(port) );
  // set pinMode OUTPUT */
  pinMode(port, OUTPUT);
  setNumber(DEFAULT_MAX_LED_NUMBER);
}

/**
 * Alternate Constructor which can call your own function to map the LOOL_RGBLed to arduino port,
 * it will assigned the LED display buffer and initialization the GPIO of LED lights. You can
 * set any arduino digital pin for the LED data PIN, and reset the LED number by this constructor.
 * param[in]
 *   port - arduino port
 * param[in]
 *   led_num - The LED number
 */
LOOL_RGBLed::LOOL_RGBLed(uint8_t port, uint8_t led_num)
{
  pinMask       = digitalPinToBitMask(port);
  ws2812_port   = portOutputRegister(digitalPinToPort(port) );
  // set pinMode OUTPUT */
  pinMode(port, OUTPUT);
  setNumber(led_num);
}
#endif // LOOL_PORT_DEFINED

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
void LOOL_RGBLed::reset(uint8_t port)
{
  _port = port;
  s2    = lool_Port[port].s2;
  s1    = lool_Port[port].s1;
  pinMask = digitalPinToBitMask(s2);
  ws2812_port = portOutputRegister(digitalPinToPort(s2) );
  pinMode(s2, OUTPUT);
}

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
void LOOL_RGBLed::reset(uint8_t port,uint8_t slot)
{
  _port = port;
  s2    = lool_Port[port].s2;
  s1    = lool_Port[port].s1;
  if(SLOT2 == slot)
  {
    pinMask     = digitalPinToBitMask(s2);
    ws2812_port = portOutputRegister(digitalPinToPort(s2) );
    pinMode(s2, OUTPUT);
  }
  else
  {
    pinMask     = digitalPinToBitMask(s1);
    ws2812_port = portOutputRegister(digitalPinToPort(s1) );
    pinMode(s1, OUTPUT);
  }
}
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
void LOOL_RGBLed::setpin(uint8_t port)
{
  pinMask   = digitalPinToBitMask(port);
  ws2812_port = portOutputRegister(digitalPinToPort(port) );
  pinMode(port, OUTPUT);
}

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
void LOOL_RGBLed::setNumber(uint8_t num_leds)
{
  count_led = num_leds;
  pixels    = (uint8_t*)malloc(count_led * 3);
  if(!pixels)
  {
    printf("There is not enough space!\r\n");
  }
  for(int16_t i = 0; i < count_led * 3; i++)
  {
    pixels[i] = 0;
  }
}

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
cRGB LOOL_RGBLed::getColorAt(uint8_t index)
{
  cRGB px_value;

  if(index < count_led)
  {
    uint8_t tmp;
    tmp = (index-1) * 3;

    px_value.g = pixels[tmp];
    px_value.r = pixels[tmp + 1];
    px_value.b = pixels[tmp + 2];
  }
  return(px_value);
}

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
uint8_t LOOL_RGBLed::getNumber(void)
{
  return(count_led);
}

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
bool LOOL_RGBLed::setColorAt(uint8_t index, uint8_t red, uint8_t green, uint8_t blue)
{
  if(index < count_led)
  {
    uint8_t tmp = index * 3;
    pixels[tmp] = green;
    pixels[tmp + 1] = red;
    pixels[tmp + 2] = blue;
    return(true);
  }
  return(false);
}

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
bool LOOL_RGBLed::setColor(uint8_t index, uint8_t red, uint8_t green, uint8_t blue)
{
  if(index == 0)
  {
    for(int16_t i = 0; i < count_led; i++)
    {
      setColorAt(i,red,green,blue);
    }
    return(true);
  }
  else
  {
    setColorAt(index-1,red,green,blue);
  }
  return(false);
}

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
bool LOOL_RGBLed::setColor(uint8_t red, uint8_t green, uint8_t blue)
{
  return(setColor(0, red, green, blue) );;
}

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
bool LOOL_RGBLed::setColor(uint8_t index, long value)
{
  if(index == 0)
  {
    for(int16_t i = 0; i < count_led; i++)
    {
      uint8_t tmp    = index * 3;
      uint8_t red    = (value & 0xff0000) >> 16;
      uint8_t green  = (value & 0xff00) >> 8;
      uint8_t blue   = value & 0xff;
      pixels[tmp]    = green;
      pixels[tmp + 1] = red;
      pixels[tmp + 2] = blue;
    }
    return(true);
  }
  else if(index < count_led)
  {
    uint8_t tmp    = (index - 1) * 3;
    uint8_t red    = (value & 0xff0000) >> 16;
    uint8_t green  = (value & 0xff00) >> 8;
    uint8_t blue   = value & 0xff;
    pixels[tmp]    = green;
    pixels[tmp + 1] = red;
    pixels[tmp + 2] = blue;
    return(true);
  }
  return(false);
}

/*
  This routine writes an array of bytes with RGB values to the Dataout pin
  using the fast 800kHz clockless WS2811/2812 protocol.
 */
/* Timing in ns */
#define w_zeropulse (350)
#define w_onepulse  (900)
#define w_totalperiod (1250)

/* Fixed cycles used by the inner loop */
#define w_fixedlow  (3)
#define w_fixedhigh (6)
#define w_fixedtotal (10)

/* Insert NOPs to match the timing, if possible */
#define w_zerocycles ( ( (F_CPU / 1000) * w_zeropulse) / 1000000)
#define w_onecycles ( ( (F_CPU / 1000) * w_onepulse + 500000) / 1000000)
#define w_totalcycles ( ( (F_CPU / 1000) * w_totalperiod + 500000) / 1000000)

/* w1 - nops between rising edge and falling edge - low */
#define w1 (w_zerocycles - w_fixedlow)
/* w2   nops between fe low and fe high */
#define w2 (w_onecycles - w_fixedhigh - w1)
/* w3   nops to complete loop */
#define w3 (w_totalcycles - w_fixedtotal - w1 - w2)

#if w1 > 0
#define w1_nops w1
#else
#define w1_nops 0
#endif

/*
  The only critical timing parameter is the minimum pulse length of the "0"
  Warn or throw error if this timing can not be met with current F_CPU settings.
 */
#define w_lowtime ( (w1_nops + w_fixedlow) * 1000000) / (F_CPU / 1000)
#if w_lowtime > 550
#error "Light_ws2812: Sorry, the clock speed is too low. Did you set F_CPU correctly?"
#elif w_lowtime > 450
#warning "Light_ws2812: The timing is critical and may only work on WS2812B, not on WS2812(S)."
#warning "Please consider a higher clockspeed, if possible"
#endif

#if w2 > 0
#define w2_nops w2
#else
#define w2_nops 0
#endif

#if w3 > 0
#define w3_nops w3
#else
#define w3_nops 0
#endif

#define w_nop1  "nop      \n\t"
#define w_nop2  "rjmp .+0 \n\t"
#define w_nop4  w_nop2 w_nop2
#define w_nop8  w_nop4 w_nop4
#define w_nop16 w_nop8 w_nop8

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
void LOOL_RGBLed::rgbled_sendarray_mask(uint8_t *data, uint16_t datlen, uint8_t maskhi, uint8_t *port)
{
  uint8_t curbyte, ctr, masklo;
  uint8_t oldSREG = SREG;
  cli(); // Disables all interrupts

  masklo  = *port & ~maskhi;
  maskhi  = *port | maskhi;

  while(datlen--)
  {
    curbyte = *data++;

    asm volatile (
            "       ldi   %0,8  \n\t"
            "loop%=:            \n\t"
            "       st    X,%3 \n\t"        //  '1' [02] '0' [02] - re
#if (w1_nops & 1)
            w_nop1
#endif
#if (w1_nops & 2)
            w_nop2
#endif
#if (w1_nops & 4)
            w_nop4
#endif
#if (w1_nops & 8)
            w_nop8
#endif
#if (w1_nops & 16)
            w_nop16
#endif
            "       sbrs  %1,7  \n\t"       //  '1' [04] '0' [03]
            "       st    X,%4 \n\t"        //  '1' [--] '0' [05] - fe-low
            "       lsl   %1    \n\t"       //  '1' [05] '0' [06]
#if (w2_nops & 1)
            w_nop1
#endif
#if (w2_nops & 2)
            w_nop2
#endif
#if (w2_nops & 4)
            w_nop4
#endif
#if (w2_nops & 8)
            w_nop8
#endif
#if (w2_nops & 16)
            w_nop16
#endif
            "       brcc skipone%= \n\t"    /*  '1' [+1] '0' [+2] - */
            "       st   X,%4      \n\t"    /*  '1' [+3] '0' [--] - fe-high */
            "skipone%=:               "     /*  '1' [+3] '0' [+2] - */

#if (w3_nops & 1)
            w_nop1
#endif
#if (w3_nops & 2)
            w_nop2
#endif
#if (w3_nops & 4)
            w_nop4
#endif
#if (w3_nops & 8)
            w_nop8
#endif
#if (w3_nops & 16)
            w_nop16
#endif

            "       dec   %0    \n\t"       //  '1' [+4] '0' [+3]
            "       brne  loop%=\n\t"       //  '1' [+5] '0' [+4]
            : "=&d" (ctr)
            : "r" (curbyte), "x" (port), "r" (maskhi), "r" (masklo)
    );
  }

  SREG = oldSREG;
}

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
void LOOL_RGBLed::show(void)
{
  rgbled_sendarray_mask(pixels, 3 * count_led, pinMask, (uint8_t*)ws2812_port);
}

/**
 * Destructor which can call your own function, it will release the LED buffer
 */
LOOL_RGBLed::~LOOL_RGBLed(void)
{
  free(pixels);
  pixels = NULL;
}

