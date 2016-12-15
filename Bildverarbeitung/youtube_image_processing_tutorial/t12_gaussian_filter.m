close all;
a = imread('cameraman.tif');
an = imnoise(a,'gaussian',0.01);

figure, imshow(a);
figure, imshow(an);

sigma = 3;
cutoff = ceil(3*sigma);
h = fspecial('gaussian',2*cutoff+1, sigma);
out = conv2(double(a),h,'same');
out1 = conv2(double(an),h,'same');
figure, imshow(out/256);
figure, imshow(out1/256);
%% wiener filter to remove gaussian noise
w = wiener2(an,[5 5]);
figure, imshow(w);

surf(1:2*cutoff+1, 1:2*cutoff+1, h);