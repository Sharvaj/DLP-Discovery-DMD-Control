#pragma once
# include <iostream>
# include <fstream>
# include <string>
# include <algorithm>
# include <Windows.h>
# include "8055.D4100_usb.h"
# include "CyAPI.h"
# include "RegisterDefines.h"
// defined in testFunctions.cpp :
void myCheckRowModes();

// defined in ControllerFunctions.cpp :
int myInitializeDMD(short devNum);
int myReprogramFPGA(short int devNum);
void myLoadZebra(bool zebraState);
short myPowerDownPrep(short devNum);
void myLoadPattern(std::string patFilename, const int imageByteSize, short devNum);

namespace myTemp {
	void SaveZebra(bool zebraState);
	void LoadBMP(std::string patFilename, const int imageByteSize, short devNum);
}