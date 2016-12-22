clear all, close all;
rgb = imread('GOPR9325.JPG');
[masg_r, red] = labRed(rgb);
[masg_g, green] = labGreen(rgb);
[masg_b, blue] = labBlue(rgb);
figure, imshow(rgb)
figure, imshow(red)
figure, imshow(green)
figure, imshow(blue)