/**
 * @par Copyright (C), 2012-2015, loollool
 * @class LOOL_Humiture
 * @brief    Driver for humiture sensor device.
 * @file    LOOL_HumitureSensor.cpp
 * @author  sean
 * @version V1.0.0
 * @date    2015/11/18
 * @brief   Driver for humiture sensor device.
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
 * This file is a drive for humiture sensor device, It supports humiture sensor
 * provided by the loollool.
 *
 * @par Method List:
 *
 *    1. void LOOL_Humiture::setpin(uint8_t port)
 *    2. void LOOL_Humiture::update(void)
 *    3. uint8_t LOOL_Humiture::getHumidity(void)
 *    4. uint8_t LOOL_Humiture::getTemperature(void)
 *    5. uint8_t LOOL_Humiture::getValue(uint8_t index)
 *
 * @par History:
 * <pre>
 * `<Author>`         `<Time>`        `<Version>`        `<Descr>`
 * sean         2015/11/18     1.0.0            Rebuild the old lib.
 * </pre>
 *
 * @example Humiture.ino
 */
#include "LOOL_HumitureSensor.h"

#ifdef LOOL_PORT_DEFINED
/**
 * Alternate Constructor which can call your own function to map the humiture sensor to arduino port,
 * no pins are used or initialized here.
 * param[in]
 *   None
 */
LOOL_Humiture::LOOL_Humiture(void) : LOOL_Port(0)
{

}

/**
 * Alternate Constructor which can call your own function to map the temperature sensor to arduino port,
 * the slot2 pin will be used here since specify slot is not be set.
 * param[in]
 *   port - RJ25 port from PORT_1 to M2
 */
LOOL_Humiture::LOOL_Humiture(uint8_t port) : LOOL_Port(port)
{

}
#else // LOOL_PORT_DEFINED
/**
 * @par Function
 *   setpin
 * @par Description
 *   Reset available PIN for temperature sensor by its arduino port.
 * param[in]
 *   port - arduino port(should digital pin)
 * @par Output
 *   None
 * return
 *   None
 * @par Others
 *   None
 */
LOOL_Humiture::LOOL_Humiture(uint8_t port)
{
  _DataPin = port;
}
#endif // LOOL_PORT_DEFINED

/**
 * @par Function
 *   setpin
 * @par Description
 *   Reset available PIN for temperature sensor by its arduino port.
 * param[in]
 *   port - arduino port(should digital pin)
 * @par Output
 *   None
 * return
 *   None
 * @par Others
 *   None
 */
void LOOL_Humiture::setpin(uint8_t port)
{
  _DataPin = port;
  s2 = _DataPin;
}

/**
 * @par Function
 *   update
 * @par Description
 *   Use this function to update the sensor data
 * @par Output
 *   None
 * return
 *   None
 * @par Others
 *   None
 */
void LOOL_Humiture::update(void)
{
  uint8_t data[5] = {0};
  unsigned long Time, datatime;
  
#ifdef LOOL_PORT_DEFINED
  LOOL_Port::dWrite2(LOW);
  delay(20);
  LOOL_Port::dWrite2(HIGH);
  delayMicroseconds(40);
  LOOL_Port::dWrite2(LOW);
#else // LOOL_PORT_DEFINED
  pinMode(_DataPin,OUTPUT);
  digitalWrite(_DataPin,LOW);
  delay(20);
  digitalWrite(_DataPin,HIGH);
  delayMicroseconds(40);
  digitalWrite(_DataPin,LOW);
#endif // LOOL_PORT_DEFINED
  Time = millis();
#ifdef LOOL_PORT_DEFINED
  while(LOOL_Port::dRead2() != HIGH)
#else // LOOL_PORT_DEFINED
  pinMode(_DataPin,INPUT);
  while(digitalRead(_DataPin) != HIGH)
#endif // LOOL_PORT_DEFINED
  {
    if( ( millis() - Time ) > 2)
    {
      Humidity = 0;
      Temperature = 0;
      break;
    }
  }

  Time = millis();
  
#ifdef LOOL_PORT_DEFINED
  while(LOOL_Port::dRead2() != LOW)
#else // LOOL_PORT_DEFINED
  pinMode(_DataPin,INPUT);
  while(digitalRead(_DataPin) != LOW)
#endif // LOOL_PORT_DEFINED
  {
    if( ( millis() - Time ) > 2)
    {
      break;
    }
  }

  for(int16_t i=0;i<40;i++)
  {
  	Time = millis();
#ifdef LOOL_PORT_DEFINED
    while(LOOL_Port::dRead2() == LOW)
#else // LOOL_PORT_DEFINED
    pinMode(_DataPin,INPUT);
    while(digitalRead(_DataPin) == LOW)
#endif // LOOL_PORT_DEFINED
    {
      if( ( millis() - Time ) > 2)
      {
        break;
      }
    }

    datatime = micros();
    Time = millis();
#ifdef LOOL_PORT_DEFINED
    while(LOOL_Port::dRead2() == HIGH)
#else // LOOL_PORT_DEFINED
    pinMode(_DataPin,INPUT);
    while(digitalRead(_DataPin) == HIGH)
#endif // LOOL_PORT_DEFINED
    {
      if( ( millis() - Time ) > 2 )
      {
        break;
      }
    }

    if ( micros() - datatime > 40 )
    {
      data[i/8] <<= 1;
      data[i/8] |= 0x01;
    }
    else
    {
      data[i/8] <<= 1;
    }
  }
   
  if( (data[0] + data[2]) == data[4] )
  {
  	Humidity = data[0];
    Temperature = data[2];
  }
}

/**
 * @par Function
 *   getHumidity
 * @par Description
 *   Use this function to Get the Humidity data
 * @par Output
 *   None
 * return
 *   The value of Humidity
 * @par Others
 *   None
 */
uint8_t LOOL_Humiture::getHumidity(void)
{
  return Humidity;
}

/**
 * @par Function
 *   getTemperature
 * @par Description
 *   Use this function to Get the Temperature data
 * @par Output
 *   None
 * return
 *   The value of Temperature
 * @par Others
 *   None
 */
uint8_t LOOL_Humiture::getTemperature(void)
{
  return Temperature;
}

/**
 * @par Function
 *   getValue
 * @par Description
 *   Use this function to Get the Temperature data or Humidity data
 * param[in]
 *   index - The value '0' means get the value of Humidity data and '1' used to get the
 *   Temperature data.
 * @par Output
 *   None
 * return
 *   The value of Temperature
 * @par Others
 *   None
 */
uint8_t LOOL_Humiture::getValue(uint8_t index)
{
  if(index == 0)
  {
    return Humidity;
  }
  else
  {
    return Temperature;
  }
}

