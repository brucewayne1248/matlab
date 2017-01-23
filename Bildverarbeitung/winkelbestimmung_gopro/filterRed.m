function [ binRed ] = filterRed( image, levelRed )
% filters an RGB image for levelRed[0...1] and returns binary image
%   Detailed information

diff_im = imsubtract(image(:,:,1), rgb2gray(image));

diff_im = medfilt2(diff_im, [3 3]);

binRed = im2bw(diff_im, levelRed);

end

