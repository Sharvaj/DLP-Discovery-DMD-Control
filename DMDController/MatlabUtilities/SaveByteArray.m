function elemCount = SaveByteArray(fileName, byteArray)

fileID = fopen(fileName,'w');
elemCount = fwrite(fileID, byteArray);
fclose(fileID);

end

