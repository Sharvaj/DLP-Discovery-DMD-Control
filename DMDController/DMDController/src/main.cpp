
//# include "D4100_usb.h"
//# include <Windows.h>


#include "8055.D4100_usb.h"
#include "CyAPI.h"
#include "RegisterDefines.h"

# include "MyHeaders.h"

// # include other stuff if needed



int main(int argc, char** argv) {

    std::cout << argc << std::endl;
    std::cout << "This is the DMD control code!" << std::endl;

    std::cout << "Arguments:" << std::endl;
    for (int jj = 0; jj < argc; jj++)
        std::cout << argv[jj] << std::endl;

    // char* inputState = argv[1];

    short x = USB::GetNumDev();
    std::cout << "Number of devices: " << x << std::endl;

    short devNum = x - 1;


    std::string binFile;
    std::string patFileDir = "DMDController/";

    if (argc == 2) {

        if (argv[1][0] == 'I') {
            int myFlag = myInitializeDMD(devNum);
            
            std::cout << "Initialization result: " << myFlag << std::endl;
            return 0;
        }
        else if (argv[1][0] == 'F') {
            short result = myPowerDownPrep(devNum);
            return 0;
        }
    }
    else if (argc == 3) {
        if (argv[1][0] == 'L') {
            std::cout << "Patterns are currently accessed from "
                << patFileDir << std::endl;
            std::cout << argv[2] << std::endl;
            binFile = argv[2];
        }
            
    }
    else {
        std::cout << "Command line arguments are absent or not meaningful" << std::endl;
        std::cout << "Loading default pattern into DMD ..." << std::endl;
        std::cout << "Patterns are currently accessed from "
            << patFileDir << std::endl;
        binFile = "data/zebra1.bin";
    }
            
        
    //std::string patFilename = "DMDController/data/zebra1.bin";
    
    std::string patFilename = patFileDir + binFile;
    const int imageByteSize = 1920 * 1080 / 8;

    myLoadPattern(patFilename, imageByteSize, devNum);

    //myLoadZebra(true);

    // myTemp::SaveZebra(true);

    // myLoadZebra(false);

    //for (int j = 0; j < 30; j++) {
    //    myLoadZebra(j % 2); // TODO: UNCOMMENT  
    //    
    //}





    return 0;
}


