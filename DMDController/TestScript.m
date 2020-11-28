%% // Testing: calling executable from MATLAB using system()

callerMode = 'I';
exeFullFile = 'DMDController\bin\Debug\DMDController.exe';

cmdInput = [exeFullFile, ' ', callerMode];

[status, cmdout] = system(cmdInput);

disp(['Status: ', num2str(status)])
disp(cmdout)


%% // Testing: converting 

info = struct;
info.npix = 64;

myPattern = 1.0 * (randn([8,8])>0);

imagesc(myPattern);
colormap(gray);
pause;

myArray = MakeByteArray(myPattern, info);

myArray
