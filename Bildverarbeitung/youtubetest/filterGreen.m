function [ binGreen ] = filterGreen( image, levelGreen )
%REDFILTER Filters an RGB image for green level and returns binary image
%   Detailed explanation goes here

diff_im = imsubtract(image(:,:,2), rgb2gray(image));

diff_im = medfilt2(diff_im, [3 3]);

binGreen = im2bw(diff_im, levelGreen);

end

