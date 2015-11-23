/**
 * @mainpage loollool library for Arduino
 *
 * @par Description
 *
 * This is the library provided by loollool. \n
 * It provides drivers for all loollool RJ25 jack interface modules. \n
 *
 * The latest version of this documentation can be downloaded from \n
 * http://learn.loollool.cc/
 *
 * Package can be download from http://learn.loollool.cc/
 *
 * @par Installation
 *
 * Install the package in the normal way: unzip the distribution zip file to the libraries \n
 * sub-folder of your sketchbook or Arduino, \n
 * copy files in loollool/src folder to arduino/libraries/loollool/
 *
 * @par Donations
 *
 * This library is offered under GPLv2 license for those who want to use it that way. \n
 * Additional information can be found at http://www.gnu.org/licenses/old-licenses/gpl-2.0.html \n
 * We are tring hard to keep it up to date, fix bugs free and to provide free support on our site. \n
 *
 * @par Copyright
 *
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
 * @par History:
 * <pre>
 * Author           Time           Version          Descr
 * sean         2015/11/18     1.0.0            Rebuild the old lib.
 * </pre>
 *
 * @author  sean (sean@loollool.cc) DO NOT CONTACT THE AUTHOR DIRECTLY: USE THE LISTS
 */

#ifndef LOOL_Config_H
#define LOOL_Config_H

#include <..\..\servo\src\servo.h>
#include <..\..\..\hardware\arduino\avr\libraries\Wire\Wire.h>
#include <..\..\..\hardware\arduino\avr\libraries\EEPROM\EEPROM.h>
#include <..\..\..\hardware\arduino\avr\libraries\SoftwareSerial\SoftwareSerial.h>


#define LOOL_PORT_DEFINED

#if defined(__AVR__)
#define MePIN_TO_BASEREG(pin)               ( portInputRegister (digitalPinToPort (pin) ) )
#define MePIN_TO_BITMASK(pin)               ( digitalPinToBitMask (pin) )
#define MeIO_REG_TYPE                       uint8_t
#define MeIO_REG_ASM                        asm ("r30")
#define MeDIRECT_READ(base, mask)           ( ( (*(base) ) & (mask) ) ? 1 : 0)
#define MeDIRECT_MODE_INPUT(base, mask)     ( (*( (base) + 1) ) &= ~(mask) ), ( (*( (base) + 2) ) |= (mask) ) // INPUT_PULLUP
#define MeDIRECT_MODE_OUTPUT(base, mask)    ( (*( (base) + 1) ) |= (mask) )
#define MeDIRECT_WRITE_LOW(base, mask)      ( (*( (base) + 2) ) &= ~(mask) )
#define MeDIRECT_WRITE_HIGH(base, mask)     ( (*( (base) + 2) ) |= (mask) )
#endif // __AVR__


#endif // LOOL_Config_H

