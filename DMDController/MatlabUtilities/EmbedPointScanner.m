function EmbedPointScanner(bh, bw, topBuffer, leftBuffer, loch, locw, binSize, cycleAll, debug)
% Point scan inside the active box
%
% bh: active box height,  bw: active box width
% topBuffer: num of black rows above the active box
% leftBuffer: num of black columns to the left of the active box
% binSize: length of the square white block in pixels
% loch and locw: i and j indices of white block
% 0 <= loch < bh/binSize, 0 <= locw < bw/binSize
%
% cycleAll: if true, loop through the raster scan; if false, just one point


if debug
    exeFullFile = 'DMDController\bin\Debug\DMDController.exe';
else 
    exeFullFile = 'DMDController\bin\Release\DMDController.exe';
end

ws = ' ';

%Divide to get number of steps to move 
pbh = bh/binSize; % post bin height
pbw = bw/binSize; % post bin width

if ~cycleAll
    
    cmdInput = [exeFullFile, ws, 'EmbedPointScan', ws];
    cmdInput = [cmdInput, num2str(bh), ws];
    cmdInput = [cmdInput, num2str(bw), ws];
    cmdInput = [cmdInput, num2str(topBuffer), ws];
    cmdInput = [cmdInput, num2str(leftBuffer), ws];
    cmdInput = [cmdInput, num2str(loch), ws];
    cmdInput = [cmdInput, num2str(locw), ws];
    cmdInput = [cmdInput, num2str(binSize)];

    [status, cmdout] = system(cmdInput)
    
else
    for ii = loch:pbh-1
        for jj = locw:pbw-1
            cmdInput = [exeFullFile, ws, 'EmbedPointScan', ws];
            cmdInput = [cmdInput, num2str(bh), ws];
            cmdInput = [cmdInput, num2str(bw), ws];
            cmdInput = [cmdInput, num2str(topBuffer), ws];
            cmdInput = [cmdInput, num2str(leftBuffer), ws];
            cmdInput = [cmdInput, num2str(ii), ws];
            cmdInput = [cmdInput, num2str(jj), ws];
            cmdInput = [cmdInput, num2str(binSize)];
            [status, cmdout] = system(cmdInput);
            disp(sprintf('ii = %d, jj = %d:  status = %d', ii, jj, status));
        end
    end

end