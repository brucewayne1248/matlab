a = imread('cameraman.tif');
[rows, columns] = size(a);
i = 1; j = 1;
c = zeros(rows/2, columns/2);
for x = 1:2:rows
    for y = 1:2:columns
        c(i,j) = a(x,y);
        j = j + 1;
    end
    i = i +1;
    j=1;
end
figure(1),imshow(a);
figure(2),imshow(c/255);
figure(3), imagesc(c), colormap(gray);

%% using inbuild commands
x = imread('cameraman.tif');
y = imresize(x,1/2);
figure(4), imagesc(y);
figure(5), imagesc(y),colormap(gray);