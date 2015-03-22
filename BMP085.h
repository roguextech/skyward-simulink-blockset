#ifndef BMP085_h
#define BMP085_h


#include "Arduino.h"
#include "Wire.h"

/* Register defines for the BMP085 Pressure Sensor */

#define BMP085_CAL_AC1           0xAA  // R   Calibration data (16 bits)
#define BMP085_CAL_AC2           0xAC  // R   Calibration data (16 bits)
#define BMP085_CAL_AC3           0xAE  // R   Calibration data (16 bits)    
#define BMP085_CAL_AC4           0xB0  // R   Calibration data (16 bits)
#define BMP085_CAL_AC5           0xB2  // R   Calibration data (16 bits)
#define BMP085_CAL_AC6           0xB4  // R   Calibration data (16 bits)
#define BMP085_CAL_B1            0xB6  // R   Calibration data (16 bits)
#define BMP085_CAL_B2            0xB8  // R   Calibration data (16 bits)
#define BMP085_CAL_MB            0xBA  // R   Calibration data (16 bits)
#define BMP085_CAL_MC            0xBC  // R   Calibration data (16 bits)
#define BMP085_CAL_MD            0xBE  // R   Calibration data (16 bits)
#define BMP085_ADDRESS           0x77  //     I2C address of BMP085
#define BMP085_CONTROL           0xF4  //     Control 
#define BMP085_READTEMPCMD       0x2E  //     Mode : Temperature
#define BMP085_READPRESSURECMD   0x34  //     Mode : Pressure
#define BMP085_RA_MSB       	 0xF6  //     MSB 
#define BMP085_RA_LSB            0xF7  //     LSB 
#define BMP085_RA_XLSB           0xF8  //     XLSB
#define SAMPLES 		 512

 

class BMP085
{
  public:
    //BMP085();
	void bmp085Calibration();
	float bmp085GetReference();
	float bmp085GetTemperature(unsigned int ut);
	long bmp085GetPressure(unsigned long up);
	float calcAltitude(float pressure);
	unsigned int bmp085ReadUT();
	unsigned long bmp085ReadUP();
    float Pref;                            // Reference pressure
	float Tref;                            // Reference temperature 
  private:
    char bmp085Read(unsigned char address);
	int bmp085ReadInt(unsigned char address);		
	/* Calibration datas for the BMP085 Pressure Sensor */
	int ac1, ac2, ac3, b1, b2, mb, mc, md; // These register store calibration datas
	unsigned int ac4, ac5, ac6;
	long b5;                               // It's ugly to have this here. Should walk trought another solution
	           // Oversampling Setting -> 3 = Highest Resolution (I think)
};

#endif