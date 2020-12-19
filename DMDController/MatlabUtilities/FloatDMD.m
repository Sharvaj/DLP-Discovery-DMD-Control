function FloatDMD(debug)

callerMode = 'Float';

if debug
    exeFullFile = 'DMDController\bin\Debug\DMDController.exe';
else 
    exeFullFile = 'DMDController\bin\Release\DMDController.exe';
end

cmdInput = [exeFullFile, ' ', callerMode];

[status, cmdout] = system(cmdInput);

disp(['Status: ', num2str(status)])
disp(cmdout)

end
