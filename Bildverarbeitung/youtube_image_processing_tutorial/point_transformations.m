i = imread('cameraman.tif');
i1 = i > 120;
figure(1), imshow(i1), impixelinfo
id = double(i);
id1 = id+100;       
figure(2), imshow(uint8(id1)),impixelinfo % increasing intensity by fixed margin

id2 = id - 50;      % decreasing intensity by fixed number
figure(3), imshow(i);
id2 = imadd(i,100);
impixelinfo;
y = imsubtract(i,30);
figure(4), imshow(y);
z = immultiply(i,0.5);
figure(5), imshow(z);
a = imdivide(i,0.5);
figure(6), imshow(a), impixelinfo;
b = imcomplement(i);
figure(7), imshow(b), impixelinfo;

%% building own functions 
a = imread('cameraman.tif');
ad = im2double(a);
x = ad; y = ad;
[r,c] = size(ad);
factor = 1;
for i = 1:r
    for j = 1:r
        x(i,j) = factor * log(1+ad(i,j));   % logarithmic operator, reducing contrast in brighter regions
        y(i,j) = factor * ad(i,j) ^20;      % exponential operator, enhancing contrast of brighter regions
    end
end
subplot(1,2,1);imshow(ad);title('before'), impixelinfo;
subplot(1,2,2);imshow(x);title('after');
figure, imshow(y)