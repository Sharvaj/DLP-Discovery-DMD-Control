%% This is a demo script that shows all functionality

SetPaths

debug = true; 
% debug = true : access the executable from DMDControler/bin/Debug
%
% Set debug = false if the build configuration of the executable is 'Release'
% debug = false : access the executable from DMDController/bin/Release
% 

%% 1) Initialize DMD

InitializeDMD(debug)

%% 2) Active box positioning

%Size of active window 
bh = 512;
bw = 512;
%Top left position for active window 
topBuffer = 250;
leftBuffer = 704;

% Call function from MatlabUtilities
ActiveBoxPositioning(bh, bw, topBuffer, leftBuffer, debug)


%% 2) Point scan within the active box

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
% Cycle or only one point
cycleAll = true;

% Call function from MatlabUtilities
EmbedPointScanner(bh, bw, topBuffer, leftBuffer, loch, locw, binSize, cycleAll, debug)

%% 3) Embed a pattern inside the active box

% .bin file containing the pattern
patFile = 'data/embeddedTrial.bin';

%Size of active window (this must be compatible with the pattern saved in patFile
% Here the patern in embeddedTrial.bin is 512x512
bh = 512;
bw = 512;
%Top left position for active window 
topBuffer = 250;
leftBuffer = 704;

% Call function from MatlabUtilities
EmbedLoadPattern(patFile, bh, bw, topBuffer, leftBuffer, debug)

%% 4) Float the DMD mirrors
% This must be done before turning off the power

FloatDMD(debug)

