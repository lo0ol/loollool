/**
 * \par Copyright (C), 2012-2015, LOOLLOOL
 * @file    DCMotorDriverTest.ino
 * @author  Sean
 * @version V1.0.0
 * @date    2015/09/09
 * @brief   Description: this file is sample code for DC motor device.
 *
 * Function List:
 *    1. void LOOL_DCMotor::run(int16_t speed)
 *    2. void LOOL_DCMotor::stop(void)
 *
 * @par History:
 * <pre>
 * `<Author>`         `<Time>`        `<Version>`        `<Descr>`
 * sean         2015/09/09     1.0.0            Rebuild the old lib.
 * </pre>
 */
#include "LOOL_Smart.h"

LOOL_DCMotor motor1(PORT_1);

LOOL_DCMotor motor2(PORT_2);

LOOL_DCMotor motor3(M1);

LOOL_DCMotor motor4(M2);

uint8_t motorSpeed = 100;

void setup()
{
}

void loop()
{
  motor1.run(motorSpeed); /* value: between -255 and 255. */
  motor2.run(motorSpeed); /* value: between -255 and 255. */
  motor3.run(motorSpeed);
  motor4.run(motorSpeed);
  delay(2000);
  motor1.stop();
  motor2.stop();
  motor3.stop();
  motor4.stop();
  delay(100);
  motor1.run(-motorSpeed);
  motor2.run(-motorSpeed);
  motor3.run(-motorSpeed);
  motor4.run(-motorSpeed);
  delay(2000);
  motor1.stop();
  motor2.stop();
  motor3.stop();
  motor4.stop();
  delay(2000);
}

