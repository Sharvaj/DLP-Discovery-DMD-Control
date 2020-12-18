
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
    short fl1 = SetWDT(1, devNum); // Enable WDT
    short fl2 = SetTPGEnable(0, devNum); // Disable TestPatternGenerator
    short fl3 = ClearFifos(devNum); // Initialize the DMD fifo.
    //SetNSFLIP(1, devNum);

    int myOutput = fl0 && fl1 && fl2 && fl3;
    return myOutput;
}

int myReprogramFPGA(short int devNum) {

    std::fstream FPGAFile;
    FPGAFile.open("DMDController/vendor/D4100_GUI_FPGA.bin", std::ios::in|std::ios::binary);
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

void myActiveBoxPositioning(int bh, int bw, int topBuffer, int leftBuffer, short devNum) {

    if ((leftBuffer % 8 != 0) || (bw % 8 != 0)) {
        std::cout << "leftBuffer must be a multiple of 8" << std::endl;
        exit(1);
    }
    const int DMDFullDisplayCols = 1920;
    const int DMDBytesPerRow = 240;
    //const int DMDBytesPerRow = 256;
    /*const int leftExtraBytes = 0;
    const int rightExtraBytes = 0;*/
    const int DMDTotalRows = 1080;
    const int DMDRowsPerBlock = 72;
    const int DMDNumBlocks = 15;
    const int DMDByteSize = DMDBytesPerRow * DMDTotalRows;
    const int rightBuffer = DMDFullDisplayCols - leftBuffer - bw;

    const int patternBytesPerRow = bw / 8;
    const int leftBufferBytesPerRow = leftBuffer / 8;
    
    const int rightBufferBytesPerRow = rightBuffer / 8;

    unsigned char eightBlack = 0xff;
    unsigned char eightWhite = 0x00;

    unsigned char* myFullPattern = new unsigned char[DMDByteSize];
    unsigned char* rowTraverser;
    for (int ir = 0; ir < DMDTotalRows; ir++) {  
        rowTraverser = myFullPattern + ir * DMDBytesPerRow;

        if (ir < topBuffer || ir >= topBuffer + bh) {
            std::fill_n(rowTraverser, DMDBytesPerRow, eightBlack);
        }
        else {

            
            std::fill_n(rowTraverser, leftBufferBytesPerRow, eightBlack);
            std::fill_n(rowTraverser + leftBufferBytesPerRow, patternBytesPerRow, eightWhite);
            std::fill_n(rowTraverser + leftBufferBytesPerRow + patternBytesPerRow, rightBufferBytesPerRow, eightBlack);

            
        }
    }

    int status = myLoadLive(myFullPattern, DMDByteSize, devNum);

   /* if (true) {
        std::string patFilename = "DMDController/data/AcBoxTest.bin";
        std::ofstream datFile(patFilename, std::ios::binary);
        if (!datFile) {
            std::cout << "Failure to open file:  " << patFilename << std::endl;
            exit(1);
        }
        datFile.write(reinterpret_cast<char*>(myFullPattern), DMDByteSize);
    }*/

    delete[] myFullPattern;
    std::cout << "DMD control status:  " << status << std::endl;
}

void myActiveBoxEmbedPattern(std::string patFilename, int bh, int bw, 
                                        int topBuffer, int leftBuffer, short devNum) {

    if ((leftBuffer % 8 != 0) || (bw % 8 != 0)) {
        std::cout << "leftBuffer and bh must be a multiple of 8" << std::endl;
        exit(1);
    }
    //const int DMDTotalCols = 1920;
    const int DMDFullDisplayCols = 1920;
    const int DMDBytesPerRow = 240;
    //const int DMDBytesPerRow = 256;
    /*const int leftExtraBytes = 8;
    const int rightExtraBytes = 8;*/
    const int DMDTotalRows = 1080;
    const int DMDRowsPerBlock = 72;
    const int DMDNumBlocks = 15;
    const int DMDByteSize = DMDBytesPerRow * DMDTotalRows;
    const int patternBytesPerRow = bw / 8;
    const int leftBufferBytesPerRow = leftBuffer / 8;
    const int rightBuffer = DMDFullDisplayCols - leftBuffer - bw;
    const int rightBufferBytesPerRow = rightBuffer / 8;

    unsigned char eightBlack = 0xff;
    unsigned char eightWhite = 0x00;

    unsigned char* myFullPattern = new unsigned char[DMDByteSize];
    std::ifstream datFile(patFilename, std::ios::binary);
    if (!datFile) {
        std::cout << "Failure to open file:  " << patFilename << std::endl;
        exit(1);
    }

    unsigned char* rowTraverser;
    for (int ir = 0; ir < DMDTotalRows; ir++) {
        rowTraverser = myFullPattern + ir * DMDBytesPerRow;       
        if (ir < topBuffer || ir >= topBuffer + bh) {
            std::fill_n(rowTraverser, DMDBytesPerRow, eightBlack);
        }
        else {
            
            std::fill_n(rowTraverser, leftBufferBytesPerRow, eightBlack);
            datFile.read(reinterpret_cast<char*>(rowTraverser + leftBufferBytesPerRow), 
                                                                                   patternBytesPerRow);
            std::fill_n(rowTraverser + leftBufferBytesPerRow + patternBytesPerRow,
                rightBufferBytesPerRow, eightBlack);
        }
        
    }

    int status = myLoadLive(myFullPattern, DMDByteSize, devNum);

   /* if (true) {
        std::string patFilename = "DMDController/data/AcBoxTest.bin";
        std::ofstream datFile(patFilename, std::ios::binary);
        if (!datFile) {
            std::cout << "Failure to open file:  " << patFilename << std::endl;
            exit(1);
        }
        datFile.write(reinterpret_cast<char*>(myFullPattern), DMDByteSize);
    }*/

    delete[] myFullPattern;
    std::cout << "DMD control status:  " << status << std::endl;

}

void myActiveBoxEmbedPointScan(int bh, int bw, int topBuffer, int leftBuffer, 
                                int loch, int locw, int binSize, short devNum) {
    
    if ((leftBuffer % 8 != 0) || (bw % 8 != 0)) {
        std::cout << "leftBuffer and bh must be a multiple of 8" << std::endl;
        exit(1);
    }
    
    if (binSize != 8) {
        std::cout << "For Point Scan, only binSize = 8 is supported as of now!" << std::endl;
        exit(1);
    }

    //bool outWhite = true;

    const int DMDFullDisplayCols = 1920;
    const int DMDBytesPerRow = 240;
    const int DMDTotalRows = 1080;
    const int DMDRowsPerBlock = 72;
    const int DMDNumBlocks = 15;
    const int DMDByteSize = DMDBytesPerRow * DMDTotalRows;
    const int patternBytesPerRow = bw / 8;
    const int leftBufferBytesPerRow = leftBuffer / 8;
    const int rightBuffer = DMDFullDisplayCols - leftBuffer - bw;
    const int rightBufferBytesPerRow = rightBuffer / 8;

    unsigned char eightBlack = 0xff;
    unsigned char eightWhite = 0x00;


    unsigned char* myFullPattern = new unsigned char[DMDByteSize];

    //Calculate which mirror to 'on / off' 
    unsigned char* rowTraverser;
    for (int ir = 0; ir < DMDTotalRows; ir++) {
        rowTraverser = myFullPattern + ir * DMDBytesPerRow;
        std::fill_n(rowTraverser, DMDBytesPerRow, eightBlack);
        if ((ir >= topBuffer + binSize*loch) && (ir < topBuffer + binSize*(loch+1)))
            *(rowTraverser + leftBufferBytesPerRow + locw) = eightWhite;

    }

    int status = myLoadLive(myFullPattern, DMDByteSize, devNum);

    delete[] myFullPattern;
    std::cout << "DMD control status:  " << status << std::endl;

}
                   
                                                
int myLoadLive(unsigned char* myFullPattern, const int DMDByteSize, short devNum) {
    
    const int DMDBytesPerRow = 240;
    
    const int DMDRowsPerBlock = 72;

    
    
    USB::SetBlkMd(0, 0);         //Set BlkMode to No Op
    USB::SetRowMd(3, 0);       //Set Row Mode to Set Address mode
    USB::SetRowAddr(0, 0);                      //Set the Row address to the top of the DMD

    USB::LoadData(&myFullPattern[0], DMDBytesPerRow, 0, devNum);  //Load the first row of data  (e2e)
    // cin.get();
    Sleep(1);
    USB::SetRowMd(1, 0);              //Set the DMD pointer to Increment mode  (e2e)
    USB::LoadData(&myFullPattern[DMDBytesPerRow], DMDBytesPerRow * (DMDRowsPerBlock - 1), 0, 0);  //Load the rest of Block 1
    Sleep(1);
    // cin.get();
    for (int i = 1; i < 15; i++) {
        USB::LoadData(&myFullPattern[DMDBytesPerRow * DMDRowsPerBlock * i], DMDBytesPerRow * DMDRowsPerBlock, 0, devNum);  //Load the other 14 blocks
    }
    
    
    int status = 0;

    status += USB::SetRowMd(0, devNum);
    status += USB::SetBlkMd(3, devNum);
    status += USB::SetBlkAd(8, devNum);
    status += USB::LoadControl(devNum);
    /*USB::LoadControl(devNum);
    USB::LoadControl(devNum);*/
    Sleep(1);
    status += USB::SetBlkMd(0, devNum);
    status += USB::LoadControl(devNum);
    status += USB::LoadControl(devNum);

    return status;
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
    Sleep(1);
    SetRowMd(1, 0);              //Set the DMD pointer to Increment mode  (e2e)
    LoadData(&zebra[DMDBytesPerRow], DMDBytesPerRow * (DMDRowsPerBlock - 1), 0, 0);  //Load the rest of Block 1
    Sleep(1);
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

    USB::SetRowMd(0, 0);
    USB::SetBlkMd(3, 0);
    USB::SetBlkAd(12, 0);
    USB::LoadControl(0);
    
    Sleep(1);
    USB::SetBlkMd(0, 0);
    
    USB::LoadControl(0);
    USB::LoadControl(0);
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
    
    Sleep(10);

    USB::SetBlkMd(0, devNum);         //Set BlkMode to No Op
    //USB::LoadControl(devNum);

    USB::SetRowMd(3, devNum);       //Set Row Mode to Set Address mode
    USB::SetRowAddr(0, devNum);     //Set the Row address to the top of the DMD

    //USB::SetRowMd(1, devNum);              //Set the DMD pointer to Increment mode  (e2e)
    //USB::SetNSFLIP(1, devNum);
   // USB::LoadControl(devNum);

    //USB::ClearFifos(devNum);
    USB::LoadData(&myPattern[0], DMDBytesPerRow, 0, devNum);  //Load the first row of data  (e2e)
    // cin.get();
    Sleep(1);
    USB::SetRowMd(1, 0);              //Set the DMD pointer to Increment mode  (e2e)
    USB::LoadData(&myPattern[DMDBytesPerRow], DMDBytesPerRow * (DMDRowsPerBlock - 1), 0, 0);  //Load the rest of Block 1
    Sleep(1);
    // cin.get();
    for (int i = 1; i < 15; i++) {
        USB::LoadData(&myPattern[DMDBytesPerRow * DMDRowsPerBlock * i], DMDBytesPerRow * DMDRowsPerBlock, 0, devNum);  //Load the other 14 blocks
    }

  
    //for (int i = 0; i < 15; i++) {
    //    USB::LoadData(myPattern + (DMDBytesPerRow * DMDRowsPerBlock * i), 
    //        DMDBytesPerRow * DMDRowsPerBlock, 0, devNum);  //Load all 15 blocks
    //}

    USB::SetRowMd(0, devNum);
    USB::SetBlkMd(3, devNum);
    USB::SetBlkAd(8, devNum);
    USB::LoadControl(devNum);
    /*USB::LoadControl(devNum);
    USB::LoadControl(devNum);*/
    Sleep(1);
    USB::SetBlkMd(0, 0);
    USB::LoadControl(devNum);
    USB::LoadControl(devNum); 
    
    //USB::LoadControl(devNum);

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
            datFile.open("DMDController/data/zebra1.bin", std::ios::out | std::ios::binary);
        else
            datFile.open("DMDController/data/zebra0.bin", std::ios::out | std::ios::binary);

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

    void LoadBMP(std::string patFilename, const int imageByteSize, short devNum) {
        const int DMDBytesPerRow = 240;
        const int DMDRowsPerBlock = 72;

        unsigned char* myPattern = nullptr;

        
        unsigned char* datBuff[2] = { nullptr, nullptr }; // Header buffers

        BITMAPFILEHEADER* bmpHeader = nullptr; // Header
        BITMAPINFOHEADER* bmpInfo = nullptr; // Info 

        std::ifstream datFile(patFilename, std::ios::binary);
        if (!datFile) {
            std::cout << "Failure to open bitmap file: " << patFilename << std::endl;
            exit(1);
        }

        // Allocate byte memory that will hold the two headers
        datBuff[0] = new unsigned char[sizeof(BITMAPFILEHEADER)];
        datBuff[1] = new unsigned char[sizeof(BITMAPINFOHEADER)];

        datFile.read(reinterpret_cast<char*>(datBuff[0]), sizeof(BITMAPFILEHEADER));
        datFile.read(reinterpret_cast<char*>(datBuff[1]), sizeof(BITMAPINFOHEADER));

        // Construct the values from the buffers
        bmpHeader = (BITMAPFILEHEADER*)datBuff[0];
        bmpInfo = (BITMAPINFOHEADER*)datBuff[1];

        // Check if the file is an actual BMP file
        if (bmpHeader->bfType != 0x4D42) {
            std::cout << "File \"" << patFilename << "\" isn't a bitmap file\n";
            exit(1);
        }

        // First allocate pixel memory
        myPattern = new unsigned char[bmpInfo->biSizeImage];
        std::cout << bmpInfo->biSizeImage << std::endl;
        // Go to where image data starts, then read in image data
        datFile.seekg(bmpHeader->bfOffBits);
        datFile.read(reinterpret_cast<char*>(myPattern), bmpInfo->biSizeImage);

        // Delete the two buffers.
        delete[] datBuff[0];
        delete[] datBuff[1];



        
        


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
    
}