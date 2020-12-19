function DMDLoadPattern(patFile, displayOutput)
% Loads a 1920-by-1080 pixel pattern onto the DMD
% Patfile: location and name of file inside the 'data' folder
% The prefix 'data/' is added by default
%
% NOTE: only works with the Debug configuration executable
% For the Release version, use the newer function in EmbedLoadPattern.m


callerMode = 'Load';
exeFullFile = 'DMDController\bin\Debug\DMDController.exe';

cmdInput = [exeFullFile, ' ', callerMode, ' ', ...
                'data/', patFile];

[status, cmdout] = system(cmdInput);

if displayOutput   
    disp(['Status: ', num2str(status)])
    disp(cmdout)
end

end