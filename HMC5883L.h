#ifndef HMC5883L_h
#define HMC5883L_h


#include "Arduino.h"
#include "Wire.h"

/* Register defines for the HMC5883L Magnetometer */

#define HMC5883L_ADDRESS		0x1E	//	R	Device Address
#define CONIFGA  				0x00	// 		Configuration Register A  
#define CONIFGB  				0x01	// 		Configuration Register B
#define MODE  					0x02	// 		Mode Register
#define DXRMSB  				0x03	// 	R 	X Output
#define DXRLSB  				0x04
#define DYRMSB  				0x07	//	R	Y Output
#define DYRLSB  				0x08
#define DZRMSB  				0x05	//	R	Z Output
#define DZRLSB  				0x06
#define STATUS  				0x09	//  R	Status Register
#define IRA  					0x0A	// 	R	Identification Register A
#define IRB  					0x0B	//  R 	Identification Register B
#define IRC  					0x0C	// 	R 	Identification Register C 

class HMC5883L
{
  public:
    void setMode(byte mode);
	void setGain(byte gain);
	void averagedSamples(byte numberOfSamples);
	void setDataOutputRate(byte rate);
	void setMeasurementMode(byte mode);  
    float readX();
	float readY();
	float readZ();
	void biasDataOutputs();
	boolean checkLockStatus();	
  private:
    boolean RDY();
	void unLock();
	void pointTo(byte regPointer);
	byte readByteFrom (byte regList);
	void writeByteTo (byte regList,byte byteData);
};

#endif