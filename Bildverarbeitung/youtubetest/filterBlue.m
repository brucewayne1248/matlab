function [ binBlue ] = filterBlue( image, levelBlue )
%REDFILTER Filters an RGB image for blue level and returns binary image
%   Detailed explanation goes here

diff_im = imsubtract(image(:,:,3), rgb2gray(image));

diff_im = medfilt2(diff_im, [3 3]);

binBlue = im2bw(diff_im, levelBlue);

end

