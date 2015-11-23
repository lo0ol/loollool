/**
 * @par Copyright (C), 2012-2015, LOOLLOOL
 * @file    ColorLoopTest.ino
 * @author  Sean
 * @version V1.0.0
 * @date    2015/11/18
 * @brief   Description: this file is sample code for RGB LED, It used for random color change
 *
 * Function List:
 * 1. bool LOOL_RGBLed::setColorAt(uint8_t index, uint8_t red, uint8_t green, uint8_t blue)
 * 2. void LOOL_RGBLed::show()
 * \par History:
 * <pre>
 * <Author>     <Time>        <Version>      <Descr>
 * Sean    2015/11/18   1.0.0          rebuild the old lib
 * </pre>
 */
#include "LOOL_Smart.h"

LOOL_RGBLed led(PORT_3);

uint8_t red = 128;
uint8_t green = 128;
uint8_t blue = 128;
float j, f, k;

void setup()
{

  led.setColorAt(0, red, green, blue);
  led.setColorAt(1, red, green, blue);
  led.setColorAt(2, red, green, blue);
  led.setColorAt(3, red, green, blue);
}

void loop()
{
  color_loop();
}

void color_loop()
{
  for(uint8_t i=0;i<4;i++)
  {
    led.turnOn_Any(i);
    delay(500);
    led.turnOff_Any(i);
    delay(500);
  }
}

