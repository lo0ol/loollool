/**
 * @par Copyright (C), 2012-2015, loollool
 * @class   LOOL_LEDMatrix
 * @brief   Header for LOOL LEDMatrix module.
 * @file    LOOL_LEDMatrix.h
 * @author  sean
 * @version V1.0.0
 * @date    2015/11/18
 * @brief   Header for LOOL LEDMatrix module
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
 * This file is a drive  LOOL LEDMatrix, It supports LOOL LEDMatrix  device provided
 * by loollool.
 *
 * @par Method List:
 *
 *    1. void LOOL_LEDMatrix::clearScreen()
 *    2. void LOOL_LEDMatrix::setBrightness(uint8_t Bright)
 *    3. void LOOL_LEDMatrix::setColorIndex(bool Color_Number);
 *    4. void LOOL_LEDMatrix::drawBitmap(int8_t x, int8_t y, uint8_t Bitmap_Width, uint8_t *Bitmap)
 *    5. void LOOL_LEDMatrix::drawStr(int16_t X_position, int8_t Y_position, const char *str)
 *    6. void LOOL_LEDMatrix::showClock(uint8_t hour, uint8_t minute, bool = PointOn)
 *    7. void LOOL_LEDMatrix::reset(uint8_t port)
 *
 * @par History:
 * <pre>
 * `<Author>`         `<Time>`        `<Version>`        `<Descr>`
 * sean         2015/11/18     1.0.0            Rebuild the old lib.
 * </pre>
 *
 */
#ifndef LOOL_LED_MATRIX_H_
#define LOOL_LED_MATRIX_H_

#include "LOOL_Port.h"
#define PointOn   1
#define PointOff  0


#define LED_BUFFER_SIZE   16
#define STRING_DISPLAY_BUFFER_SIZE 20


//Define Data Command Parameters
#define Mode_Address_Auto_Add_1  0x40     //0100 0000 B
#define Mode_Permanent_Address   0x44     //0100 0100 B


//Define Address Command Parameters
#define ADDRESS(addr)  (0xC0 | addr)


typedef enum
{
	Brightness_0 = 0,
	Brightness_1,
	Brightness_2,
	Brightness_3,
	Brightness_4,
	Brightness_5,
	Brightness_6,
	Brightness_7,
	Brightness_8
}LED_Matrix_Brightness_TypeDef;



/*           Me LED Matrix 8X16            */

class LOOL_LEDMatrix:public LOOL_Port
{
public:

/**
 * Alternate Constructor which can call your own function to map the LOOL_LEDMatrix to arduino port,
 * no pins are used or initialized here, it only assigned the LED Matrix display buffer. 
 * param[in]
 *   None
 */
 
	LOOL_LEDMatrix();
	/**
 * Alternate Constructor which can call your own function to map the LOOL_LEDMatrix to arduino port,
 * it will assigned the LED Matrix display buffer and initialization the GPIO of LED lights. The S1 S2
 * will be used here.
 * param[in]
 *   port - RJ25 port from PORT_1 to M2
 */
 
	LOOL_LEDMatrix(uint8_t port);
	
/**
 * Alternate Constructor which can call your own function to map the LOOL LEDMatrix to arduino port. 
 * param[in]
 *    DIN_Pin - The DATA pin for LED Matrix module(arduino port).
 * param[in]
 *    SCK_Pin - The CLK pin for LED Matrix module(arduino port).
 */

	LOOL_LEDMatrix(uint8_t SCK_Pin, uint8_t DIN_Pin);

/**
 * @par Function
 *    clearScreen
 * @par Description
 *    clear the Screen data.
 * param[in]
 *    None
 * @par Output
 *    None
 * return
 *    None
 * @par Others
 *    None
 */
	void clearScreen();
	/**
 * @par Function
 *    setBrightness
 * @par Description
 *    set the Brightness of screen.
 * param[in]
 *    Bright - Value to be set
 * @par Output
 *    None
 * return
 *    None
 * @par Others
 *    None
 */
	void setBrightness(uint8_t Bright);
	/**
 * @par Function
 *    setColorIndex
 * @par Description
 *    set the Brightness of screen.
 * param[in]
 *    Bright - Value to be set
 * @par Output
 *    None
 * return
 *    None
 * @par Others
 *    None
 */
	void setColorIndex(bool Color_Number);
	/**
 * @par Function
 *    drawBitmap
 * @par Description
 *    show Bitmap  on LEDMatrix.
 * param[in]
 *    X_position - X position to be set
 * param[in]
 *    Y_position - Y position to be set
 * param[in]
 *   Bitmap_Width - width of bitmap
 * param[in]
 *    *Bitmap - Bitmap to show
 * @par Output
 *    None
 * return
 *    None
 * @par Others
 *    None
 */
	void drawBitmap(int8_t x, int8_t y, uint8_t Bitmap_Width, uint8_t *Bitmap);
	
/**
 * @par Function
 *    drawStr
 * @par Description
 *    Draw string data on LEDMatrix.
 * param[in]
 *    X_position - X position to be set
  * param[in]
 *    Y_position - Y position to be set
  * param[in]
 *    *str - Data to show
 * @par Output
 *    None
 * return
 *    None
 * @par Others
 *    None
 */
 
	void drawStr(int16_t X_position, int8_t Y_position, const char *str);
	/**
 * @par Function
 *    showStr
 * @par Description
 *    show string data on LEDMatrix.
 * param[in]
 *    None
 * @par Output
 *    None
 * return
 *    None
 * @par Others
 *    None
 */
 
	void showClock(uint8_t hour, uint8_t minute, bool = PointOn);
	/**
 * @par Function
 *    reset
 * @par Description
 *    Reset the port for  LOOL LEDMatrix module, the prot here is RJ25 port from PORT_1 to M2.
 * param[in]
 *    port - RJ25 port from PORT_1 to M2
 * @par Output
 *    None
 * @par Return
 *    None
 * @par Others
 *    Set global variable u8_SCKPin and u8_DINPin
 */
 
	void reset(uint8_t port);

private:
	uint8_t u8_SCKPin;
	uint8_t u8_DINPin;

	bool b_Color_Index;
	bool b_Draw_Str_Flag;

	uint8_t u8_Display_Buffer[LED_BUFFER_SIZE];

	int16_t i16_Str_Display_X_Position;
	int8_t i8_Str_Display_Y_Position;
	int16_t i16_Number_of_Character_of_Str;
	char i8_Str_Display_Buffer[STRING_DISPLAY_BUFFER_SIZE];

	void writeByte(uint8_t data);
	void writeBytesToAddress(uint8_t Address, const uint8_t *P_data, uint8_t count_of_data);
	void showStr();

};

#endif
