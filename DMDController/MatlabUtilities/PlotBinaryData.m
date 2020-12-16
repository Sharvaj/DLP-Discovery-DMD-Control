function PlotBinaryData(binFilename, DMDInfo)

fileID = fopen(binFilename,'r');
[data, elemCount] = fread(fileID);
fclose(fileID);
disp(elemCount)
data = dec2bin(data);
data = (data == '0'); % Due to flipped configuration

myImage = reshape(data.', [DMDInfo.ncol, DMDInfo.nrow]).'; 

figure();
imagesc(myImage);
colormap(gray)
daspect([1 1 1])

end