#ifndef LOOL_OLED_H
#define LOOL_OLED_H 

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stdbool.h>
#include <arduino.h>
#include "LOOL_Config.h"
#ifdef LOOL_PORT_DEFINED
#include "LOOL_Port.h"
#endif // LOOL_PORT_DEFINED

#include <avr/pgmspace.h>
#define BLACK 0
#define WHITE 1

#define SSD1306_I2C_ADDRESS   0x3C	// 011110+SA0+RW - 0x3C or 0x3D
 #define SSD1306_128_64
#if defined SSD1306_128_64
  #define SSD1306_LCDWIDTH                  128
  #define SSD1306_LCDHEIGHT                 64
#endif

#define SSD1306_SETCONTRAST 0x81
#define SSD1306_DISPLAYALLON_RESUME 0xA4
#define SSD1306_DISPLAYALLON 0xA5
#define SSD1306_NORMALDISPLAY 0xA6
#define SSD1306_INVERTDISPLAY 0xA7
#define SSD1306_DISPLAYOFF 0xAE
#define SSD1306_DISPLAYON 0xAF

#define SSD1306_SETDISPLAYOFFSET 0xD3
#define SSD1306_SETCOMPINS 0xDA

#define SSD1306_SETVCOMDETECT 0xDB

#define SSD1306_SETDISPLAYCLOCKDIV 0xD5
#define SSD1306_SETPRECHARGE 0xD9

#define SSD1306_SETMULTIPLEX 0xA8

#define SSD1306_SETLOWCOLUMN 0x00
#define SSD1306_SETHIGHCOLUMN 0x10

#define SSD1306_SETSTARTLINE 0x40

#define SSD1306_MEMORYMODE 0x20

#define SSD1306_COMSCANINC 0xC0
#define SSD1306_COMSCANDEC 0xC8

#define SSD1306_SEGREMAP 0xA0

#define SSD1306_CHARGEPUMP 0x8D

#define SSD1306_EXTERNALVCC 0x1
#define SSD1306_SWITCHCAPVCC 0x2

// Scrolling #defines
#define SSD1306_ACTIVATE_SCROLL 0x2F
#define SSD1306_DEACTIVATE_SCROLL 0x2E
#define SSD1306_SET_VERTICAL_SCROLL_AREA 0xA3
#define SSD1306_RIGHT_HORIZONTAL_SCROLL 0x26
#define SSD1306_LEFT_HORIZONTAL_SCROLL 0x27
#define SSD1306_VERTICAL_AND_RIGHT_HORIZONTAL_SCROLL 0x29
#define SSD1306_VERTICAL_AND_LEFT_HORIZONTAL_SCROLL 0x2A

class LOOL_OLED : public LOOL_Port{
 public:
 #ifdef LOOL_PORT_DEFINED
/**
 * Alternate Constructor which can call your own function to map the LOOL_Compass to arduino port,
 * no pins are used or initialized here
 */
  LOOL_OLED(void);

/**
 * Alternate Constructor which can call your own function to map the LOOL_Compass to arduino port,
 * no pins are used or initialized here, but PWM frequency set to 976 Hz
 * param[in]
 *   port - RJ25 port from PORT_1 to M2
 */
  LOOL_OLED(uint8_t port);

/**
 * Alternate Constructor which can call your own function to map the LOOL_Compass to arduino port
 * and change the i2c device address
 * no pins are used or initialized here, but PWM frequency set to 976 Hz
 * param[in]
 *   port - RJ25 port from PORT_1 to M2
 * param[in]
 *   address - the i2c address you want to set
 */
  LOOL_OLED(uint8_t port, uint8_t address);
#else
/**
 * Alternate Constructor which can call your own function to map the _AD0 and _INT to arduino port,
 * no pins are used or initialized here
 * param[in]
 *   _AD0 - arduino gpio number
 * param[in]
 *   _INT - arduino gpio number
 */
  LOOL_OLED(uint8_t AD0, uint8_t INT);

/**
 * Alternate Constructor which can call your own function to map the _AD0 and _INT to arduino port
 * and change the i2c device address, no pins are used or initialized here
 * param[in]
 *   _AD0 - arduino gpio number
 * param[in]
 *   _INT - arduino gpio number
 * param[in]
 *   address - the i2c address you want to set
 */
  LOOL_OLED(uint8_t AD0, uint8_t INT, uint8_t address);
#endif  //  LOOL_PORT_DEFINED
void setpin(uint8_t AD0, uint8_t INT);
  void begin();
  void ssd1306_command(unsigned char c);
  void ssd1306_data(unsigned char c);
  void clearDisplay(unsigned char m);
  void clearDisplay();
  void Set_Pos(unsigned char x, unsigned char y);
  void display();
  void expression();
  void  LCD_Num(uint8_t ch,uint8_t  x,uint8_t y);
  void  LCD_Number(uint16_t ch,uint8_t  x,uint8_t y);
  void  LCD_Str(char ch[],uint8_t x,uint8_t y);
  void  LCD_Str(uint8_t ch[],uint8_t length,uint8_t y);
  void  LCD_shuzi_1(uint8_t ch);
  void  LCD_shuzi_2(uint8_t cch);
   private:
  static volatile uint8_t  _AD0;
  static volatile uint8_t  _INT;
  unsigned char _i2caddr;
};
#endif
