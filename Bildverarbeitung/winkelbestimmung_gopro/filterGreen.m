function [ binGreen ] = filterGreen( image, levelGreen )
%REDFILTER Filters an RGB image for green level and returns binary image
%   Detailed explanation goes here

binGreen = imsubtract(image(:,:,2), rgb2gray(image));

binGreen = medfilt2(binGreen, [3 3]);

binGreen = im2bw(binGreen, levelGreen);

end

