function [ binRed ] = filterRed( image, levelRed )
% filters an RGB image for levelRed[0...1] and returns binary image
%   Detailed information

binRed = imsubtract(image(:,:,1), rgb2gray(image));

binRed = medfilt2(binRed, [3 3]);

binRed = im2bw(binRed, levelRed);

end

