/**
 * \par Copyright (C), 2012-2015, LOOLLOOL
 * @file    PIRMotionSensorTest.ino
 * @author  Sean
 * @version V1.0.0
 * @date    2015/09/01
 * @brief   Description: this file is sample program for PIR Motion module.
 *
 * Function List:
 * 1. void    LOOL_PIRMotionSensor::SetPirMotionMode(uint8_t ModePin)
 * 2. bool    LOOL_PIRMotionSensor::isHumanDetected();
 *
 * \par History:
 * <pre>
 * `<Author>`         `<Time>`        `<Version>`        `<Descr>`
 * sean         2015/11/18     1.0.0            Rebuild the old lib.
 * </pre>
 */

/* Includes ------------------------------------------------------------------*/
#include "LOOL_Smart.h"

/* Private variables ---------------------------------------------------------*/
LOOL_PIRMotionSensor PIRsensor(PORT_3);

void setup()
{
  Serial.begin(9600);
  PIRsensor.SetPirMotionMode(1);   //Continuous Trigger mode
}

void loop()
{
  if(PIRsensor.isHumanDetected() )
  {
    Serial.println("People Motion Detected");
  }
  delay(20);
}

