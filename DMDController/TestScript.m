%% Point scan
%Size of active window 
bh = 512;
bw = 512;
%Top left position for active window 
topBuffer = 250;
leftBuffer = 704;

%Starting position 
loch = 0;
locw = 0;
%Size of block 
binSize = 8;
cycleAll = true;
EmbedPointScanner(bh, bw, topBuffer, leftBuffer, loch, locw, binSize, cycleAll)

% exeFullFile = 'DMDController\bin\Debug\DMDController.exe';
% 
% ws = ' ';
% cmdInput = [exeFullFile, ws, 'EmbedPointScan', ws];
% cmdInput = [cmdInput, num2str(bh), ws];
% cmdInput = [cmdInput, num2str(bw), ws];
% cmdInput = [cmdInput, num2str(topBuffer), ws];
% cmdInput = [cmdInput, num2str(leftBuffer), ws];
% cmdInput = [cmdInput, num2str(loch), ws];
% cmdInput = [cmdInput, num2str(locw), ws];
% cmdInput = [cmdInput, num2str(binSize)];
% 
% [status, cmdout] = system(cmdInput);

%%
exeFullFile = 'DMDController\bin\Debug\DMDController.exe';
cmdInput = [exeFullFile, ' ', 'Default'];
%cmdInput = [exeFullFile, ' ', 'Pos 512 512 284 704 '];
cmdInput = [exeFullFile, ' ', 'Pos 512 512 250 704 '];
%cmdInput = [exeFullFile, ' ', 'EmbedLoad 512 512 128 128 ', 'data/embeddedTrial.bin'];

[status, cmdout] = system(cmdInput)



%% //
%Size : 1080 x 1920 
trialIm = 1* (randn(128,128) > 0);
trialIm = imresize(trialIm, [512, 512], 'nearest');
info.npix = 512*512;

%Make binary pattern 
byteArray = MakeByteArray(trialIm, info);
%Specify the pattern file name for saving 
fileName = 'DMDController\data\embeddedTrial.bin';
%Save the pattern file in .bin 
elemCount = SaveByteArray(fileName, byteArray);
%Name of DMD controller exe 
exeFullFile = 'DMDController\bin\Debug\DMDController.exe';
%%
%Generate Commaand line to display the pattern 
%Eg: EmbedLoad (Height , width , top pos, left pos) + file name 
cmdInput = [exeFullFile, ' ', 'EmbedLoad 512 512 284 704 ', 'data/embeddedTrial.bin'];
%cmdInput = [exeFullFile, ' ', 'EmbedLoad 512 512 128 128 ', 'data/embeddedTrial.bin'];

%Run based on cmdInput 
[status, cmdout] = system(cmdInput)

%% // Testing: calling executable from MATLAB using system()

%Command mode 'Init / Float'
%callerMode = 'Init';
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


