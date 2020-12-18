function EmbedLoadPattern(patFile, bh, bw, topBuffer, leftBuffer, debug)
% Loads a pattern inside the active box (region of interest on the DMD)
% Patfile: location and name of file inside the 'data' folder
% The prefix 'data/' is added by default
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
cmdInput = [exeFullFile, ws, 'EmbedLoad', ws];
cmdInput = [cmdInput, num2str(bh), ws];
cmdInput = [cmdInput, num2str(bw), ws];
cmdInput = [cmdInput, num2str(topBuffer), ws];
cmdInput = [cmdInput, num2str(leftBuffer), ws];
cmdInput = [cmdInput, 'data/', patFile]; 
% Note that the DMDController/ part of the file location is 
% handled by the C++ code.

[status, cmdout] = system(cmdInput);

if debug
   status
   cmdout
end
