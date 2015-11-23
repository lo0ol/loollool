/**
 * @par Copyright (C), 2012-2015, loollool
 * @class LOOL_DCMotor
 * @brief    Driver for  DC motor device.
 * @file    LOOL_DCMotor.cpp
 * @author  sean
 * @version V1.0.0
 * @date    2015/09/09
 * @brief   Driver for  DC motor device.
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
 * This file is a drive for DC motor device.
 *
 * @par Method List:
 *
 *    1. void LOOL_DCMotor::setpin(uint8_t dir_pin,uint8_t pwm_pin)
 *    2. void LOOL_DCMotor::run(int16_t speed)
 *    3. void LOOL_DCMotor::stop(void)
 *
 * @par History:
 * <pre>
 * `<Author>`         `<Time>`        `<Version>`        `<Descr>`
 * sean         2015/09/09     1.0.0            Rebuild the old lib.
 * </pre>
 *
 * @example DCMotorDriverTest.ino
 */
#include "LOOL_DCMotor.h"

volatile uint8_t       LOOL_DCMotor::dc_dir_pin        = 0;
volatile uint8_t       LOOL_DCMotor::dc_pwm_pin        = 0;

#ifdef LOOL_PORT_DEFINED
/**
 * Alternate Constructor which can call your own function to map the DC motor to arduino port,
 * no pins are used or initialized here.
 * param[in]
 *   None
 */
LOOL_DCMotor::LOOL_DCMotor(void) : LOOL_Port(0)
{

}

/**
 * Alternate Constructor which can call your own function to map the DC motor to arduino port
 * param[in]
 *   port - RJ25 port from PORT_1 to M2
 */
LOOL_DCMotor::LOOL_DCMotor(uint8_t port) : LOOL_Port(port)
{

}
#else // LOOL_PORT_DEFINED
/**
 * Alternate Constructor which can call your own function to map the DC motor to arduino port,
 * it will assigned the output pin.
 * param[in]
 *   dir_pin - arduino port for direction pin(should analog pin)
 * param[in]
 *   pwm_pin - arduino port for pwm input(should analog pin)
 */
LOOL_DCMotor::LOOL_DCMotor(uint8_t dir_pin,uint8_t pwm_pin)
{
  dc_dir_pin = dir_pin;
  dc_pwm_pin = pwm_pin;
  
  pinMode(dc_dir_pin, OUTPUT);
  
/* The PWM frequency is 976 Hz */
#if defined(__AVR_ATmega32U4__) /* MeBaseBoard use ATmega32U4 as MCU */

  TCCR1A = _BV(WGM10);
  TCCR1B = _BV(CS11) | _BV(CS10) | _BV(WGM12);

  TCCR3A = _BV(WGM30);
  TCCR3B = _BV(CS31) | _BV(CS30) | _BV(WGM32);

  TCCR4B = _BV(CS42) | _BV(CS41) | _BV(CS40);
  TCCR4D = 0;

#else if defined(__AVR_ATmega328__) /* else ATmega328 */

  TCCR1A = _BV(WGM10);
  TCCR1B = _BV(CS11) | _BV(CS10) | _BV(WGM12);

  TCCR2A = _BV(WGM21) | _BV(WGM20);
  TCCR2B = _BV(CS22);
#endif
}
#endif /* LOOL_PORT_DEFINED */

/**
 * @par Function
 *   setpin
 * @par Description
 *   Reset the DC motor available PIN by its arduino port.
 * param[in]
 *   dir_pin - arduino port for direction pin(should analog pin)
 * param[in]
 *   pwm_pin - arduino port for pwm input(should analog pin)
 * @par Output
 *   None
 * return
 *   None
 * @par Others
 *   None
 */
void LOOL_DCMotor::setpin(uint8_t dir_pin,uint8_t pwm_pin)
{
  dc_dir_pin = dir_pin;
  dc_pwm_pin = pwm_pin;
  pinMode(dc_dir_pin, OUTPUT);
#ifdef LOOL_PORT_DEFINED
  s1 = pwm_pin;
  s2 = dir_pin;
#endif // LOOL_PORT_DEFINED
}

/**
 * @par Function
 *   run
 * @par Description
 *   Control the motor forward or reverse
 * param[in]
 *   speed - Speed value from -255 to 255
 * @par Output
 *   None
 * return
 *   None
 * @par Others
 *   None
 */
void LOOL_DCMotor::run(int16_t speed)
{
  speed	= speed > 255 ? 255 : speed;
  speed	= speed < -255 ? -255 : speed;

  if(speed >= 0)
  {
#ifdef LOOL_PORT_DEFINED
    LOOL_Port::dWrite2(HIGH);
    LOOL_Port::aWrite1(speed);
#else /* LOOL_PORT_DEFINED */
    digitalWrite(dc_dir_pin,HIGH);
    analogWrite(dc_pwm_pin,speed);
#endif/* LOOL_PORT_DEFINED */
  }
  else
  {
#ifdef LOOL_PORT_DEFINED
    LOOL_Port::dWrite2(LOW);
    LOOL_Port::aWrite1(-speed);
#else /* LOOL_PORT_DEFINED */
    digitalWrite(dc_dir_pin,LOW);
    analogWrite(dc_pwm_pin,-speed);
#endif/* LOOL_PORT_DEFINED */
  }
}

/**
 * @par Function
 *   stop
 * @par Description
 *   Stop the rotation of the motor
 * @par Output
 *   None
 * return
 *   None
 * @par Others
 *   None
 */
void LOOL_DCMotor::stop(void)
{
  LOOL_DCMotor::run(0);
}
