function EmbedLoadPattern(patFile, bh, bw, topBuffer, leftBuffer, debug)
% Loads a pattern inside the active box (region of interest on the DMD)
% Patfile: location and name of file inside the 'data' folder
% The prefix 'data/' is added by default
% 
% bh: active box height,  bw: active box width
% topBuffer: num of black rows above the active box
% leftBuffer: num of black columns to the left of the active box
%
% Mechanism: this function calls DMDController.exe with the appropriate
% call mode 'EmbedLoad'. The actual logic and DMD operations are carried out by
% the functions in DMDController/src/ControllerFunctions.cpp

if debug
    exeFullFile = 'DMDController\bin\Debug\DMDController.exe';
else 
    exeFullFile = 'DMDController\bin\Release\DMDController.exe';
end

% Formatting the command line arguments to DMDController.exe
ws = ' ';
cmdInput = [exeFullFile, ws, 'EmbedLoad', ws];
cmdInput = [cmdInput, num2str(bh), ws];
cmdInput = [cmdInput, num2str(bw), ws];
cmdInput = [cmdInput, num2str(topBuffer), ws];
cmdInput = [cmdInput, num2str(leftBuffer), ws];
cmdInput = [cmdInput, 'data/', patFile]; 
% Note that the DMDController/ part of the file location is 
% handled by the C++ code.

% Using system() to call DMDController.exe with the appropriate command
% line arguments
[status, cmdout] = system(cmdInput);

if debug
   status
   cmdout
end
