/*if (true) {
        std::ifstream datFile("DMDController/data/littleTest.bin", std::ios::binary);
        if (!datFile) {
            std::cout << "Failure to open file!" << std::endl;
            exit(1);
        }
        char myData[2];
        datFile.read(myData, 1);
        datFile.read(myData+1, 1);
        std::cout << "myData[0] = " << (int)myData[0] << std::endl;
        std::cout << "myData[1] = " << (int)myData[1] << std::endl;
        return 0;
    }*/


//if (true) {
//
//
//    myActiveBoxPositioning(512, 512, 284, 704, devNum);
//
//}



//if (true) {
    //    USB::ClearFifos(devNum);
    //    Sleep(10);

    //    USB::SetBlkMd(0, 0);         //Set BlkMode to No Op
    //    USB::SetRowMd(3, 0);       //Set Row Mode to Set Address mode
    //    USB::SetRowAddr(0, 0);                      //Set the Row address to the top of the DMD
    //    USB::SetRowMd(1, 0);

    //    unsigned char myFullPattern[1] = { 0xff };


    //    for (int i = 0; i < 15; i++) {

    //        USB::LoadData(myFullPattern,
    //                          1, 0, devNum);  //Load all 15 blocks
    //    }