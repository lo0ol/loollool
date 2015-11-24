/**
 * @par Copyright (C), 2012-2015, loollool
 * @class   LOOL_IMU
 * @brief    Driver for LOOL GYRO and ACC module.
 * @file    LOOL_Gyro.cpp
 * @author  sean & Mr.K
 * @version V1.0.0
 * @date    2015/11/23
 * @brief   Driver for LOOL GYRO and ACC module.
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
 * @example MeGyroTest.ino
 */
 
/* Includes ------------------------------------------------------------------*/
#include "LOOL_IMU.h"
#include "math.h"

/* Private variables ---------------------------------------------------------*/
volatile uint8_t LOOL_IMU::_AD0 = 0;
volatile uint8_t LOOL_IMU::_INT = 0;

/* Private functions ---------------------------------------------------------*/
#ifdef LOOL_PORT_DEFINED
/**
 * Alternate Constructor which can call your own function to map the LOOL_IMU to arduino port,
 * no pins are used or initialized here
 */
LOOL_IMU::LOOL_IMU(void) : LOOL_Port(0)
{
  Device_Address = GYRO_DEFAULT_ADDRESS;
}

/**
 * Alternate Constructor which can call your own function to map the LOOL_IMU to arduino port,
 * no pins are used or initialized here, but PWM frequency set to 976 Hz
 * param[in]
 *   port - RJ25 port from PORT_1 to M2
 */
LOOL_IMU::LOOL_IMU(uint8_t port) : LOOL_Port(port)
{
  Device_Address = GYRO_DEFAULT_ADDRESS;
}

/**
 * Alternate Constructor which can call your own function to map the LOOL_IMU to arduino port
 * and change the i2c device address
 * no pins are used or initialized here, but PWM frequency set to 976 Hz
 * param[in]
 *   port - RJ25 port from PORT_1 to M2
 * param[in]
 *   address - the i2c address you want to set
 */
LOOL_IMU::LOOL_IMU(uint8_t port, uint8_t address) : LOOL_Port(port)
{
  Device_Address = address;
}
#else  // LOOL_PORT_DEFINED
/**
 * Alternate Constructor which can call your own function to map the _AD0 and _INT to arduino port,
 * no pins are used or initialized here
 * param[in]
 *   _AD0 - arduino gpio number
 * param[in]
 *   _INT - arduino gpio number
 */
LOOL_IMU::LOOL_IMU(uint8_t AD0, uint8_t INT)
{
  Device_Address = GYRO_DEFAULT_ADDRESS;
  _AD0 = AD0;
  _INT = INT;
}

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
LOOL_IMU::LOOL_IMU(uint8_t AD0, uint8_t INT, uint8_t address)
{
  Device_Address = address;
  _AD0 = AD0;
  _INT = INT;
}
#endif // LOOL_PORT_DEFINED

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
void LOOL_IMU::setpin(uint8_t AD0, uint8_t INT)
{
  _AD0 = AD0;
  _INT = INT;
#ifdef LOOL_PORT_DEFINED
  s1 = AD0;
  s2 = INT;
#endif // LOOL_PORT_DEFINED
}

/**
 * @par Function
 *   begin
 * @par Description
 *   Initialize the LOOL_IMU.
 * param[in]
 *   None
 * @par Output
 *   None
 * return
 *   None
 * @par Others
 *   You can check the MPU6050 datasheet for the registor address.
 */
void LOOL_IMU::begin(void)
{
	for(uint8_t i=0;i<3;i++)
	{
		angle[i] = 0;
		gyro[i] = 0;
		acc[i] = 0;
		gyroOffs[i] = 0;
		accOffs[i] = 0;
	}
  Wire.begin();
  delay(800);
  writeReg(0x6b, 0x00);//close the sleep mode
  writeReg(0x19, 0x00);//gyroscope sample rate  1000hz
  writeReg(0x1a, 0x01);//configurate the digital low pass filter
  writeReg(0x1b, 0x18);//set the gyro scale to +-2000 deg/s
  writeReg(0x1c, 0x10);//set the acc  scale to +-8g
  
  deviceCalibration(GYRO_CALIBRATION);// calibration the gyroscope
}

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
void LOOL_IMU::dataUpdate(void)
{
  int8_t return_value;

  /* read imu data */
	  return_value = readData(0x3b, i2cData, 14);
	  if(return_value != 0)
	  {
		return;
	  }

	  // assemble 16 bit sensor data    UNIT: acc is m/s2,  gyro is rad/s    
	  acc[X] = ( ((i2cData[0] << 8) | i2cData[1]) - accOffs[X])*ACC_1G/4096.0f;
	  acc[Y] = ( ((i2cData[2] << 8) | i2cData[3]) - accOffs[Y])*ACC_1G/4096.0f;
	  acc[Z] = ( ((i2cData[4] << 8) | i2cData[5]) - accOffs[Z])*ACC_1G/4096.0f;  
	  gyro[X] = ( ( (i2cData[8] << 8) | i2cData[9] ) - gyroOffs[X]) * 0.0010652635f;
	  gyro[Y] = ( ( (i2cData[10] << 8) | i2cData[11] ) - gyroOffs[Y]) * 0.0010652635f;
	  gyro[Z] = ( ( (i2cData[12] << 8) | i2cData[13] ) - gyroOffs[Z]) * 0.0010652635f;  
	  
	  IMU_Update(); //update IMU data, we can get angle of 3 axis  
}

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
float LOOL_IMU::getACC(uint8_t axis)
{
	return acc[axis];
}

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
float LOOL_IMU::getGYRO(uint8_t axis)
{
	return gyro[axis];
}

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
float LOOL_IMU::getAngle(uint8_t axis)
{
  return angle[axis];
}

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
void LOOL_IMU::IMU_Update(void)
{
  float norm;	
	float gx = gyro[X],gy = gyro[Y],gz = gyro[Z];
	float ax = acc[X],ay = acc[Y],az = acc[Z];
	static uint32_t cycleT=0,previousT=micros();
	
	float q0q0 = q0 * q0;
  float q0q1 = q0 * q1;
  float q0q2 = q0 * q2;
  float q1q1 = q1 * q1;
  float q1q3 = q1 * q3;
  float q2q2 = q2	* q2;
  float q2q3 = q2	*	q3;
  float q3q3 = q3	*	q3;	
	float vx, vy, vz;
  float ex, ey, ez;
	
	float	q0_yawq0_yaw = q0_yaw * q0_yaw;
	float	q1_yawq1_yaw = q1_yaw * q1_yaw;
	float	q2_yawq2_yaw = q2_yaw * q2_yaw;
	float	q3_yawq3_yaw = q3_yaw * q3_yaw;
	float	q1_yawq2_yaw = q1_yaw * q2_yaw;
	float	q0_yawq3_yaw = q0_yaw * q3_yaw;
	
	cycleT = micros()-previousT;
	previousT = micros();
	
	//differential equation of yaw axis quaternion
  q0_yaw = q0_yaw + (-q1_yaw * gx - q2_yaw * gy - q3_yaw * gz) * (cycleT/2000000.0f);
  q1_yaw = q1_yaw + (q0_yaw * gx + q2_yaw * gz - q3_yaw * gy) * (cycleT/2000000.0f);
  q2_yaw = q2_yaw + (q0_yaw * gy - q1_yaw * gz + q3_yaw * gx) * (cycleT/2000000.0f);
  q3_yaw = q3_yaw + (q0_yaw * gz + q1_yaw * gy - q2_yaw * gx) * (cycleT/2000000.0f);
	
	//standardize yaw axis quaternion
  norm = sqrt(q0_yawq0_yaw + q1_yawq1_yaw + q2_yawq2_yaw + q3_yawq3_yaw);
  q0_yaw = q0_yaw / norm;
  q1_yaw = q1_yaw / norm;
  q2_yaw = q2_yaw / norm;
  q3_yaw = q3_yaw / norm;
	
  
	if(ax * ay * az	== 0)
	return ;
	
	//standardize acceleration
  norm = sqrt(ax * ax + ay * ay + az * az); 
  ax = ax / norm;
  ay = ay / norm;
  az = az / norm;
	

  vx = 2 * (q1q3 - q0q2);											
  vy = 2 * (q0q1 + q2q3);
  vz = q0q0 - q1q1 - q2q2 + q3q3 ;
	
  //get the error
  ex = (ay * vz - az * vy) ;      
  ey = (az * vx - ax * vz) ;
  ez = (ax * vy - ay * vx) ;

	//use PI method 
  ex_int = ex_int + ex * IMU_KI;			
  ey_int = ey_int + ey * IMU_KI;
  ez_int = ez_int + ez * IMU_KI;

  //correct gyro
  gx = gx + IMU_KP * ex + ex_int;					
  gy = gy + IMU_KP * ey + ey_int;
  gz = gz + IMU_KP * ez + ez_int;			
			
	//differential equation of quaternion
  q0 = q0 + (-q1 * gx - q2	*	gy - q3	*	gz)	*	(cycleT/2000000.0f);
  q1 = q1 + (q0	*	gx + q2	*	gz - q3	*	gy)	*	(cycleT/2000000.0f);
  q2 = q2 + (q0	*	gy - q1	*	gz + q3	*	gx)	*	(cycleT/2000000.0f);
  q3 = q3 + (q0	*	gz + q1	*	gy - q2	*	gx)	*	(cycleT/2000000.0f);

  //standardize quaternion of pitch axis and roll axis
  norm = sqrt(q0q0 + q1q1 + q2q2 + q3q3);
  q0 = q0 / norm;
  q1 = q1 / norm;
  q2 = q2 / norm;
  q3 = q3 / norm;
	
	//get euler angle
	angle[X] = atan2(2 * q2q3 + 2 * q0q1, -2 * q1q1 - 2 * q2q2 + 1) * 57.3f;
	angle[Y] = asin(-2 * q1q3 + 2 * q0q2) * 57.3f;
	angle[Z] = atan2(2 * q1_yawq2_yaw + 2 * q0_yawq3_yaw, -2 * q2_yawq2_yaw - 2 * q3_yawq3_yaw + 1)	* 57.3f;

}
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
void LOOL_IMU::deviceCalibration(uint8_t deviceCali)
{
  int8_t return_value;
  uint16_t i, num = 500;
  long xSum	= 0, ySum = 0, zSum = 0;
  if(deviceCali|ACC_CALIBRATION)
  {
	  xSum	= 0, ySum = 0, zSum = 0;
	  for(i = 0; i < num; i++)
	  {
		  return_value = readData(0x43, i2cData, 6);
		  xSum += ( (i2cData[0] << 8) | i2cData[1] );
		  ySum += ( (i2cData[2] << 8) | i2cData[3] );
		  zSum += ( (i2cData[4] << 8) | i2cData[5] );  
		  
	  }
	  accOffs[X] = xSum / num;
	  accOffs[Y] = ySum / num;
	  accOffs[Z] = zSum / num;
  }
  if(deviceCali|GYRO_CALIBRATION)
  {
	  xSum	= 0, ySum = 0, zSum = 0;
	  for(i = 0; i < num; i++)
	  {
		  return_value = readData(0x43, i2cData, 6);
		  xSum += ( (i2cData[8] << 8) | i2cData[9] );
		  ySum += ( (i2cData[10] << 8) | i2cData[11] );
		  zSum += ( (i2cData[12] << 8) | i2cData[13] );
	  }
	  gyroOffs[X] = xSum / num;
	  gyroOffs[Y] = ySum / num;
	  gyroOffs[Z] = zSum / num;
  }
}

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
int8_t LOOL_IMU::writeReg(int16_t reg, uint8_t data)
{
  int8_t return_value = 0;
  return_value = writeData(reg, &data, 1);
  return(return_value);
}

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
int8_t LOOL_IMU::readData(uint8_t start, uint8_t *buffer, uint8_t size)
{
  int16_t i = 0;
  int8_t return_value = 0;
  Wire.beginTransmission((uint8_t)0x68);
  return_value = Wire.write(start);
  if(return_value != 1)
  {
    return(I2C_ERROR);
  }
  return_value = Wire.endTransmission(false);
  if(return_value != 0)
  {
    return(return_value);
  }
  delayMicroseconds(1);
  /* Third parameter is true: relase I2C-bus after data is read. */
  Wire.requestFrom((uint8_t)0x68, size, (uint8_t)true);
  while(Wire.available() && i < size)
  {
    buffer[i++] = Wire.read();
  }
  delayMicroseconds(1);
  if(i != size)
  {
    return(I2C_ERROR);
  }
  return(0); //return: no error 
}

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
int8_t LOOL_IMU::writeData(uint8_t start, const uint8_t *pData, uint8_t size)
{
  int8_t return_value = 0;
  Wire.beginTransmission(0x68);
  return_value = Wire.write(start); 
  if(return_value != 1)
  {
    return(I2C_ERROR);
  }
  Wire.write(pData, size);  
  return_value = Wire.endTransmission(true); 
  return(return_value); //return: no error                     
}
