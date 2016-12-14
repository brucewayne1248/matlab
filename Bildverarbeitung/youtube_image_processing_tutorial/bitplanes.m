c = imread('cameraman.tif');
cd = double(c);

% representing bitplanes in binaray:
% most significant bit ->0000 0000 <- least significant bit

c0 = floor(mod(cd,2));
c1 = floor(mod(cd/2,2));
c2 = floor(mod(cd/4,2));
c3 = floor(mod(cd/8,2));
c4 = floor(mod(cd/16,2));
c5 = floor(mod(cd/32,2));
c6 = floor(mod(cd/64,2));
c7 = floor(mod(cd/128,2));
figure, imshow(c0);
figure, imshow(c1);
figure, imshow(c2);
figure, imshow(c3);
figure, imshow(c4);
figure, imshow(c5);
figure, imshow(c6);
figure, imshow(c7);

