function [ binRed ] = filterRed( image, levelRed )
%REDFILTER Filters an RGB image for red level and returns binary image
%   Detailed explanation goes here

diff_im = imsubtract(image(:,:,1), rgb2gray(image));

diff_im = medfilt2(diff_im, [3 3]);

binRed = im2bw(diff_im, levelRed);

end

