close all;
i = imread('cameraman.tif');
f = ones(3,3)/9; % Filtermatrix
figure, imshow(i)

i1 = filter2(f,i,'same'); % shape same, valid, full
figure;
subplot(1,2,1), imshow(uint8(i1)), impixelinfo;
subplot(1,2,2), imshow(i1/255), impixelinfo;

f1 = fspecial('average',[3 3]);
i2 = filter2(f1,i,'same');
figure, imshow(i2/255), impixelinfo;

f3 = fspecial('average',11);
i3 = filter2(f3,i,'same');
figure, imshow(i3/255), impixelinfo;