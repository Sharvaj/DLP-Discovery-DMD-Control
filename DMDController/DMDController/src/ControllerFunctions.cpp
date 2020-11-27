
# include "MyHeaders.h"


int myInitializeDMD(short devNum) {
    
    using namespace USB;

    short w;
    long y;
    short int z;
    y = GetDLLRev();
    z = GetUsbSpeed(devNum);
    w = GetDMDTYPE(devNum);

    
    std::cout << "DLL version info: " << y << std::endl;
    std::cout << "USB speed: " << z << std::endl;
    std::cout << "DMD type: " << w << std::endl;


    int fl0 = myReprogramFPGA(devNum);
    short fl1 = SetWDT(0, devNum); // Disable WDT
    short fl2 = SetTPGEnable(0, devNum); // Disable TestPatternGenerator
    short fl3 = ClearFifos(devNum); // Initialize the DMD fifo.

    int myOutput = fl0 && fl1 && fl2 && fl3;
    return myOutput;
}

int myReprogramFPGA(short int devNum) {

    std::fstream FPGAFile;
    FPGAFile.open("D4100_GUI_FPGA.bin", std::ios::in|std::ios::binary);
    long writeSize = 1569584;

    unsigned char* writeBuffer = new unsigned char[writeSize];

    if (FPGAFile) {
        FPGAFile.read(reinterpret_cast<char*>(writeBuffer), writeSize);
        FPGAFile.close();
    }
    else {
        std::cout << "Error opening D4100_GUI_FPGA.bin !" << std::endl;
        exit(1);
    }
    
    int result = USB::program_FPGA(writeBuffer, writeSize, devNum);

    delete[] writeBuffer;
    return result;
}

void myLoadZebra(bool zebraState) {

    using namespace USB;

    SetBlkMd(0, 0);         //Set BlkMode to No Op
    SetRowMd(3, 0);       //Set Row Mode to Set Address mode
    SetRowAddr(0, 0);                      //Set the Row address to the top of the DMD

    const int DMDBytesPerRow = 240;
    const int DMDRowsPerBlock = 72;
    const int BlocksPerLoad = 2;

    unsigned char* zebra = new unsigned char[1920 * 1080 / 8];

    if (zebraState) {

        for (int i = 0; i < 1920 * 1080 / 8; i++)
        {
            if (i % (240 * 72 * 2) < 240 * 72)
                zebra[i] = 0x00;
            else
                zebra[i] = 0xff;
        }
    }
    else {
        for (int i = 0; i < 1920 * 1080 / 8; i++)
        {
            if (i % (240 * 72 * 2) < 240 * 72)
                zebra[i] = 0x00;
            else
                zebra[i] = 0xff;
        }
    }

    LoadData(&zebra[0], DMDBytesPerRow, 0, 0);  //Load the first row of data  (e2e)
    // cin.get();
    SetRowMd(1, 0);              //Set the DMD pointer to Increment mode  (e2e)
    LoadData(&zebra[DMDBytesPerRow], DMDBytesPerRow * (DMDRowsPerBlock - 1), 0, 0);  //Load the rest of Block 1
    // cin.get();
    for (int i = 1; i < 15; i++) {
        LoadData(&zebra[DMDBytesPerRow * DMDRowsPerBlock * i], DMDBytesPerRow * DMDRowsPerBlock, 0, 0);  //Load the other 14 blocks
    }

    SetRowMd(0, 0);
    SetBlkMd(3, 0);
    SetBlkAd(8, 0);
    LoadControl(0);

    Sleep(1);
    SetBlkMd(0, 0);

    LoadControl(0);
    LoadControl(0);
    // SetGPIORESETCOMPLETE(0);
    delete[] zebra;
}

short myPowerDownPrep(short devNum) {
    // short result = USB::SetPWRFLOAT(1, devNum);
    using namespace USB;

    SetRowMd(0, 0);
    SetBlkMd(3, 0);
    SetBlkAd(12, 0);
    LoadControl(0);

    Sleep(1);
    SetBlkMd(0, 0);

    LoadControl(0);
    LoadControl(0);
    return 0;
}

void myLoadPattern(std::string patFilename, const int imageByteSize, short devNum) {

    const int DMDBytesPerRow = 240;
    const int DMDRowsPerBlock = 72;

    std::fstream datFile;
    
    datFile.open(patFilename, std::ios::in | std::ios::binary);
    unsigned char* myPattern = new unsigned char[imageByteSize];

    if (datFile) { 
        datFile.read(reinterpret_cast<char*>(myPattern), imageByteSize);
        datFile.close();
    }
    else {
        std::string errMsg = std::string("Error opening pattern file: ") + patFilename;
        std::cout << errMsg << std::endl;
        exit(1);
    }

    USB::SetBlkMd(0, devNum);         //Set BlkMode to No Op
    USB::SetRowMd(3, devNum);       //Set Row Mode to Set Address mode
    USB::SetRowAddr(0, devNum);     //Set the Row address to the top of the DMD

    USB::SetRowMd(1, 0);              //Set the DMD pointer to Increment mode  (e2e)
  
    for (int i = 1; i < 15; i++) {
        USB::LoadData(myPattern + (DMDBytesPerRow * DMDRowsPerBlock * i), 
            DMDBytesPerRow * DMDRowsPerBlock, 0, devNum);  //Load all 15 blocks
    }

    USB::SetRowMd(0, devNum);
    USB::SetBlkMd(3, devNum);
    USB::SetBlkAd(8, devNum);
    USB::LoadControl(devNum);

    Sleep(1);
    USB::SetBlkMd(0, 0);

    USB::LoadControl(devNum); 
    USB::LoadControl(devNum);

    delete[] myPattern;

}

namespace myTemp {
    void SaveZebra(bool zebraState) {
        const int imageByteSize = 1920 * 1080 / 8;
        const int DMDBytesPerRow = 240;
        const int DMDRowsPerBlock = 72;
        const int BlocksPerLoad = 2;

        unsigned char* zebra = new unsigned char[imageByteSize];

        if (zebraState) {

            for (int i = 0; i < 1920 * 1080 / 8; i++)
            {
                if (i % (240 * 72 * 2) < 240 * 72)
                    zebra[i] = 0x00;
                else
                    zebra[i] = 0xff;
            }
        }
        else {
            for (int i = 0; i < 1920 * 1080 / 8; i++)
            {
                if (i % (240 * 72 * 2) < 240 * 72)
                    zebra[i] = 0xff;
                else
                    zebra[i] = 0x00;
            }
        }

        std::fstream datFile;
        if (zebraState)
            datFile.open("zebra1.bin", std::ios::out | std::ios::binary);
        else
            datFile.open("zebra0.bin", std::ios::out | std::ios::binary);

        if (datFile) {
            datFile.write(reinterpret_cast<char*>(zebra), imageByteSize);
            datFile.close();
        }
        else {
            std::cout << "Error opening file for writing !" << std::endl;
            exit(1);
        }

        delete[] zebra;

    }
}