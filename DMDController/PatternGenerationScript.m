%% 
clearvars
saveLocation = ['DMDController' filesep 'data' filesep 'PSPatterns_240-135'];


DMDInfo = struct;
DMDInfo.nrow = 1080;
DMDInfo.ncol = 1920;
DMDInfo.npix = DMDInfo.nrow * DMDInfo.ncol;

patternInfo.nh = DMDInfo.nrow/8;
patternInfo.nw = DMDInfo.ncol/8;

%% Script to save PS patterns

GenPointScanPatterns(saveLocation, DMDInfo, patternInfo);

%% Load and plot
binFilename = [saveLocation filesep 'PointScan_from_135-240_ind_1-3.bin'];

PlotBinaryData(binFilename, DMDInfo)

