#ifndef MPU6050_h
#define MPU6050_h


#include "Arduino.h"
#include "Wire.h"

/* Register defines for the MPU6050 IMU */

#define MPU6050_I2C_ADDRESS        0x68			
#define MPU6050_PWR_MGMT_1         0x6B   		// R/W
#define MPU6050_ACCEL_XOUT_H       0x3B   		// R  
#define accelerometer_sensitivity  16.384
#define gyroscope_sensitivity      131

typedef union accel_t_gyro_union
{
  struct
  {
    unsigned char x_accel_h;
    unsigned char x_accel_l;
    unsigned char y_accel_h;
    unsigned char y_accel_l;
    unsigned char z_accel_h;
    unsigned char z_accel_l;
    unsigned char t_h;
    unsigned char t_l;
    unsigned char x_gyro_h;
    unsigned char x_gyro_l;
    unsigned char y_gyro_h;
    unsigned char y_gyro_l;
    unsigned char z_gyro_h;
    unsigned char z_gyro_l;
  } reg;
  struct
  {
    int x_accel;
    int y_accel;
    int z_accel;
    int temperature;
    int x_gyro;
    int y_gyro;
    int z_gyro;
  } value;
};

class MPU6050
{
  public:
    int MPU6050_read(int start, unsigned char *buffer, int size);
	int MPU6050_write_reg(int reg, unsigned char data);
  private:
    int MPU6050_write(int start, const unsigned char *pData, int size);
};

#endif