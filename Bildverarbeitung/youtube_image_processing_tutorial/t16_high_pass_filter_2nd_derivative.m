clear all, close all,
% figure, imshow('t16_2nd_derivative.png')    
% figure, imshow('t16_filter.png')    % kernel for filter

i = imread('circuit.tif');
f1 = [0 1 0; 1 -4 1; 0 1 0]; % laplacian filter with 3x3 kernel

if1 = filter2(f1,i,'same');
if1conv = conv2(i,f1,'valid'); 

figure, 
subplot(1,2,1), imshow(i);
subplot(1,2,2), imshow(if1);

figure, 
subplot(1,2,1), imshow(i);
subplot(1,2,2), imshow(if1conv);


flaplace = fspecial('laplacian');
if2 = filter2(flaplace,i,'same');
s
figure, 
subplot(1,2,1), imshow(i);
subplot(1,2,2), imshow(if2);

%%
e = edge(i,'log'); % log = laplacian of gaussian, first gaussian filter  and then laplacian mask
figure,imshow(e);
h = fspecial('disk');
e1 = edge(i,'zerocross',h);
figure, imshow(e1);