function GenPointScanPatterns(saveLocation, DMDInfo, patternInfo)
% Generating point scan patterns by brute-force for the full 1920x1080 DMD
% NOTE: Not yet linked with the Active Box functions
% NOTE: Very slow and storage intensive
% Use instead, the function in EmbedPointScanner.m

sh = DMDInfo.nrow/patternInfo.nh;
sw = DMDInfo.ncol/patternInfo.nw;

if (sh~=round(sh)) || (sw~=round(sw))
    error('Pattern binning block is incompatible with DMD')
end

if sh~=sw
    error('Need binning block to be square for now')
end

basePattern = zeros([patternInfo.nh, patternInfo.nw]);

for ii = 1:patternInfo.nh
    for jj = 1:patternInfo.nw
        myFilename = [saveLocation filesep 'PointScan_from_' ...
            num2str(patternInfo.nh) '-' num2str(patternInfo.nw)...
            '_ind_' num2str(ii) '-' num2str(jj) '.bin'];
        basePattern(ii,jj) = 1;
        myPattern = imresize(basePattern, [DMDInfo.nrow, DMDInfo.ncol], 'nearest');
        myArray = MakeByteArray(myPattern, DMDInfo);
        elemCount = SaveByteArray(myFilename, myArray);
        disp(elemCount)
        
        basePattern(ii,jj) = 0;
    end
end
