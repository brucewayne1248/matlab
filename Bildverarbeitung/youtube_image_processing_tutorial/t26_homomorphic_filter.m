a = imread('trees.tif');
im = im2double(a);
fftlogim = fft2(log(im+0.01));
