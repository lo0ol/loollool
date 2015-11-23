/**
 * \par Copyright (C), 2012-2015, LOOLLOOL
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

int lastNum = 0;

void setup()
{

}

void loop()
{
  uint8_t count = random(0, 15);
  /* generates random numbers */
  indicators(count, 20, 30, 40);
  delay(150);
}

void indicators(uint8_t count, uint8_t r, uint8_t g, uint8_t b)
{
  uint8_t inSpeed = 10;
  if(lastNum <= count)
  {
    for(int16_t x = lastNum; x <= count; ++x)
    {
      led.setColorAt(x, r, g, b);
      led.show();
      delay(inSpeed);
    }
  }
  else
  {
    for(int16_t x = lastNum; x > count; --x)
    {
      led.setColorAt(x, 0, 0, 0);
      led.show();
      delay(inSpeed);
    }
  }
  lastNum = count;
}

