

/*
 * Include Files
 *
 */
#if defined(MATLAB_MEX_FILE)
#include "tmwtypes.h"
#include "simstruc_types.h"
#else
#include "rtwtypes.h"
#endif

/* %%%-SFUNWIZ_wrapper_includes_Changes_BEGIN --- EDIT HERE TO _END */
#ifndef MATLAB_MEX_FILE

// This should be cleaned by using a general wrapper file

#include <Arduino.h>
#include "../../cores/Wire.h"
#include "../../cores/Wire.cpp"
#include "../../cores/twi.h"
#include "../../cores/twi.c"
#include "../../cores/BMP085.h"
#include "../../cores/BMP085.cpp"
#include "../../cores/HMC5883L.h"
#include "../../cores/HMC5883L.cpp"
#include "../../cores/MPU6050.h"
#include "../../cores/MPU6050.cpp"

BMP085 barometer;
HMC5883L magnetometer;
MPU6050 imu;

# endif
/* %%%-SFUNWIZ_wrapper_includes_Changes_END --- EDIT HERE TO _BEGIN */
#define u_width 
#define y_width 1
/*
 * Create external references here.  
 *
 */
/* %%%-SFUNWIZ_wrapper_externs_Changes_BEGIN --- EDIT HERE TO _END */
/* extern double func(double a); */
/* %%%-SFUNWIZ_wrapper_externs_Changes_END --- EDIT HERE TO _BEGIN */

/*
 * Output functions
 *
 */
extern "C" void GY_88_Outputs_wrapper(real_T *temperature,
			real_T *pressure,
			real_T *altitude,
			real_T *magnitude,
			real_T *acceleration,
			real_T *angular_velocity,
			const real_T *xD,
			const real_T  *S_T, const int_T  p_width0)
{
/* %%%-SFUNWIZ_wrapper_Outputs_Changes_BEGIN --- EDIT HERE TO _END */
if (xD[0]==1) {    
  # ifndef MATLAB_MEX_FILE
    temperature[0] = barometer.bmp085GetTemperature(barometer.bmp085ReadUT());
    pressure[0] = barometer.bmp085GetPressure(barometer.bmp085ReadUP());
    altitude[0] = barometer.calcAltitude(pressure[0]);
    magnitude[0] = magnetometer.readX();
    magnitude[1] = magnetometer.readZ();
    magnitude[2] = magnetometer.readY();
    int error;
    accel_t_gyro_union accel_t_gyro;
    error = imu.MPU6050_read (MPU6050_ACCEL_XOUT_H, (unsigned char *) &accel_t_gyro, sizeof(accel_t_gyro));
    unsigned char swap;
    #define SWAP(x,y) swap = x; x = y; y = swap
    SWAP (accel_t_gyro.reg.x_accel_h, accel_t_gyro.reg.x_accel_l);
    SWAP (accel_t_gyro.reg.y_accel_h, accel_t_gyro.reg.y_accel_l);
    SWAP (accel_t_gyro.reg.z_accel_h, accel_t_gyro.reg.z_accel_l);
    SWAP (accel_t_gyro.reg.t_h, accel_t_gyro.reg.t_l);
    SWAP (accel_t_gyro.reg.x_gyro_h, accel_t_gyro.reg.x_gyro_l);
    SWAP (accel_t_gyro.reg.y_gyro_h, accel_t_gyro.reg.y_gyro_l);
    SWAP (accel_t_gyro.reg.z_gyro_h, accel_t_gyro.reg.z_gyro_l);    
    acceleration[0] = accel_t_gyro.value.x_accel/accelerometer_sensitivity;
    acceleration[1] = accel_t_gyro.value.y_accel/accelerometer_sensitivity;
    acceleration[2] = accel_t_gyro.value.z_accel/accelerometer_sensitivity;
    angular_velocity[0] = accel_t_gyro.value.x_gyro/gyroscope_sensitivity;
    angular_velocity[1] = accel_t_gyro.value.y_gyro/gyroscope_sensitivity;
    angular_velocity[2] = accel_t_gyro.value.z_gyro/gyroscope_sensitivity;
  # endif
}
/* %%%-SFUNWIZ_wrapper_Outputs_Changes_END --- EDIT HERE TO _BEGIN */
}

/*
  * Updates function
  *
  */
extern "C" void GY_88_Update_wrapper(const real_T *temperature,
			const real_T *pressure,
			const real_T *altitude,
			const real_T *magnitude,
			const real_T *acceleration,
			const real_T *angular_velocity,
			real_T *xD,
			const real_T  *S_T,  const int_T  p_width0)
{
  /* %%%-SFUNWIZ_wrapper_Update_Changes_BEGIN --- EDIT HERE TO _END */
if (xD[0]!=1) {    
  # ifndef MATLAB_MEX_FILE
      Wire.begin();
      barometer.bmp085Calibration();                      // this do the calibration of the barometer
      barometer.bmp085GetReference();                     // this set reference values to actual values
      magnetometer.setGain(7);
      magnetometer.setMode(0);
      magnetometer.biasDataOutputs();     		    // this biases the output reading for the reading to start from zero
      magnetometer.averagedSamples(1);  	 		// default value need not be set
      magnetometer.setDataOutputRate(8);	 		// default value need not be set
      magnetometer.setMeasurementMode(0); 		    // default value need not be set  
      int error;
      unsigned char c;
      error = imu.MPU6050_read (MPU6050_PWR_MGMT_1, &c, 1);    // ?????
      imu.MPU6050_write_reg (MPU6050_PWR_MGMT_1, 0);
  # endif   
  xD[0]=1;
}
/* %%%-SFUNWIZ_wrapper_Update_Changes_END --- EDIT HERE TO _BEGIN */
}
