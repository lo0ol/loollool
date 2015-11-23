/**
 * @par Copyright (C), 2012-2015, loollool
 * @class LOOL_Bluetooth
 * @brief    Driver for  Bluetooth device.
 * @file    LOOL_Bluetooth.cpp
 * @author  sean
 * @version V1.0.0
 * @date    2015/09/09
 * @brief   Driver for  Bluetooth device.
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
 * This file is a drive for LOOL Bluetooth device, The bluetooth inherited the 
 * LOOL_Serial class from SoftwareSerial.
 *
 * @par Method List:
 *  inherited from LOOL_Serial
 *
 * @par History:
 * <pre>
 * `<Author>`         `<Time>`        `<Version>`        `<Descr>`
 * sean         2015/11/19     1.0.0            Rebuild the old lib.
 * </pre>
 *
 * @example SlaveBluetoothBySoftSerialTest.ino
 */
#include "LOOL_Bluetooth.h"

#ifdef LOOL_PORT_DEFINED
/**
 * Alternate Constructor which can call your own function to map the Bluetooth to arduino port,
 * no pins are used or initialized here.
 * param[in]
 *   None
 */
LOOL_Bluetooth::LOOL_Bluetooth() : LOOL_Serial(0)
{

}

/**
 * Alternate Constructor which can call your own function to map the Bluetooth to arduino port,
 * If the hardware serial was selected, we will used the hardware serial.
 * param[in]
 *   port - RJ25 port from PORT_1 to M2
 */
LOOL_Bluetooth::LOOL_Bluetooth(uint8_t port) : LOOL_Serial(port)
{

}
#else // LOOL_PORT_DEFINED
/**
 * Alternate Constructor which can call your own function to map the Bluetooth to arduino port,
 * If the hardware serial was selected, we will used the hardware serial.
 * param[in]
 *   receivePin - the rx pin of serial(arduino port)
 * param[in]
 *   transmitPin - the tx pin of serial(arduino port)
 * param[in]
 *   inverse_logic - Whether the Serial level need inv.
 */
LOOL_Bluetooth::LOOL_Bluetooth(uint8_t receivePin, uint8_t transmitPin, bool inverse_logic)\
                        : LOOL_Serial(receivePin, transmitPin, inverse_logic)
{

}
#endif // LOOL_PORT_DEFINED

