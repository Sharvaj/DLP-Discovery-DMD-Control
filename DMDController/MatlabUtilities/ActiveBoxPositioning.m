function ActiveBoxPositioning(bh, bw, topBuffer, leftBuffer, debug)
% Creates a white active box of the indicated size at the indicated position
%
% bh: active box height,  bw: active box width
% topBuffer: num of black rows above the active box
% leftBuffer: num of black columns to the left of the active box

if debug
    exeFullFile = 'DMDController\bin\Debug\DMDController.exe';
else 
    exeFullFile = 'DMDController\bin\Release\DMDController.exe';
end

ws = ' ';
cmdInput = [exeFullFile, ws, 'Pos', ws];
cmdInput = [cmdInput, num2str(bh), ws];
cmdInput = [cmdInput, num2str(bw), ws];
cmdInput = [cmdInput, num2str(topBuffer), ws];
cmdInput = [cmdInput, num2str(leftBuffer)];

[status, cmdout] = system(cmdInput);

end

