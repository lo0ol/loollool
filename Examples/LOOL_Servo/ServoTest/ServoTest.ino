/**
 * @par Copyright (C), 2012-2015, LOOLLOOL
 * @file    ServoTest.ino
 * @author  Sean
 * @version V1.0.0
 * @date    2015/09/02
 * @brief   Description: this file is sample code for servo. Servo.h should be 
 * included before loollool header file
 * Function List:
 * 1. uint8_t Servo::attach()
 * 2. uint8_t Servo::write()
 *
 * \par History:
 * <pre>
 * <Author>     <Time>        <Version>      <Descr>
 *  Sean     2015/11/19    1.0.0          rebuild the old lib
 * </pre>
 */
#include "LOOL_Smart.h"
#include <Servo.h>

//Parts required: RJ25 Adapter and two servo 	
// RJ25 Adapter SLOT1 connect servo1,SLOT2 connect servo2,
//The  RJ25 Adapter module can connect to the port with yellow tag (PORT_3 to PROT_8). 

LOOL_Port port(PORT_3);
Servo myservo1;  // create servo object to control a servo 
Servo myservo2;  // create servo object to control another servo
int16_t servo1pin =  port.pin1();//attaches the servo on PORT_3 SLOT1 to the servo object
int16_t servo2pin =  port.pin2();//attaches the servo on PORT_3 SLOT2 to the servo object

void setup() 
{ 
  myservo1.attach(servo1pin);  // attaches the servo on servopin1
  myservo2.attach(servo2pin);  // attaches the servo on servopin2
} 

void loop() 
{ 
  myservo1.write(0);                  // sets the servo position according to the scaled value 
  myservo2.write(0);
  delay(2000);                           // waits for the servo to get there 
  myservo1.write(180);
  myservo2.write(180);
  delay(2000); 
} 
