function SaveBMP(fileName, myPattern, info) 
% myArray will be of type uint8
% info is a struct

fileName = char(fileName);
if ~strcmp('.bmp', fileName(end-3:end))
    error('An extension of .bmp is needed in fileName');
end

myPattern = logical(myPattern);
imwrite(myPattern, fileName);

end

