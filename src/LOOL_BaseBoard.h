/**
 * @par Copyright (C), 2012-2015, loollool
 * @brief    Driver for BaseBoard.
 * \file    LOOL BaseBoard.h
 * @author  sean
 * @version V1.0.0
 * @date    2015/11/18
 * @brief   Driver for BaseBoard.
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
 * This file is Hardware adaptation layer between BaseBoard board
 * and all loollool drives
 *
 * @par History:
 * <pre>
 * `<Author>`         `<Time>`        `<Version>`        `<Descr>`
 * sean         2015/11/18     1.0.0            Rebuild the old lib.
 * </pre>
 */
#ifndef LOOL_BaseBoard_H
#define LOOL_BaseBoard_H

#include <arduino.h>
#include "LOOL_Config.h"

/* Supported Modules drive needs to be added here */
#include "LOOL_7SegmentDisplay.h"
#include "LOOL_UltrasonicSensor.h"
#include "LOOL_DCMotor.h"
#include "LOOL_RGBLed.h"
#include "LOOL_4Button.h"
#include "LOOL_Potentiometer.h"
#include "LOOL_Joystick.h"
#include "LOOL_PIRMotionSensor.h"
#include "LOOL_Shutter.h"
#include "LOOL_LineFollower.h"
#include "LOOL_SoundSensor.h"
#include "LOOL_LimitSwitch.h"
#include "LOOL_LightSensor.h"
#include "LOOL_Serial.h"
#include "LOOL_Bluetooth.h"
#include "LOOL_Wifi.h"
#include "LOOL_Temperature.h"
#include "LOOL_Gyro.h"
#include "LOOL_InfraredReceiver.h"
#include "LOOL_Compass.h"
#include "LOOL_USBHost.h"
#include "LOOL_TouchSensor.h"
#include "LOOL_Stepper.h"
#include "LOOL_EncoderMotor.h"
#include "LOOL_Buzzer.h"
#include "LOOL_LEDMatrix.h"
#include "LOOL_HumitureSensor.h"
#include "LOOL_FlameSensor.h"
#include "LOOL_GasSensor.h"

/*********************  base Board GPIO Map *********************************/
LOOL_Port_Sig lool_Port[11] =
{
  { NC, NC }, { 11, A8 }, { 13, A11}, { A10, A9 }, { 1, 0 },
  { MISO, SCK }, { A0, A1 }, { A2, A3 }, { A4, A5 }, { 6, 7 },
  { 5, 4 }
};

#define buzzerOn()  DDRE |= 0x04,PORTE |= B00000100
#define buzzerOff() DDRE |= 0x04,PORTE &= B11111011

#endif // MeBaseBoard_H

