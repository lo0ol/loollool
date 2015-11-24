/**
 * @par Copyright (C), 2012-2015, loollool
 * @class   LOOL_IMU
 * @brief    Driver for LOOL IMU module.
 * @file    LOOL_IMU.h
 * @author  sean & Mr.K
 * @version V1.0.0
 * @date    2015/11/18
 * @brief   Header for LOOL IMU  module.
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
 * This file is a drive for LOOL IMU module, It supports LOOL IMU V1.0 device provided
 * by loollool.
 *
 * @par Method List:
 *
 *    1. void LOOL_IMU::setpin(uint8_t AD0, uint8_t INT)
 *    2. void LOOL_IMU::begin(void)
 *    3. void LOOL_IMU::dataUpdate(void)
 *    4. float LOOL_IMU::getACC(uint8_t axis)
 *    5. float LOOL_IMU::getGYRO(uint8_t axis)
 *    6. float LOOL_IMU::getAngle(uint8_t axis)
 *    7. void LOOL_IMU::IMU_Update(void)
 *    8. void LOOL_IMU::deviceCalibration(uint8_t deviceCali)
 *    9. int8_t LOOL_IMU::writeReg(int16_t reg, uint8_t data)
 *   10. int8_t LOOL_IMU::readData(uint8_t start, uint8_t *buffer, uint8_t size)
 *   11. int8_t LOOL_IMU::writeData(uint8_t start, const uint8_t *pData, uint8_t size)
 *
 * @par History:
 * <pre>
 * `<Author>`         `<Time>`        `<Version>`        `<Descr>`
 *  Sean             2015/11/9          1.0.0         rebuild the old lib.
 * </pre>
 *
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef LOOL_IMU_H
#define LOOL_IMU_H

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stdbool.h>
#include <arduino.h>
#include "LOOL_Config.h"
#ifdef LOOL_PORT_DEFINED
#include "LOOL_Port.h"
#endif // LOOL_PORT_DEFINED

/* Exported macro ------------------------------------------------------------*/
#define I2C_ERROR                  (-1)
#define GYRO_DEFAULT_ADDRESS       (0x68)
#define ACC_1G                     9.80665f
#define IMU_KP                     1.5f
#define IMU_KI                     0.0005f//0.0005f  
#define ACC_CALIBRATION            0X01
#define GYRO_CALIBRATION           0X02
#define X                          0
#define Y                          1
#define Z                          2
/**
 * Class: LOOL_IMU
 * @par Description
 * Declaration of Class LOOL_IMU
 */
#ifndef LOOL_PORT_DEFINED
class LOOL_IMU
#else // !LOOL_PORT_DEFINED
class LOOL_IMU : public LOOL_Port
#endif // !LOOL_PORT_DEFINED
{
public:
#ifdef LOOL_PORT_DEFINED
/**
 * Alternate Constructor which can call your own function to map the LOOL_Compass to arduino port,
 * no pins are used or initialized here
 */
  LOOL_IMU(void);

/**
 * Alternate Constructor which can call your own function to map the LOOL_Compass to arduino port,
 * no pins are used or initialized here, but PWM frequency set to 976 Hz
 * param[in]
 *   port - RJ25 port from PORT_1 to M2
 */
  LOOL_IMU(uint8_t port);

/**
 * Alternate Constructor which can call your own function to map the LOOL_Compass to arduino port
 * and change the i2c device address
 * no pins are used or initialized here, but PWM frequency set to 976 Hz
 * param[in]
 *   port - RJ25 port from PORT_1 to M2
 * param[in]
 *   address - the i2c address you want to set
 */
  LOOL_IMU(uint8_t port, uint8_t address);
#else
/**
 * Alternate Constructor which can call your own function to map the _AD0 and _INT to arduino port,
 * no pins are used or initialized here
 * param[in]
 *   _AD0 - arduino gpio number
 * param[in]
 *   _INT - arduino gpio number
 */
  LOOL_IMU(uint8_t AD0, uint8_t INT);

/**
 * Alternate Constructor which can call your own function to map the _AD0 and _INT to arduino port
 * and change the i2c device address, no pins are used or initialized here
 * param[in]
 *   _AD0 - arduino gpio number
 * param[in]
 *   _INT - arduino gpio number
 * param[in]
 *   address - the i2c address you want to set
 */
  LOOL_IMU(uint8_t AD0, uint8_t INT, uint8_t address);
#endif  //  LOOL_PORT_DEFINED
/**
 * @par Function
 *   setpin
 * @par Description
 *   Set the PIN of the button module.
 * param[in]
 *   AD0 - pin mapping for arduino
 * param[in]
 *   INT - pin mapping for arduino
 * @par Output
 *   None
 * return
 *   None.
 * @par Others
 *   Set global variable _AD0, _INT, s1 and s2
 */
  void setpin(uint8_t AD0, uint8_t INT);

/**
 * @par Function
 *   begin
 * @par Description
 *   Initialize the LOOL_Gyro.
 * param[in]
 *   None
 * @par Output
 *   None
 * return
 *   None
 * @par Others
 *   You can check the MPU6050 datasheet for the registor address.
 */
  void begin(void);

/**
 * @par Function
 *   update
 * @par Description
 *   Update acceleration, angular rate and angle of 3 axis.
 * param[in]
 *   None
 * @par Output
 *   None
 * return
 *   None
 * @par Others
 *   The angle values are calculated by complementary filter.
 *   The time constant of filter is set to 0.5 second, but period dt is not a constant, 
 *   so the filter coefficient will be calculated dynamically.
 */
  void dataUpdate(void);

  /**
 * @par Function
 *   getACC
 * @par Description
 *   get acceleration of 3 axis.
 * param[in]
 *   axis
 * @par Output
 *   acceleration of any axis 
 * return
 *   acceleration of any axis
 * @par Others
 *   the unit of acceleration is m/s2
 */
  float getACC(uint8_t axis);
  
  /**
 * @par Function
 *   getGYRO
 * @par Description
 *   get angular rate of 3 axis.
 * param[in]
 *   axis
 * @par Output
 *   angular rate of any axis 
 * return
 *   angular rate of any axis
 * @par Others
 *   the unit of angular rate is rad/s
 */
  float getGYRO(uint8_t axis);
/**
 * @par Function
 *   getAngle
 * @par Description
 *   get angle of 3 axis.
 * param[in]
 *   axis
 * @par Output
 *   angle of any axis 
 * return
 *   angle of any axis
 * @par Others
 *   the unit of angular rate is degree
 */
  float getAngle(uint8_t axis);

private:
  static volatile uint8_t  _AD0;
  static volatile uint8_t  _INT;
  float  angle[3];                                                     //unit   degree
  float   gyro[3];                                                     //unit   rad/s
  float   acc[3];                                                      //unit   m/s2
  int16_t  gyroOffs[3];                                                //gyroscope   ADC
  int16_t  accOffs[3];                                                 //acc         ADC
  uint8_t i2cData[14];
  uint8_t Device_Address;
  
  float ex_int = 0, ey_int = 0, ez_int = 0;                           //P error of 3 axis
  float q0 = 1, q1 = 0, q2 = 0, q3 = 0;                               //quaternion
  float q0_yaw = 1, q1_yaw = 0, q2_yaw = 0, q3_yaw = 0;               //yaw axis quaternion
  
 /**
 * @par Function
 *   IMU_Update
 * @par Description
 *   get angle of 3 axis by quaternion.
 *   we have corrected 3 reference axis to keep down the drift of gyroscope
 * param[in]
 *   None
 * @par Output
 *   angle of 3 axis 
 * return
 *   None
 * @par Others
 *   we use quaternion method to get angle, so X axis is -180 degree to +180 degree
 *                                             Y axis is -90  degree to +90  degree
 *                                             Z axis is +180 degree to +180 degree
 */
  void IMU_Update(void);
  
/**
 * @par Function
 *   deviceCalibration
 * @par Description
 *   Calibration function for the LOOL_IMU. 
 * param[in]
 *   IMU device(acc, gyro or both)
 * @par Output
 *   acc offset and gyro offset
 * return
 *   None.
 * @par Others
 *   The calibration function will be called in initial process, please keep the 
 *   device in a rest status at that time.
 */
  void deviceCalibration(uint8_t deviceCali);

/**
 * @par Function
 *   writeReg
 * @par Description
 *   Write the registor of i2c device.
 * param[in]
 *   reg - the address of registor.
 * param[in]
 *   data - the data that will be written to the registor.
 * @par Output
 *   None
 * return
 *   Return the error code.
 *   the definition of the value of variable return_value:
 *   0:success
 *   1:BUFFER_LENGTH is shorter than size
 *   2:address send, nack received
 *   3:data send, nack received
 *   4:other twi error
 *   refer to the arduino official library twi.c
 * @par Others
 *   To set the registor for initializing.
 */
  int8_t writeReg(int16_t reg, uint8_t data);

/**
 * @par Function
 *   readData
 * @par Description
 *   Write the data to i2c device.
 * param[in]
 *   start - the address which will write the data to.
 * param[in]
 *   pData - the head address of data array.
 * param[in]
 *   size - set the number of data will be written to the devide.
 * @par Output
 *   None
 * return
 *   Return the error code.
 *   the definition of the value of variable return_value:
 *   0:success
 *   1:BUFFER_LENGTH is shorter than size
 *   2:address send, nack received
 *   3:data send, nack received
 *   4:other twi error
 *   refer to the arduino official library twi.c
 * @par Others
 *   Calling the official i2c library to read data.
 */
  int8_t readData(uint8_t start, uint8_t *buffer, uint8_t size);

/**
 * @par Function
 *   writeData
 * @par Description
 *   Write the data to i2c device.
 * param[in]
 *   start - the address which will write the data to.
 * param[in]
 *   pData - the head address of data array.
 * param[in]
 *   size - set the number of data will be written to the devide.
 * @par Output
 *   None
 * return
 *   Return the error code.
 *   the definition of the value of variable return_value:
 *   0:success
 *   1:BUFFER_LENGTH is shorter than size
 *   2:address send, nack received
 *   3:data send, nack received
 *   4:other twi error
 *   refer to the arduino official library twi.c
 * @par Others
 *   Calling the official i2c library to write data.
 */
  int8_t writeData(uint8_t start, const uint8_t *pData, uint8_t size);
  
};
#endif //  MeGyro_H
