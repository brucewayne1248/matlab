close all
%% Reading video
v = VideoReader('dp.mp4');

k = 1;

while hasFrame(v)
    % extract frame
    image_rgb = readFrame(v);
%     close all

    % color segmenation
    [bw_r, red] = labRed(image_rgb);
    [bw_g, green] = labGreen(image_rgb);
    [bw_b, blue] = labBlue(image_rgb);
    
%     bw_total = bw_r + bw_g + bw_b;
%     figure(1), imshow(bw_r)
%     figure, imshow(red)
%     figure, imshow(green)
%     figure, imshow(blue)
%     pause(0.5)
end
