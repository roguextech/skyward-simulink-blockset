#include"Arduino.h"
#include "MPU6050.h"

// DATA READING

int MPU6050::MPU6050_read(int start, unsigned char *buffer, int size)
{
  int i, n, error;
 
  Wire.beginTransmission(MPU6050_I2C_ADDRESS);
  n = Wire.write(start);
  if (n != 1)
    return (-10);
 
  n = Wire.endTransmission();    // hold the I2C-bus
  if (n != 0)
    return (n);
 
  // Third parameter is true: relase I2C-bus after data is read.
  Wire.requestFrom(MPU6050_I2C_ADDRESS, size);
  i = 0;
  while(Wire.available() && i<size)
  {
    buffer[i++]=Wire.read();
  }
  if ( i != size)
    return (-11);
 
  return (0);  // return : no error
}

int MPU6050::MPU6050_write(int start, const unsigned char *pData, int size)
{
  int n, error;
 
  Wire.beginTransmission(MPU6050_I2C_ADDRESS);
  n = Wire.write(start);        // write the start address
  if (n != 1)
    return (-20);
 
  n = Wire.write(pData, size);  // write data bytes
  if (n != size)
    return (-21);
 
  error = Wire.endTransmission(); // release the I2C-bus
  if (error != 0)
    return (error);
 
  return (0);         // return : no error
}

int MPU6050::MPU6050_write_reg(int reg, unsigned char data)
{
  int error;
 
  error = MPU6050_write(reg, &data, 1);
 
  return (error);
}
