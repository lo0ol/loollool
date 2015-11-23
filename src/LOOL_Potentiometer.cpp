/**
 * @par Copyright (C), 2012-2015, loollool
 * @class   LOOL_Potentiometer
 * @brief    Driver for Me potentiometer module.
 * @file    LOOL_Potentiometer.cpp
 * @author  sean
 * @version V1.0.0
 * @date    2015/11/18
 * @brief   Driver for Me potentiometer module.
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
 *
 * @par Method List:
 *
 *    1. void     LOOL_Potentiometer::setpin(uint8_t potentiometerPin); 
 *    2. uint16_t LOOL_Potentiometer::read(void); 
 *
 * @par History:
 * <pre>
 * `<Author>`         `<Time>`        `<Version>`        `<Descr>`
 * Sean         2015/11/18     1.0.0            Rebuild the old lib.
 * </pre>
 *
 * @example PotentiometerTest.ino
 */

/* Includes ------------------------------------------------------------------*/
#include "LOOL_Potentiometer.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
volatile uint8_t LOOL_Potentiometer::_potentiometerPin = 0;

/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/
#ifdef LOOL_PORT_DEFINED
/**
 * Alternate Constructor which can call your own function to map the Me potentiometer device to arduino port,
 * no pins are used or initialized here.
 * param[in]
 *   None
 */
LOOL_Potentiometer::LOOL_Potentiometer(void) : LOOL_Port(0)
{

}

/**
 * Alternate Constructor which can call your own function to map the Me potentiometer device to arduino port
 * param[in]
 *   port - RJ25 port from PORT_1 to M2
 */
LOOL_Potentiometer::LOOL_Potentiometer(uint8_t port) : LOOL_Port(port)
{

}
#else // LOOL_PORT_DEFINED
/**
 * Alternate Constructor which can call your own function to map the Me potentiometer device to arduino port
 * param[in]
 *   potentiometerPin - arduino port for potentiometer output port
 */
LOOL_Potentiometer::LOOL_Potentiometer(uint8_t potentiometerPin)
{
  _potentiometerPin = potentiometerPin;
  pinMode(_potentiometerPin, INPUT);
}
#endif // LOOL_PORT_DEFINED 
/**
 * @par Function
 *    setpin
 * @par Description
 *    Reset the potentiometer device available PIN by its arduino port.
 * param[in]
 *   potentiometerPin - arduino port for potentiometer output port
 * @par Output
 *    None
 * @par Return
 *    None
 * @par Others
 *    None
 */
void LOOL_Potentiometer::setpin(uint8_t potentiometerPin)
{
  _potentiometerPin = potentiometerPin;
  pinMode(_potentiometerPin, INPUT);
#ifdef LOOL_PORT_DEFINED
  s2 = potentiometerPin;
#endif // LOOL_PORT_DEFINED
}

/**
 * @par Function
 *    read()
 * @par Description
 *    Read DAC value of Me potentiometer module.
 * param[in]
 *    None
 * @par Output
 *    None
 * @par Return
 *    The value of potentiometer device(0-1024)
 * @par Others
 *    None
 */
uint16_t LOOL_Potentiometer::read(void)
{
#ifdef LOOL_PORT_DEFINED
  return(LOOL_Port::aRead2() );
#else // LOOL_PORT_DEFINED
  return analogRead(_potentiometerPin);
#endif // LOOL_PORT_DEFINED
}

