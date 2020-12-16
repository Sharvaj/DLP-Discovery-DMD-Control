function ActiveBoxPositioning(bh, bw, topBuffer, leftBuffer)
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here

exeFullFile = 'DMDController\bin\Debug\DMDController.exe';

ws = ' ';
cmdInput = [exeFullFile, ws, 'Pos', ws];
cmdInput = [cmdInput, num2str(bh), ws];
cmdInput = [cmdInput, num2str(bw), ws];
cmdInput = [cmdInput, num2str(topBuffer), ws];
cmdInput = [cmdInput, num2str(leftBuffer)];

[status, cmdout] = system(cmdInput);

end

