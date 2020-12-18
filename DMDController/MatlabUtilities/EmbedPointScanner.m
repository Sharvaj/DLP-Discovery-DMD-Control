function EmbedPointScanner(bh, bw, topBuffer, leftBuffer, loch, locw, binSize, cycleAll)

exeFullFile = 'DMDController\bin\Debug\DMDController.exe';
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