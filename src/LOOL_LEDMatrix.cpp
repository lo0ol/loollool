/**
 * @par Copyright (C), 2012-2015, loollool
 * @class   LOOL_LEDMatrix
 * @brief   Driver for LOOL LEDMatrix module.
 * @file    LOOL_Joystick.h
 * @author  sean
 * @version V1.0.0
 * @date    2015/11/18
 * @brief   Header for LOOL_Joystick.cpp module
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

#include "LOOL_LEDMatrix.h"
#include "LOOL_LEDMatrixData.h"
/**
 * Alternate Constructor which can call your own function to map the LOOL_LEDMatrix to arduino port,
 * no pins are used or initialized here, it only assigned the LED Matrix display buffer. 
 * param[in]
 *   None
 */
LOOL_LEDMatrix::LOOL_LEDMatrix():LOOL_Port()
{

}
/**
 * Alternate Constructor which can call your own function to map the LOOL_LEDMatrix to arduino port,
 * it will assigned the LED Matrix display buffer and initialization the GPIO of LED lights. The S1 S2
 * will be used here.
 * param[in]
 *   port - RJ25 port from PORT_1 to M2
 */

LOOL_LEDMatrix::LOOL_LEDMatrix(uint8_t port): LOOL_Port(port)
{
	u8_SCKPin = s1;
	u8_DINPin = s2;


	pinMode(u8_SCKPin, OUTPUT);
	pinMode(u8_DINPin, OUTPUT);
	digitalWrite(u8_SCKPin,HIGH);
	digitalWrite(u8_DINPin,HIGH);

    writeByte(Mode_Address_Auto_Add_1);
    setBrightness(Brightness_5);
    clearScreen();
}
/**
 * Alternate Constructor which can call your own function to map the LOOL LEDMatrix to arduino port. 
 * param[in]
 *    DIN_Pin - The DATA pin for LED Matrix module(arduino port).
 * param[in]
 *    SCK_Pin - The CLK pin for LED Matrix module(arduino port).
 */

LOOL_LEDMatrix::LOOL_LEDMatrix(uint8_t SCK_Pin, uint8_t DIN_Pin)
{
	u8_SCKPin = SCK_Pin; 
	u8_DINPin = DIN_Pin;

	pinMode(u8_SCKPin, OUTPUT);
	pinMode(u8_DINPin, OUTPUT);
	digitalWrite(u8_SCKPin,HIGH);
	digitalWrite(u8_DINPin,HIGH);

    writeByte(Mode_Address_Auto_Add_1);
    setBrightness(Brightness_5);
    clearScreen();
}
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
void LOOL_LEDMatrix::reset(uint8_t port){
    u8_SCKPin = lool_Port[port].s1;
	u8_DINPin = lool_Port[port].s2;


	pinMode(u8_SCKPin, OUTPUT);
	pinMode(u8_DINPin, OUTPUT);
	digitalWrite(u8_SCKPin,HIGH);
	digitalWrite(u8_DINPin,HIGH);

    writeByte(Mode_Address_Auto_Add_1);
    setBrightness(Brightness_5);
    clearScreen();
}
/**
 * @par Function
 *    writeByte
 * @par Description
 *    White data Byte to LEDMatrix.
 * param[in]
 *    data - Data  to write to module.
 * @par Output
 *    None
 * return
 *    None
 * @par Others
 *    None
 */
void LOOL_LEDMatrix::writeByte(uint8_t data)
{
    //Start
    digitalWrite(u8_SCKPin, HIGH);
    digitalWrite(u8_DINPin, LOW);

    for(char i=0;i<8;i++)
    {
        digitalWrite(u8_SCKPin, LOW);
        digitalWrite(u8_DINPin, (data & 0x01));
        digitalWrite(u8_SCKPin, HIGH);
        data = data >> 1;
    }

    //End
    digitalWrite(u8_SCKPin, LOW);
    digitalWrite(u8_DINPin, LOW);
    digitalWrite(u8_SCKPin, HIGH);
    digitalWrite(u8_DINPin, HIGH);
    // delayMicroseconds(1);
}
/**
 * @par Function
 *    writeBytesToAddress
 * @par Description
 *    Write count of data Byte to certain address.
 * param[in]
 *    Address - address of data.
 * param[in]
 *    P_data - Data array  to write to Data address.
 * param[in]
 *    count_of_data - number of Data to write to module.
 * @par Output
 *    None
 * return
 *    None
 * @par Others
 *    None
 */

void LOOL_LEDMatrix::writeBytesToAddress(uint8_t Address, const uint8_t *P_data, uint8_t count_of_data)
{
    uint8_t T_data;

    if(Address > 15 || count_of_data==0)
        return;

    Address = ADDRESS(Address);

    //Start
    digitalWrite(u8_SCKPin, HIGH);
    digitalWrite(u8_DINPin, LOW);

    //write Address
    for(char i=0;i<8;i++)
    {
        digitalWrite(u8_SCKPin, LOW);
        digitalWrite(u8_DINPin, (Address & 0x01));
        digitalWrite(u8_SCKPin, HIGH);
        Address = Address >> 1;
    }


    //write data
    for(uint8_t k=0; k<count_of_data; k++)
    {
        T_data = *(P_data + k);

        for(char i=0;i<8;i++)
        {
            digitalWrite(u8_SCKPin, LOW);
            digitalWrite(u8_DINPin, (T_data & 0x80));
            digitalWrite(u8_SCKPin, HIGH);
            T_data = T_data << 1;
        }
    }

    //End
    digitalWrite(u8_SCKPin, LOW);
    digitalWrite(u8_DINPin, LOW);
    digitalWrite(u8_SCKPin, HIGH);
    digitalWrite(u8_DINPin, HIGH);
    // delayMicroseconds(1);
}

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

void LOOL_LEDMatrix::clearScreen()
{
    for(uint8_t i=0;i<LED_BUFFER_SIZE;i++)
    {
        u8_Display_Buffer[i] = 0x00;
    }

    b_Color_Index = 1;
    b_Draw_Str_Flag = 0;

    writeBytesToAddress(0,u8_Display_Buffer,LED_BUFFER_SIZE);
}

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
 
void LOOL_LEDMatrix::setBrightness(uint8_t Bright)
{
    if((uint8_t)Bright>8)
    {
        Bright = Brightness_8;
    }

    if((uint8_t)Bright != 0)
    {
        Bright = (LED_Matrix_Brightness_TypeDef)((uint8_t)(Bright-1)|0x08);
        
    }
    writeByte(0x80 | (uint8_t)Bright);

}

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

void LOOL_LEDMatrix::setColorIndex(bool Color_Number)
{
    b_Color_Index = Color_Number;
}

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
 
void LOOL_LEDMatrix::drawBitmap(int8_t x, int8_t y, uint8_t Bitmap_Width, uint8_t *Bitmap)
{

    if(x>15 || y>7 || Bitmap_Width==0)
        return;


    if(b_Color_Index == 1)
    {
        for(uint8_t k=0;k<Bitmap_Width;k++)
        {
          if(x+k>=0){
            u8_Display_Buffer[x+k] = (u8_Display_Buffer[x+k] & (0xff << (8-y))) | (y>0?(Bitmap[k] >> y):(Bitmap[k] << (-y)));
          }
        }
    }
    else if(b_Color_Index == 0)
    {
        for(uint8_t k=0;k<Bitmap_Width;k++)
        {
            if(x+k>=0){
              u8_Display_Buffer[x+k] = (u8_Display_Buffer[x+k] & (0xff << (8-y))) | (y>0?(~Bitmap[k] >> y):(~Bitmap[k] << (-y)));
            }
        }
    }

    writeBytesToAddress(0,u8_Display_Buffer,LED_BUFFER_SIZE);
}

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
 
void LOOL_LEDMatrix::drawStr(int16_t X_position, int8_t Y_position, const char *str)
{
    b_Draw_Str_Flag = 1;

    for(i16_Number_of_Character_of_Str = 0; str[i16_Number_of_Character_of_Str] != '\0'; i16_Number_of_Character_of_Str++)
    {
        if(i16_Number_of_Character_of_Str < STRING_DISPLAY_BUFFER_SIZE - 1)
        {
            i8_Str_Display_Buffer[i16_Number_of_Character_of_Str] = str[i16_Number_of_Character_of_Str];
        }
        else
        {
            break;
        }
    }
    i8_Str_Display_Buffer[i16_Number_of_Character_of_Str] = '\0';


    if(X_position < -(i16_Number_of_Character_of_Str * 6))
    {
        X_position = -(i16_Number_of_Character_of_Str * 6);
    }
    else if(X_position > 16)
    {
        X_position = 16;
    }
    i16_Str_Display_X_Position = X_position;


    if(Y_position < -1)
    {
        Y_position = -1;
    }
    else if(Y_position >15)
    {
        Y_position = 15;
    }
    i8_Str_Display_Y_Position = Y_position;

    showStr();

}
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
 
void LOOL_LEDMatrix::showStr()
{

    uint8_t display_buffer_label = 0;

    if(i16_Str_Display_X_Position > 0)
    {
        for(display_buffer_label = 0; display_buffer_label < i16_Str_Display_X_Position && display_buffer_label < LED_BUFFER_SIZE; display_buffer_label++)
        {
            u8_Display_Buffer[display_buffer_label] = 0x00;
        }

        if(display_buffer_label < LED_BUFFER_SIZE)
        {
            uint8_t num;

            for(uint8_t k=0;display_buffer_label < LED_BUFFER_SIZE && k < i16_Number_of_Character_of_Str;k++)
            {
                for(num=0; pgm_read_byte(&Character_font_6x8[num].Character[0]) != '@'; num++)
                {
                    if(i8_Str_Display_Buffer[k] == pgm_read_byte(&Character_font_6x8[num].Character[0]))
                    {
                        for(uint8_t j=0;j<6;j++)
                        {
                            u8_Display_Buffer[display_buffer_label] = pgm_read_byte(&Character_font_6x8[num].data[j]);
                            display_buffer_label++;

                            if(display_buffer_label >= LED_BUFFER_SIZE)
                            {
                                break;
                            }
                        }
                        break;
                    }
                }

                if(pgm_read_byte(&Character_font_6x8[num].Character[0]) == '@')
                {
                    i8_Str_Display_Buffer[k] = ' ';
                    k--;
                }
            }

            if(display_buffer_label < LED_BUFFER_SIZE)
            {
                for(display_buffer_label = display_buffer_label; display_buffer_label < LED_BUFFER_SIZE; display_buffer_label++)
                {
                    u8_Display_Buffer[display_buffer_label] = 0x00;
                }
            }
        }
    }

    else if(i16_Str_Display_X_Position <= 0)
    {
        if(i16_Str_Display_X_Position == -(i16_Number_of_Character_of_Str * 6))
        {
            for(; display_buffer_label < LED_BUFFER_SIZE; display_buffer_label++)
            {
                u8_Display_Buffer[display_buffer_label] = 0x00;
            }
        }
        else
        {
            int8_t j = (-i16_Str_Display_X_Position) % 6;
            uint8_t num;

            i16_Str_Display_X_Position = -i16_Str_Display_X_Position;

            for(int16_t k=i16_Str_Display_X_Position/6; display_buffer_label < LED_BUFFER_SIZE && k < i16_Number_of_Character_of_Str;k++)
            {
                for(num=0; pgm_read_byte(&Character_font_6x8[num].Character[0]) != '@'; num++)
                {
                    if(i8_Str_Display_Buffer[k] == pgm_read_byte(&Character_font_6x8[num].Character[0]))
                    {
                        for(;j<6;j++)
                        {
                            u8_Display_Buffer[display_buffer_label] = pgm_read_byte(&Character_font_6x8[num].data[j]);
                            display_buffer_label++;

                            if(display_buffer_label >= LED_BUFFER_SIZE)
                            {
                                break;
                            }
                        }
                        j=0;
                        break;
                    }
                }

                if(pgm_read_byte(&Character_font_6x8[num].Character[0]) == '@')
                {
                    i8_Str_Display_Buffer[k] = ' ';
                    k--;
                }

            }

            if(display_buffer_label < LED_BUFFER_SIZE)
            {
                for(; display_buffer_label < LED_BUFFER_SIZE; display_buffer_label++)
                {
                    u8_Display_Buffer[display_buffer_label] = 0x00;
                }
            }

            i16_Str_Display_X_Position = -i16_Str_Display_X_Position;
        }
    }


    if(7 - i8_Str_Display_Y_Position >= 0)
    {
        for(uint8_t k=0; k<LED_BUFFER_SIZE; k++)
        {
            u8_Display_Buffer[k] = u8_Display_Buffer[k] << (7 - i8_Str_Display_Y_Position);
        }
    }
    else
    {
        for(uint8_t k=0; k<LED_BUFFER_SIZE; k++)
        {
            u8_Display_Buffer[k] = u8_Display_Buffer[k] >> (i8_Str_Display_Y_Position - 7);
        }
    }

    
    if(b_Color_Index == 0)
    {
        for(uint8_t k=0; k<LED_BUFFER_SIZE; k++)
        {
            u8_Display_Buffer[k] = ~u8_Display_Buffer[k];
        }
    }

    writeBytesToAddress(0,u8_Display_Buffer,LED_BUFFER_SIZE);

}

/**
 * @par Function
 *    showClock
 * @par Description
 *    show Clock data on LEDMatrix.
 * param[in]
 *    hour - data of hour
  * param[in]
 *    minute - data of minute
  * param[in]
 *    point_flag - Value to be set
 * @par Output
 *    None
 * return
 *    None
 * @par Others
 *    None
 */
 
void LOOL_LEDMatrix::showClock(uint8_t hour, uint8_t minute, bool point_flag)
{
    u8_Display_Buffer[0]  = pgm_read_byte(&Clock_Number_font_3x8[hour/10].data[0]);
    u8_Display_Buffer[1]  = pgm_read_byte(&Clock_Number_font_3x8[hour/10].data[1]);
    u8_Display_Buffer[2]  = pgm_read_byte(&Clock_Number_font_3x8[hour/10].data[2]);
 
    u8_Display_Buffer[3]  = 0x00;
 
    u8_Display_Buffer[4]  = pgm_read_byte(&Clock_Number_font_3x8[hour%10].data[0]);
    u8_Display_Buffer[5]  = pgm_read_byte(&Clock_Number_font_3x8[hour%10].data[1]);
    u8_Display_Buffer[6]  = pgm_read_byte(&Clock_Number_font_3x8[hour%10].data[2]);
 
    u8_Display_Buffer[9]  = pgm_read_byte(&Clock_Number_font_3x8[minute/10].data[0]);
    u8_Display_Buffer[10] = pgm_read_byte(&Clock_Number_font_3x8[minute/10].data[1]);
    u8_Display_Buffer[11] = pgm_read_byte(&Clock_Number_font_3x8[minute/10].data[2]);

    u8_Display_Buffer[12] = 0x00;

    u8_Display_Buffer[13] = pgm_read_byte(&Clock_Number_font_3x8[minute%10].data[0]);
    u8_Display_Buffer[14] = pgm_read_byte(&Clock_Number_font_3x8[minute%10].data[1]);
    u8_Display_Buffer[15] = pgm_read_byte(&Clock_Number_font_3x8[minute%10].data[2]);


    if(point_flag == PointOn)
    {
        u8_Display_Buffer[7] = 0x28;
        u8_Display_Buffer[8] = 0x28;
    }
    else
    {
        u8_Display_Buffer[7] = 0x00;
        u8_Display_Buffer[8] = 0x00;
    }

    if(b_Color_Index == 0)
    {
        for(uint8_t k=0; k<LED_BUFFER_SIZE; k++)
        {
            u8_Display_Buffer[k] = ~u8_Display_Buffer[k];
        }
    }

    writeBytesToAddress(0,u8_Display_Buffer,LED_BUFFER_SIZE);
}
