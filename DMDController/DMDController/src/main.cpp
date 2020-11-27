
//# include "D4100_usb.h"
//# include <Windows.h>


#include "8055.D4100_usb.h"
#include "CyAPI.h"
#include "RegisterDefines.h"

# include "MyHeaders.h"

// # include other stuff if needed



int main(int argc, char** argv) {

    using namespace std;


    cout << "This is the DMD control code!" << endl;

    cout << "Arguments:" << endl;
    for (int jj = 0; jj < argc; jj++)
        cout << argv[jj] << endl;

    // char* inputState = argv[1];

    short x = USB::GetNumDev();
    cout << "Number of devices: " << x << endl;

    short devNum = x - 1;

    if (argc == 2) {
        if (argv[1][0] == 'I') {
            int myFlag = myInitializeDMD(devNum);
            cout << "Initialization result: " << myFlag << endl;
            return 0;
        }
        else if (argv[1][0] == 'X') {
            short result = myPowerDownPrep(devNum);
            return 0;
        }
    }


    std::string patFilename = "zebra0.bin";
    const int imageByteSize = 1920 * 1080 / 8;

    myLoadPattern(patFilename, imageByteSize, devNum);

    // myTemp::SaveZebra(true);

    // myLoadZebra(false);

    //for (int j = 0; j < 30; j++) {
    //    myLoadZebra(j % 2); // TODO: UNCOMMENT  
    //    
    //}





    return 0;
}


