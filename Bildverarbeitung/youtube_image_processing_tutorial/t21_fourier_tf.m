clear all, close all,
a = imread('cameraman.tif');
af = fftshift(fft2(a));
% figure, imshow(af);

fftshow(af)
[x,y] = meshgrid(-128:127,-128:127);
z = sqrt(x.^2+y.^2);
c = z<50;

af1 = af.*c;
fftshow(af1)
af1i = ifft2(af1);
ifftshow(af1i);