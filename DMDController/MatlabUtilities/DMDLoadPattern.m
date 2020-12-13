function DMDLoadPattern(patFolder, patName, displayOutput)

callerMode = 'Load';
exeFullFile = 'DMDController\bin\Debug\DMDController.exe';

cmdInput = [exeFullFile, ' ', callerMode, ' ', ...
                'data', '/', patFolder, '/', patName];

[status, cmdout] = system(cmdInput);

if displayOutput   
    disp(['Status: ', num2str(status)])
    disp(cmdout)
end

end