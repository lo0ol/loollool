/**
 * @par Copyright (C), 2012-2015, loollool
 * @class LOOL_Temperature
 * @brief    Driver for temperature sensor device.
 * @file    LOOL_Temperature.cpp
 * @author  sean
 * @version V1.0.0
 * @date    2015/11/18
 * @brief   Driver for temperature sensor device.
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
 * This file is a drive for temperature sensor device, It supports temperature sensor
 * 18B20 provided by the loollool.
 *
 * @par Method List:
 *
 *    1. void LOOL_Temperature::reset(uint8_t port)
 *    2. void LOOL_Temperature::reset(uint8_t port, uint8_t slot)
 *    3. void LOOL_Temperature::setpin(uint8_t port)
 *    4. float LOOL_Temperature::temperature(void)
 *
 * @par History:
 * <pre>
 * `<Author>`         `<Time>`        `<Version>`        `<Descr>`
 * sean         2015/11/18     1.0.0            Rebuild the old lib.
 * </pre>
 *
 * @example TemperatureTest.ino
 */
#include "LOOL_Temperature.h"

volatile uint8_t       LOOL_Temperature::_DataPin             = 0;

#ifdef LOOL_PORT_DEFINED
/**
 * Alternate Constructor which can call your own function to map the temperature sensor to arduino port,
 * no pins are used or initialized here.
 * param[in]
 *   None
 */
LOOL_Temperature::LOOL_Temperature(void) : LOOL_Port()
{

}

/**
 * Alternate Constructor which can call your own function to map the temperature sensor to arduino port,
 * the slot2 pin will be used here since specify slot is not be set.
 * param[in]
 *   port - RJ25 port from PORT_1 to M2
 */
LOOL_Temperature::LOOL_Temperature(uint8_t port) : LOOL_Port(port)
{
  _DataPin = s2;
  _ts.reset(s2);
}

/**
 * Alternate Constructor which can call your own function to map the temperature sensor to arduino port.
 * param[in]
 *   port - RJ25 port from PORT_1 to M2
 * param[in]
 *   slot - SLOT1 or SLOT2
 */
LOOL_Temperature::LOOL_Temperature(uint8_t port, uint8_t slot) : LOOL_Port(port)
{
  LOOL_Port::reset(port, slot);
  _DataPin = SLOT2 ? s2 : s1;
  _ts.reset(slot == SLOT2 ? s2 : s1);
}
#else //LOOL_PORT_DEFINED
/**
 * Alternate Constructor which can call your own function to map the temperature sensor to arduino port.
 * param[in]
 *   port - arduino port
 */
LOOL_Temperature::LOOL_Temperature(uint8_t port)
{
  _DataPin = port;
  _ts.reset(port);
}
#endif //LOOL_PORT_DEFINED

/**
 * @par Function
 *   reset
 * @par Description
 *   Reset the available PIN for temperature sensor by its RJ25 port,
 *   the slot2 pin will be used here since specify slot is not be set
 * param[in]
 *   port - RJ25 port from PORT_1 to M2
 * @par Output
 *   None
 * return
 *   None
 * @par Others
 *   None
 */
void LOOL_Temperature::reset(uint8_t port)
{
  LOOL_Port::reset(port);
  _ts.reset(s2);
}

/**
 * @par Function
 *   reset
 * @par Description
 *   Reset the available PIN for temperature sensor by its RJ25 port.
 * param[in]
 *   port - RJ25 port from PORT_1 to M2
 * param[in]
 *   slot - SLOT1 or SLOT2
 * @par Output
 *   None
 * return
 *   None
 * @par Others
 *   None
 */
void LOOL_Temperature::reset(uint8_t port, uint8_t slot)
{
  LOOL_Port::reset(port, slot);
  _ts.reset(slot == SLOT2 ? s2 : s1);
}

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
void LOOL_Temperature::setpin(uint8_t port)
{
  _DataPin = port;
  _ts.reset(port);
}

/**
 * @par Function
 *   temperature
 * @par Description
 *   Get the celsius of temperature
 * @par Output
 *   None
 * return
 *   The temperature value get from the sensor.
 * @par Others
 *   None
 */
float LOOL_Temperature::temperature(void)
{
  byte  i;
  byte  present = 0;
  byte  type_s;
  byte  data[12];
  byte	addr[8];
  float celsius;
  long  time;

  _ts.reset();
  _ts.skip();
  _ts.write(STARTCONVO);       // start conversion, with parasite power on at the end
  time = millis();
  while(!_ts.readIO() && (millis() - time) < 750)
  {
    ;
  }

  present = _ts.reset();
  _ts.skip();
  _ts.write(READSCRATCH);
  for(i = 0; i < 5; i++)      // we need 9 bytes
  {
    data[i] = _ts.read();
  }

  int16_t rawTemperature = (data[1] << 8) | data[0];

  return( (float)rawTemperature * 0.0625); // 12 bit
}
