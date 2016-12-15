close all; clear all;
i = imread('cameraman.tif');
isp = imnoise(i,'salt & pepper',0.1);
figure,imshow(isp);
a = fspecial('average');

a1 = filter2(a,isp);

figure, imshow(uint8(a1));
med = medfilt2(isp);
figure, imshow(med);

i2 = ordfilt2(isp,100,ones(5,5));
figure,imshow(i2);