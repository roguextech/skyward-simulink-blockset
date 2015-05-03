#include"Arduino.h"
#include "HMC5883L.h"

word Gain = 1090;
float biasX;						
float biasY;						
float biasZ;												
boolean isXred = false; 									
boolean isYred = true;
boolean isZred = false;	
	
// DATA READING

float HMC5883L::readX()
{
  // Bias is set by the user during the calibration Phase
  float result =0;
  pointTo(DXRMSB);
  Wire.requestFrom(HMC5883L_ADDRESS,6);
  result = Wire.read()<<8|Wire.read();
  result = result/Gain;
  result = result*100+biasX ;//convert to 10 milli_gauss
  isXred = true;
  return result ;
}

float HMC5883L::readY()
{
  // Bias is set by the user during the calibration Phase
  float result =0;
  if (isZred)
  {
    result = Wire.read()<<8|Wire.read();
    result = result/Gain;
    result = result*100+biasY;//convert to 10 milli_gauss
  }
  else{
    Wire.endTransmission();
  }
 //  reset isZred
  isZred = false;
  return result;
}

float HMC5883L::readZ()
{
  // Bias is set by the user during the calibration Phase
  float result =0;
  if (isXred)
  {
    result = Wire.read()<<8|Wire.read();
    result = result/Gain;
    result = result*100+biasZ;//convert to 10 milli_gauss
    isZred = true;
 }
  else{
    Wire.endTransmission();
    isZred = false;
  }
   //reset isXred
  isXred = false;  
  return result; 
}

void HMC5883L::biasDataOutputs()
{
  // to bias the sensor we need a somewhat reliable data so we take the average over 8 samples
  averagedSamples(8);
  delay(10);
  readX();
  biasX = -readX();
  biasZ = -readZ();
  biasY = -readY(); 
}

// FUNCTIONNS RELATED TO CONFIGURATION REGISTER A

// This funcion set how many samples to average before provideing it to output register
void HMC5883L::averagedSamples (byte numberOfSamples)
{  
  // read data first to change related bits
  byte regContent = readByteFrom(CONIFGA);
  // reserved bit should be cleared 
  bitClear(regContent,7);
  // This admits 1,2,4 or 8 
  switch (numberOfSamples){
    case 2:
      bitClear(regContent,6);bitSet(regContent,5);
      break;    
    case 4:
      bitSet(regContent,6);bitClear(regContent,5);
      break;    
    case 8:
      bitSet(regContent,6);bitSet(regContent,5);
      break;    
    default:
      // by default is set to 1
      bitWrite(regContent,6,0);bitWrite(regContent,5,0);
  }
  writeByteTo(CONIFGA,regContent);
}

// This function give data outputs rate
void HMC5883L::setDataOutputRate(byte rate)
{
  // read data first to change related bits
  byte regContent = readByteFrom(CONIFGA);
  // This admits .75 1.5 3 7.5 15(defaullt) 30 75 Hz
  // reserved bit should be cleared 
  bitClear(regContent,7);
  switch (rate){
    case 1:
      //.75 Hz
      bitWrite(regContent,4,0);bitWrite(regContent,3,0);bitWrite(regContent,2,0);
      break;    
    case 2:
      //1.5 Hz
      bitWrite(regContent,4,0);bitWrite(regContent,3,0);bitWrite(regContent,2,1);
      break;    
    case 3:
      //3 Hz
      bitWrite(regContent,4,0);bitWrite(regContent,3,1);bitWrite(regContent,2,0);
      break;    
    case 4:
      //7.5 Hz
      bitWrite(regContent,4,0);bitWrite(regContent,3,1);bitWrite(regContent,2,1); 
      break;
    case 5:
      //30 Hz
      bitWrite(regContent,4,1);bitWrite(regContent,3,0);bitWrite(regContent,2,1); 
      break;       
    case 6:
      //75 Hz
      bitWrite(regContent,4,1);bitWrite(regContent,3,1);bitWrite(regContent,2,0);
      break;       
    default:
      // by default is set to 15
      bitWrite(regContent,4,1);bitWrite(regContent,3,0);bitWrite(regContent,2,0);
  }
  writeByteTo(CONIFGA,regContent); 
}

// Measurement Mode Normal, Positive Bias or Negative Bias
void HMC5883L::setMeasurementMode(byte mode)
{
  // read data first to change related bits
  byte regContent = readByteFrom(CONIFGA);
  // reserved bit should be cleared 
  bitClear(regContent,7);
  // This admits 0 1 2
  switch (mode){
    case 1:
      //Positive Bias
      bitWrite(regContent,1,0);bitWrite(regContent,0,1);
      break;    
    case 2:
      //Negative Bias
      bitWrite(regContent,1,1);bitWrite(regContent,0,0);
      break;       
    default:
      // by default is set to 0 Normal Measurment Mode
      bitWrite(regContent,1,0);bitWrite(regContent,0,0);
  }
  writeByteTo(CONIFGA,regContent);
}

// FUNCTIONNS RELATED TO CONFIGURATION REGISTER B

// Global Variable Gain is defined to be used lated in Data output Registers but it needs to be set by the user or it is 1090 by default
void HMC5883L::setGain(byte gain)
{
  byte regContent = 0x20; 
   
  switch (gain){
    case 0:
      //1370 -- +- .88 Ga
      Gain = 1370;
      regContent = 0x00;
      break;    
    case 2:
      //820 -- +- 1.9 Ga
      Gain = 820;
      regContent = 0x40;
      break;   
    case 3:
      //660 -- +- 2.5 Ga
      Gain = 660;
      regContent = 0x60;
      break;  
    case 4:
      //440 -- +- 4.0 Ga
      Gain = 400;
      regContent = 0x80;
      break;    
    case 5:
      //390 -- +- 4.7 Ga
      Gain = 390;
      regContent = 0xA0;
      break;  
    case 6:
      //330  -- +- 5.6 Ga
      Gain = 330;
      regContent = 0xB0;
      break;  
    case 7:
      Gain = 230;
      //230  -- +- 8.1 Ga
      regContent = 0xE0;
      break;        
    default:
      // by default is set to 1090
      break; 
  }     
  writeByteTo(CONIFGB,regContent);
}

// SET MODE REGISTER

void HMC5883L::setMode(byte mode){
  byte regContent = 0x00; //(default value to set continous mode)
  switch (mode){
    case 1:
    regContent = 0x01;
    break;
    case 2:
    regContent = 0x02;
    break;
    case 3:
    regContent = 0x03;
    break;
    default:
    break;
  }
  writeByteTo(MODE,regContent);
}

boolean HMC5883L::RDY()
{
  // returns the value in the ready bit location of the status register
  // This bit is high when all data are availabe to output register
  byte regContent = readByteFrom(STATUS);
  return bitRead(regContent,0);  
}

// This function check if a register is locked
boolean HMC5883L::checkLockStatus()
{
  byte regContent = readByteFrom(STATUS);
  return bitRead(regContent,1);  
}

// This function is used when something goes wrong and the LOCK bit needs to be programatically reset, otherwise the data ouput register will be automatically unLOCKed after a correct reading of the next data stream
void HMC5883L::unLock()
{
	writeByteTo(MODE,0x00);
}

// This function points to a register map location
void HMC5883L::pointTo(byte regPointer)
{
  Wire.beginTransmission(HMC5883L_ADDRESS); 
  Wire.write(regPointer);
  Wire.endTransmission();
}

// reads a byte
byte HMC5883L::readByteFrom (byte regList)
{
  byte result = 0;
  pointTo(regList);
  Wire.requestFrom(HMC5883L_ADDRESS,1);
  result = Wire.read() ; 
  return result;
}

// writes a byte
void HMC5883L::writeByteTo (byte regList,byte byteData)
{
  Wire.beginTransmission(HMC5883L_ADDRESS); 
  Wire.write(regList);
  Wire.write(byteData);
  Wire.endTransmission();
} 

