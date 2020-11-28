function myArray = MakeByteArray(myPattern, info) 
% myArray will be of type uint8
% info is a struct

if mod(info.npix, 8)
    error('Number of pixels must be divisible by 8 for byte-writing')
end
numBytes = info.npix/8;
myPattern = string(myPattern*1).';
myPattern = reshape(myPattern, [8, numBytes]).';

myArray = strings(numBytes, 1);

for jj = 1:numBytes
    myArray(jj) = strjoin(myPattern(jj,:), '');
end

myArray = uint8(bin2dec(myArray));

end

