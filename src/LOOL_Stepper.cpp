/**
 * @par Copyright (C), 2012-2015, loollool
 * @class LOOL_Stepper
 * @brief    Driver for Stepper device.
 * @file    LOOL_Stepper.cpp
 * @author  sean
 * @version V1.0.0
 * @date    2015/11/18
 * @brief   Driver for Stepper device.
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
 * This file is a drive for Stepper device, It supports Stepper device
 * provided by the loollool.
 *
 * @par Method List:
 *
 *    1. void LOOL_Stepper::moveTo(long absolute)
 *    2. void LOOL_Stepper::move(long relative)
 *    3. boolean LOOL_Stepper::run();
 *    4. boolean LOOL_Stepper::runSpeed();
 *    5. void LOOL_Stepper::setMaxSpeed(float speed);
 *    6. void LOOL_Stepper::setAcceleration(float acceleration);
 *    7. void LOOL_Stepper::setSpeed(float speed);
 *    8. float LOOL_Stepper::speed();
 *    9. long LOOL_Stepper::distanceToGo();
 *    10. long LOOL_Stepper::targetPosition();
 *    11. long LOOL_Stepper::currentPosition();  
 *    12. void LOOL_Stepper::setCurrentPosition(long position);  
 *    13. void LOOL_Stepper::runToPosition();
 *    14. boolean LOOL_Stepper::runSpeedToPosition();
 *    15. void LOOL_Stepper::runToNewPosition(long position);
 *    16. void LOOL_Stepper::disableOutputs();
 *    17. void LOOL_Stepper::enableOutputs();
 *
 * @par History:
 * <pre>
 * `<Author>`         `<Time>`        `<Version>`        `<Descr>`
 * sean         2015/11/18     1.0.0            Rebuild the old lib.
 * </pre>
 *
 * @example Humiture.ino
 */
#include "LOOL_Stepper.h"

typedef enum
{
  DIRECTION_CCW = 0,  ///< Clockwise
  DIRECTION_CW  = 1   ///< Counter-Clockwise
} Direction;

LOOL_Stepper::LOOL_Stepper(): LOOL_Port(0)
{

}

LOOL_Stepper::LOOL_Stepper(uint8_t port): LOOL_Port(port)
{
  _currentPos = 0;
  _targetPos = 0;
  _acceleration = 0;
  _lastStepTime = micros();
  _speed = 0;
  _dir = DIRECTION_CW;
  setCurrentPosition(0);
  pinMode(s1,OUTPUT);
  pinMode(s2,OUTPUT);
}

void LOOL_Stepper::moveTo(long absolute)
{
  if (_targetPos != absolute)
  {
    _targetPos = absolute;
    computeNewSpeed();
  }
}

void LOOL_Stepper::move(long relative)
{
  moveTo(_currentPos + relative);
}

boolean LOOL_Stepper::runSpeed()
{
  // Dont do anything unless we actually have a step interval
  if (!_stepInterval)
  {
    return false;
  }

  if (micros() - _lastStepTime > _stepInterval)
  {
    if (_dir == DIRECTION_CW)
    {
      // Clockwise
      _currentPos += 1;
    }
    else
    {
      // Anticlockwise  
      _currentPos -= 1;
    }
    step();
    _lastStepTime = micros();
    return true;
  }
  else
  {
    return false;
  }
}

long LOOL_Stepper::distanceToGo()
{
  return _targetPos - _currentPos;
}

long LOOL_Stepper::targetPosition()
{
  return _targetPos;
}

long LOOL_Stepper::currentPosition()
{
  return _currentPos;
}

void LOOL_Stepper::setCurrentPosition(long position)
{
  _targetPos = _currentPos = position;
  _n = 0;
  _stepInterval = 0;
}

void LOOL_Stepper::computeNewSpeed()
{
  long distanceTo = distanceToGo();
  long stepsToStop = (long)((_speed * _speed) / (2.0 * _acceleration));
  if (distanceTo == 0 && stepsToStop <= 1)
  {
    // We are at the target and its time to stop
    _stepInterval = 0;
    _speed = 0.0;
    _n = 0;
    return;
  }

  if (distanceTo > 0)
  {
    // We are anticlockwise from the target
    // Need to go clockwise from here, maybe decelerate now
    if (_n > 0)
    {
      // Currently accelerating, need to decel now? Or maybe going the wrong way?
      if ((stepsToStop >= distanceTo) || _dir == DIRECTION_CCW)
      {
        _n = -stepsToStop; // Start deceleration
      }
    }
    else if (_n < 0)
    {
      // Currently decelerating, need to accel again?
      if ((stepsToStop < distanceTo) && _dir == DIRECTION_CW)
      {
        _n = -_n; // Start accceleration
      }
    }
  }
  else if (distanceTo < 0)
  {
    // We are clockwise from the target
    // Need to go anticlockwise from here, maybe decelerate
    if (_n > 0)
    {
      // Currently accelerating, need to decel now? Or maybe going the wrong way?
      if ((stepsToStop >= -distanceTo) || _dir == DIRECTION_CW)
      {
        _n = -stepsToStop; // Start deceleration
      }
    }
    else if (_n < 0)
    {
      // Currently decelerating, need to accel again?
      if ((stepsToStop < -distanceTo) && _dir == DIRECTION_CCW)
      {
        _n = -_n; // Start accceleration
      }
    }
  }

  // Need to accelerate or decelerate
  if (_n == 0)
  {
    // First step from stopped
    _cn = _c0;
    _dir = (distanceTo > 0) ? DIRECTION_CW : DIRECTION_CCW;
  }
  else
  {
    // Subsequent step. Works for accel (n is +_ve) and decel (n is -ve).
    _cn = _cn - ((2.0 * _cn) / ((4.0 * _n) + 1)); // Equation 13
    _cn = max(_cn, _cmin);
  }
  _n++;
  _stepInterval = _cn;
  _speed = 1000000.0 / _cn;
  if (_dir == DIRECTION_CCW)
  {
    _speed = -_speed;
  }
}

boolean LOOL_Stepper::run()
{
  if((_speed == 0.0) || (distanceToGo() == 0))
  {
    return false;
  }

  if (runSpeed())
  {
	computeNewSpeed();
    return true;
  }
}

void LOOL_Stepper::setMaxSpeed(float speed)
{
  if (_maxSpeed != speed)
  {
    _maxSpeed = speed;
    _cmin = 1000000.0 / speed;
    // Recompute _n from current speed and adjust speed if accelerating or cruising
    if (_n > 0)
    {
      _n = (long)((_speed * _speed) / (2.0 * _acceleration)); // Equation 16
      computeNewSpeed();
    }
  }
}

void LOOL_Stepper::setAcceleration(float acceleration)
{
  if(acceleration == 0.0)
  {
    return;
  }
  if(_acceleration != acceleration)
  {
    _n = _n * (_acceleration / acceleration);
    //	_c0 = sqrt(2.0 / acceleration) * 1000000.0;
    // Accelerates at half the expected rate. Why?
    _c0 = sqrt(1.0/acceleration) * 1000000.0;
    _acceleration = acceleration;
    computeNewSpeed();
  }
}

void LOOL_Stepper::setSpeed(float speed)
{
  if (speed == _speed)
  {
    return;
  }
  speed = constrain(speed, -_maxSpeed, _maxSpeed);
  if (speed == 0.0)
  {
    _stepInterval = 0;
  }

  else
  {
    _stepInterval = fabs(1000000.0 /speed);
    _dir = (speed > 0.0) ? DIRECTION_CW : DIRECTION_CCW;
  }
  _speed = speed;
}

float LOOL_Stepper::speed()
{
  return _speed;
}

void LOOL_Stepper::step()
{
  if(_dir == DIRECTION_CW)
  {
    digitalWrite(s1,LOW);
  }
  else
  {
    digitalWrite(s1,HIGH);
  }
  digitalWrite(s2, HIGH);
  delayMicroseconds(1);
  digitalWrite(s2, LOW);
}

// Blocks until the target position is reached
void LOOL_Stepper::runToPosition()
{
  while (run())
  {
    ;
  }
}

boolean LOOL_Stepper::runSpeedToPosition()
{
  if (_targetPos == _currentPos)
  {
    return false;
  }
  if (_targetPos >_currentPos)
  {
	_dir = DIRECTION_CW;
  }
  else
  {
	_dir = DIRECTION_CCW;
  }
  return runSpeed();
}

// Blocks until the new target position is reached
void LOOL_Stepper::runToNewPosition(long position)
{
  moveTo(position);
  runToPosition();
}

