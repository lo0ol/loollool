/**
 * @par Copyright (C), 2012-2015, loollool
 * @class LOOL_Stepper
 * @brief    Driver for Stepper device.
 * @file    LOOL_Stepper.h
 * @author  sean
 * @version V1.0.0
 * @date    2015/11/18
 * @brief   Header for for Stepper module
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
 * This file is a drive for Stepper module device, It supports Stepper module 
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
 */
#ifndef LOOL_Stepper_h
#define LOOL_Stepper_h
#include "LOOL_Port.h"

#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
 #include "stdlib.h"
 #include "wiring.h"
#endif


// These defs cause trouble on some versions of Arduino
#undef round

/////////////////////////////////////////////////////////////////////
/// @class LOOL_Stepper LOOL_Stepper.h <LOOL_Stepper.h>
class LOOL_Stepper:public LOOL_Port
{
public:
  LOOL_Stepper();
  LOOL_Stepper(uint8_t port);
    
  void  moveTo(long absolute); 

  void  move(long relative);
  boolean run();
  boolean runSpeed();
  void setMaxSpeed(float speed);
  void setAcceleration(float acceleration);
  void setSpeed(float speed);
  float speed();
  long distanceToGo();
  long targetPosition();
  long currentPosition();  
  void setCurrentPosition(long position);  
  void runToPosition();
  boolean runSpeedToPosition();
  void runToNewPosition(long position);
  void disableOutputs();
  void enableOutputs();

protected:

  void computeNewSpeed();
  virtual void step();
private:
  uint8_t _dir;          // 2 or 4
  long _currentPos;     // Steps
  long _targetPos;      // Steps
  float _speed;         // Steps per second
  float _maxSpeed;
  float _acceleration;
  unsigned long _stepInterval;
  unsigned long _lastStepTime;
  /// The step counter for speed calculations
  long _n;

  /// Initial step size in microseconds
  float _c0;

  /// Last step size in microseconds
  float _cn;

  /// Min step size in microseconds based on maxSpeed
  float _cmin; // at max speed
  uint8_t _dirPin, _stpPin;
};

#endif 
