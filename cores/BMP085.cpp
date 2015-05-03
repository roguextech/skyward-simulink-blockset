#include"Arduino.h"
#include "BMP085.h"

const unsigned char OSS = 3;

char BMP085::bmp085Read(unsigned char address)
{
  unsigned char data;

  Wire.beginTransmission(BMP085_ADDRESS);
  Wire.write(address);
  Wire.endTransmission();
  Wire.requestFrom(BMP085_ADDRESS, 1);   
  while(!Wire.available())               
    ;

  return Wire.read();              
}

int BMP085::bmp085ReadInt(unsigned char address)
{
  unsigned char msb, lsb;      

  Wire.beginTransmission(BMP085_ADDRESS);
  Wire.write(address);
  Wire.endTransmission();

  Wire.requestFrom(BMP085_ADDRESS, 2);    
  while(Wire.available()<2)
    ;
  msb = Wire.read();
  lsb = Wire.read();

  return (int) msb<<8 | lsb;    
}

void BMP085::bmp085Calibration()
{
  ac1 =  bmp085ReadInt(BMP085_CAL_AC1 );  
  ac2 =  bmp085ReadInt(BMP085_CAL_AC2);
  ac3 =  bmp085ReadInt(BMP085_CAL_AC3);
  ac4 =   bmp085ReadInt(BMP085_CAL_AC4);
  ac5 =   bmp085ReadInt(BMP085_CAL_AC5);
  ac6 =   bmp085ReadInt(BMP085_CAL_AC6);
  b1 =  bmp085ReadInt(BMP085_CAL_B1);
  b2 =  bmp085ReadInt(BMP085_CAL_B2);
  mb =  bmp085ReadInt(BMP085_CAL_MB);
  mc =  bmp085ReadInt(BMP085_CAL_MC);
  
  md =  bmp085ReadInt(BMP085_CAL_MD);
}

unsigned int BMP085::bmp085ReadUT()
{
  unsigned int ut;
  Wire.beginTransmission(BMP085_ADDRESS);
  Wire.write(BMP085_CONTROL);       
  Wire.write(BMP085_READTEMPCMD);       // This request a temperature reading
  Wire.endTransmission();
  // Wait at least 4.5ms
  delay(5);
  // Read two bytes from registers 0xF6 and 0xF7
  ut = bmp085ReadInt(BMP085_RA_MSB);
  return ut;
}

unsigned long BMP085::bmp085ReadUP()
{
  unsigned char msb, lsb, xlsb;
  unsigned long up = 0;

  // Write 0x34+(OSS<<6) into register 0xF4
  // Request a pressure reading w/ oversampling setting
  Wire.beginTransmission(BMP085_ADDRESS);
  Wire.write(BMP085_CONTROL);
  Wire.write(BMP085_READPRESSURECMD + (OSS<<6));
  Wire.endTransmission();
  // Wait for conversion, delay time dependent on OSS
  delay(2 + (3<<OSS));
  // Read register 0xF6 (MSB), 0xF7 (LSB), and 0xF8 (XLSB)
  msb = bmp085Read(BMP085_RA_MSB);
  lsb = bmp085Read(BMP085_RA_LSB);
  xlsb = bmp085Read(BMP085_RA_XLSB);

  up = (((unsigned long) msb << 16) | ((unsigned long) lsb << 8) | (unsigned long) xlsb) >> (8-OSS);

  return up;
}

float BMP085::bmp085GetTemperature(unsigned int ut)
{
  long x1, x2;
  x1 = (((long)ut - (long)ac6)*(long)ac5) >> 15;
  x2 = ((long)mc << 11)/(x1 + md);
  b5 = x1 + x2;
  float temp = ((b5 + 8)>>4);
  temp = temp /10;
  return temp;
}

long BMP085::bmp085GetPressure(unsigned long up)
{
  long x1, x2, x3, b3, b6, p;
  unsigned long b4, b7;

  b6 = b5 - 4000;
  // Calculate B3
  x1 = (b2 * (b6 * b6)>>12)>>11;
  x2 = (ac2 * b6)>>11;
  x3 = x1 + x2;
  b3 = (((((long)ac1)*4 + x3)<<OSS) + 2)>>2;

  // Calculate B4
  x1 = (ac3 * b6)>>13;
  x2 = (b1 * ((b6 * b6)>>12))>>16;
  x3 = ((x1 + x2) + 2)>>2;
  b4 = (ac4 * (unsigned long)(x3 + 32768))>>15;

  b7 = ((unsigned long)(up - b3) * (50000>>OSS));
  if (b7 < 0x80000000)
    p = (b7<<1)/b4;
  else
    p = (b7/b4)<<1;

  x1 = (p>>8) * (p>>8);
  x1 = (x1 * 3038)>>16;
  x2 = (-7357 * p)>>16;
  p += (x1 + x2 + 3791)>>4;

  long temp = p;
  return temp;
}

float BMP085::calcAltitude(float pressure)
{
  float a = 0.0065;         //temperature lapse rate
  float A = pressure/Pref;  
  float B = 0.190266; //(R*a)/(g*m)
  float C = pow(A,B);
  C = 1 - C;
  float altitude = C*(Tref/a);
  return altitude;
}

float BMP085::bmp085GetReference()
{
  float press_avg=0,temp_avg = 0;
  for(int i = 0; i < SAMPLES; i++)
    {
      press_avg += bmp085GetPressure(bmp085ReadUP());
      temp_avg  += bmp085GetTemperature(bmp085ReadUT());
    }
  press_avg /= SAMPLES;
  temp_avg /= SAMPLES;
  temp_avg = temp_avg+273.15;
  Pref = press_avg;
  Tref = temp_avg;
}