/**
 * \par Copyright (C), 2012-2015, LOOLLOOL
 * @file    OledTest.ino
 * @author  Sean
 * @version V1.0.0
 * @date    2015/09/01
 * @brief   Description: this file is sample program for TFT LCD.
 *
 * Function List:
 *
 * \par History:
 * <pre>
 * `<Author>`         `<Time>`        `<Version>`        `<Descr>`
 * Sean         2015/11/10     1.0.0                   
 * </pre>
 */
 #include <Wire.h>
#include <LOOL_Smart.h>
LOOL_OLED display;
void setup() {
 display.begin();  
 display.expression();
 delay(2000); 
 display.clearDisplay() ;
 display.LCD_Str("abcdefghijklmnopqrstuvwxyz",10,0);
 delay(2000); 
 display.clearDisplay() ;
 display.LCD_Str("1234567890",10,0);
 delay(2000); 
 display.clearDisplay() ;
 display.LCD_Str("Time",10,0);
 display.LCD_Str("s",60,2);
}
 uint16_t i=0;
void loop() {
  
    i++;
    display.LCD_Number(millis()/1000,10,2);
    delay(50);
}
