/**
 * @par Copyright (C), 2012-2015, loollool
 * @brief    Driver for lool_Car DC Motor.
 * \file    LOOL_CarMotor.h
 * @author  sean
 * @version V1.0.0
 * @date    2015/11/18
 * @brief   Driver for lool_Car DC Motor.
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
 * This file is Hardware adaptation layer between lool_Car board and all
 * loollool drives
 *
 * @par History:
 * <pre>
 * `<Author>`         `<Time>`        `<Version>`        `<Descr>`
 * sean         2015/11/18     1.0.0            Rebuild the old lib.
 * </pre>
 */

#include "LOOL_CarMotor.h"

#ifdef LOOL_PORT_DEFINED
LOOL_CarMotor::LOOL_CarMotor(uint8_t port) : LOOL_DCMotor(port)
{

}

void LOOL_CarMotor::move(int direction, int speed)
{
  int leftSpeed = 0;
  int rightSpeed = 0;
  if(direction==1)
  {
    leftSpeed = -speed;
    rightSpeed = speed;
  }
  else if(direction==2)
  {
    leftSpeed = speed;
    rightSpeed = -speed;
  }
  else if(direction==3)
  {
    leftSpeed = speed;
    rightSpeed = speed;
  }
  else if(direction==4)
  {
    leftSpeed = -speed;
    rightSpeed = -speed;
  }
  LOOL_DCMotor::reset(M1);
  LOOL_DCMotor::run(leftSpeed);
  LOOL_DCMotor::reset(M2);
  LOOL_DCMotor::run(rightSpeed);
}
#endif //LOOL_PORT_DEFINED

