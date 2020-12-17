#pragma once
# include <iostream>
# include <fstream>
# include <string>
# include <algorithm>
# include <Windows.h>
# include <stdlib.h>
# include "8055.D4100_usb.h"
# include "CyAPI.h"
# include "RegisterDefines.h"
// defined in testFunctions.cpp :
void myCheckRowModes();

// defined in ControllerFunctions.cpp :
int myInitializeDMD(short devNum);
int myReprogramFPGA(short int devNum);

void myActiveBoxPositioning(int bh, int bw, int topBuffer, int leftBuffer, short devNum);
void myActiveBoxEmbedPattern(std::string patFilename, int bh, int bw, int topBuffer, int leftBuffer, short devNum);
void myActiveBoxEmbedPointScan(int bh, int bw, int topBuffer, int leftBuffer, int loch, int locw, int binSize, short devNum);
int myLoadLive(unsigned char* myPattern, const int DMDByteSize, short devNum);

void myLoadZebra(bool zebraState);
short myPowerDownPrep(short devNum);
void myLoadPattern(std::string patFilename, const int imageByteSize, short devNum);

namespace myTemp {
	void SaveZebra(bool zebraState);
	void LoadBMP(std::string patFilename, const int imageByteSize, short devNum);
}