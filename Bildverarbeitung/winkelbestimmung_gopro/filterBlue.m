function [ binBlue ] = filterBlue( image, levelBlue )
%REDFILTER Filters an RGB image for blue level and returns binary image
%   Detailed explanation goes here

binBlue = imsubtract(image(:,:,3), rgb2gray(image));

binBlue = medfilt2(binBlue, [3 3]);

binBlue = im2bw(binBlue, levelBlue);

end

