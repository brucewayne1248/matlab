clear all, close all,
a = imread('circuit.tif');
e1 = edge(a,'prewitt');
e2 = edge(a,'canny');
e3 = edge(a,'sobel');
e4 = edge(a,'roberts');

figure, imshow(a)
figure,
subplot(2,2,1),imshow(e1), impixelinfo
subplot(2,2,2),imshow(e2), impixelinfo
subplot(2,2,3),imshow(e3), impixelinfo
subplot(2,2,4),imshow(e4), impixelinfo

%% self-made prewitt filter

ic = imread('circuit.tif');
px = [-1 0 1; -1 0 1; -1 0 1];
icx = filter2(px,ic);
figure, imshow(icx/256);
py = px'
icy = filter2(py,ic);
pedge = sqrt(icx.^2+icy.^2);
figure, imshow(pedge/256);
