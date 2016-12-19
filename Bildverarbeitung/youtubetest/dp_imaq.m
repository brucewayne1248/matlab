%% Reading video
v = VideoReader('dp.mp4');

% for saving into new video
writerObj = VideoWriter('newdp.avi');
writerObj_bin = VideoWriter('newdp_bin.avi');
open(writerObj);
open(writerObj_bin);

k = 1;
while hasFrame(v)
    image = readFrame(v);
    
    % red image hist
%     figure(1), imhist(image(:,:,1))
    % Now to track red objects in real time
    % we have to subtract the red component
    % from the grayscale image to extract the red components in the image.
    diff_im = imsubtract(image(:,:,1), rgb2gray(image));
    % Use median filter to filter out noise
    diff_im = medfilt2(diff_im, [3 3]);
    % Convert the resulting grayscale image into a binary image.
    diff_im = im2bw(diff_im,0.095);
    diff_im_bin = diff_im;
    % Remove all those pixels less than 300px
    diff_im = bwareaopen(diff_im,1000);
    diff_im_blop = diff_im;
    figure(3), imshowpair(diff_im_bin,diff_im_blop,'montage')   
    montage = getframe;
    writeVideo(writerObj_bin,montage);
    % Label all the connected components in the image.
    bw = bwlabel(diff_im, 8);
    % Here we do the image blob analysis.
    % We get a set of properties for each labeled region.
    stats = regionprops(bw, 'BoundingBox', 'Centroid');
    % Display the image
    figure(2)
    imshow(image), impixelinfo
    
    % plot images with boxes
    hold on
    
    % This is a loop to bound the red objects in a rectangular box.
    for object = 1:length(stats)
        bb = stats(object).BoundingBox;
        bc = stats(object).Centroid;
        rectangle('Position',bb,'EdgeColor','r','LineWidth',2)
        plot(bc(1),bc(2), '-m+')
        a=text(bc(1)+15,bc(2), strcat('X: ', num2str(round(bc(1))), '    Y: ', num2str(round(bc(2)))));
        set(a, 'FontName', 'Arial', 'FontWeight', 'bold', 'FontSize', 12, 'Color', 'yellow');
    end
    % get frame of the figure
    F = getframe;
    hold off
    
    % write each frame of figure into new video
    writeVideo(writerObj,F);
    k = k+1;
%     pause(0.2)
end
close(writerObj);
close(writerObj_bin);