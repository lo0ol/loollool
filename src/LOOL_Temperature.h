/**
 * @par Copyright (C), 2012-2015, loollool
 * @class LOOL_Temperature
 * @brief    Driver for temperature sensor device.
 * @file    LOOL_Temperature.h
 * @author  sean
 * @version V1.0.0
 * @date    2015/11/18
 * @brief   Header for LOOL_Temperature.cpp module
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
 */
#ifndef LOOL_Temperature_H
#define LOOL_Temperature_H

#include <stdint.h>
#include <stdbool.h>
#include <arduino.h>
#include "LOOL_Config.h"
#include "LOOL_OneWire.h"

#ifdef LOOL_PORT_DEFINED
#include "LOOL_Port.h"
#endif /* LOOL_PORT_DEFINED */

/* DS18B20 commands */
#define STARTCONVO       0x44    // Tells device to take a temperature reading and put it on the scratchpad
#define COPYSCRATCH      0x48    // Copy EEPROM
#define READSCRATCH      0xBE    // Read EEPROM
#define WRITESCRATCH     0x4E    // Write to EEPROM
#define RECALLSCRATCH    0xB8    // Reload from last known
#define READPOWERSUPPLY  0xB4    // Determine if device needs parasite power
#define ALARMSEARCH      0xEC    // Query bus for devices with an alarm condition

/**
 * Class: LOOL_Temperature
 * @par Description
 * Declaration of Class LOOL_Temperature.
 */
#ifndef LOOL_PORT_DEFINED
class LOOL_Temperature
#else // !LOOL_PORT_DEFINED
class LOOL_Temperature : public LOOL_Port
#endif // !LOOL_PORT_DEFINED
{
public:
#ifdef LOOL_PORT_DEFINED
/**
 * Alternate Constructor which can call your own function to map the temperature sensor to arduino port,
 * no pins are used or initialized here.
 * param[in]
 *   None
 */
  LOOL_Temperature(void);
  
/**
 * Alternate Constructor which can call your own function to map the temperature sensor to arduino port,
 * the slot2 pin will be used here since specify slot is not be set.
 * param[in]
 *   port - RJ25 port from PORT_1 to M2
 */
  LOOL_Temperature(uint8_t port);

/**
 * Alternate Constructor which can call your own function to map the temperature sensor to arduino port.
 * param[in]
 *   port - RJ25 port from PORT_1 to M2
 * param[in]
 *   slot - SLOT1 or SLOT2
 */
  LOOL_Temperature(uint8_t port, uint8_t slot);
#else // LOOL_PORT_DEFINED
/**
 * Alternate Constructor which can call your own function to map the temperature sensor to arduino port.
 * param[in]
 *   port - arduino port
 */
  LOOL_Temperature(uint8_t port);
#endif // LOOL_PORT_DEFINED
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
  void reset(uint8_t port);

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
  void reset(uint8_t port, uint8_t slot);

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
  void setpin(uint8_t port);

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
  float temperature(void);
private:
	LOOL_OneWire _ts;
    static volatile uint8_t  _DataPin;
};

#endif

