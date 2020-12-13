%% // Testing: calling executable from MATLAB using system()

callerMode = 'Init';
callerMode = 'Float';
exeFullFile = 'DMDController\bin\Debug\DMDController.exe';

cmdInput = [exeFullFile, ' ', callerMode];

[status, cmdout] = system(cmdInput);

disp(['Status: ', num2str(status)])
disp(cmdout)

%%
ii = 6;
jj = 34;
patFolder = 'PSPatterns_240-135';
patName = ['PointScan_from_135-240_ind_' num2str(ii) '-' num2str(jj) '.bin'];

displayOutput = true;
DMDLoadPattern(patFolder, patName, displayOutput)

%%

DMDInfo = struct;
DMDInfo.nrow = 1080;
DMDInfo.ncol = 1920;

%% // Testing: converting to .bin

info = struct;
info.npix = 64;

myPattern = 1.0 * (randn([8,8])>0);

imagesc(myPattern);
colormap(gray);
% pause;

myArray = MakeByteArray(myPattern, info);

myArray


%% // Testing: converting to .bmp

info = struct;
info.npix = 64;

myPattern = 1.0 * (randn([8,8])>0);

imagesc(myPattern);
colormap(gray);
% pause;

fileName = ['DMDController' filesep 'data' filesep 'smallTest.bmp'];
SaveBMP(fileName, myPattern, info);

%%

numBytes = 64/8;
myPattern2 = string(myPattern*1).';
myPattern2 = reshape(myPattern2, [8, numBytes]).';

myArray = strings(numBytes, 1);

for jj = 1:numBytes
    myArray(jj) = strjoin(myPattern2(jj,:), '');
end


