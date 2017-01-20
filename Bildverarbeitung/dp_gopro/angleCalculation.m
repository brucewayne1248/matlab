clear all; close all;
%% Reading video
v = VideoReader('X:\group\Aufnahmen\ausschwing01cut.MP4')
% v.CurrentTime = 0.25;
frameRate = v.FrameRate;
% v = VideoReader(v);
% for saving into new video
% writerObj = VideoWriter('newdp.avi');
% writerObj.FrameRate = 1;
% writerObj.FrameRate = v.FrameRate;
% writerObj_bin = VideoWriter('newdp_bin.avi');
% open(writerObj);
% open(writerObj_bin);
phi1VideoDeg =  [];
phi2VideoDeg =  [];
%counter
k = 1;
while hasFrame(v)
    k = k+1;
    % save each frame in image
    image = readFrame(v);
    
    % filters image according to intensity level [0...1] and returns binary image
    binRed = filterRed(image, 0.12);
    binGreen = filterGreen(image, 0.03);
    binBlue = filterBlue(image, 0.08);
%    
% plots to find color levels
%     figure(1), imshowpair(image ,binRed, 'montage'), impixelinfo
%     figure(2), imshowpair(image ,binGreen, 'montage'), impixelinfo
%     figure(3), imshowpair(image ,binBlue, 'montage'), impixelinfo

% manual adjustment 
% binRed = manualPreFilter(binRed, 635, 720, 1091, 1280); 
binGreen = manualPreFilter(binGreen, 205, 720, 1, 1280);
binBlue = manualPreFilter(binBlue, 1, 720, 1, 326);
binBlue = manualPreFilter(binBlue, 1, 720, 1100, 1280); 
    
% Remove all those blobs less than certain pixel number
    binRedSize = bwareaopen(binRed, 310);
    binGreenSize = bwareaopen(binGreen, 500);
    binBlueSize = bwareaopen(binBlue, 500);

    % Remove all blobs less than and higher than certain pixel number
%     lbRed = 200; ubRed = 500;
%     binRedSize = xor(bwareaopen(binRed,lbRed), bwareaopen(binRed, ubRed));

    % Label all the connected components in the image.
    bwRed = bwlabel(binRedSize, 8);
    bwGreen = bwlabel(binGreenSize, 8);
    bwBlue = bwlabel(binBlueSize, 8);
    % image blob analysis
    % We get a set of properties for each labeled region.
    statsRed = regionprops(bwRed, 'Area', 'BoundingBox', 'Centroid');
    statsGreen = regionprops(bwGreen, 'Area', 'BoundingBox', 'Centroid');
    statsBlue = regionprops(bwBlue, 'Area', 'BoundingBox', 'Centroid');
%     
% Winkelberechnung

cenroidGreen = [6.347428571428571e+02 1.766952380952381e+02];
try
    phi1VideoDeg(k) = winkel(centroidGreen, statsBlue.Centroid);
catch ME
    phi1VideoDeg(k) = phi1VideoDeg(k-1);
end

try
    phi2VideoDeg(k) = winkel(statsBlue.Centroid, statsRed.Centroid);
catch ME
    phi2VideoDeg(k) = phi2VideoDeg(k-1);
end

%% debugging: display calculated angles, blobs, centroids

binTotal = binRedSize + binGreenSize + binBlueSize;

%     red
figure(4), imshow(binTotal), impixelinfo, hold on
%     figure(4), plot(binRedSize), hold on %, impixelinfo, hold on
    for object = 1:length(statsRed)
        bbRed = statsRed(object).BoundingBox;
        cRed = statsRed(object).Centroid;
        areaRed = statsRed(object).Area;
        rectangle('Position',bbRed,'EdgeColor','r','LineWidth',2)
        plot(cRed(1),cRed(2), '-m+')
        a=text(cRed(1)+15,cRed(2), strcat('X: ', num2str(round(cRed(1))), '    Y: ', num2str(round(cRed(2))), '   Area: ', num2str(round(areaRed))));
        set(a, 'FontName', 'Arial', 'FontWeight', 'bold', 'FontSize', 12, 'Color', 'yellow');
%         b=text(40,20, strcat('phi1: ', num2str(round2(phi1VideoDeg(k),2)), '  phi2: ', num2str(round2(phi2VideoDeg(k),2))));
%         set(b, 'FontName', 'Arial', 'FontWeight', 'bold', 'FontSize', 12, 'Color', 'yellow');
    end
%     hold off 
% 
% %     green
    plot(binGreenSize) %, impixelinfo %, hold on
%     loop for green objects
    for object = 1:length(statsGreen)
        bbGreen = statsGreen(object).BoundingBox;
        cGreen = statsGreen(object).Centroid;
        areaGreen = statsGreen(object).Area;
        rectangle('Position',bbGreen,'EdgeColor','r','LineWidth',2)
        plot(cGreen(1),cGreen(2), '-m+')
        a=text(cGreen(1)+15,cGreen(2), strcat('X: ', num2str(round(cGreen(1))), '    Y: ', num2str(round(cGreen(2))), '   Area: ', num2str(round(areaGreen))));
        set(a, 'FontName', 'Arial', 'FontWeight', 'bold', 'FontSize', 12, 'Color', 'yellow');
    end
% %     hold off 
%      
% %     blue
    plot(binBlueSize) %, impixelinfo %, hold on
    %loop for blue objects
    for object = 1:length(statsBlue)
        bbBlue = statsBlue(object).BoundingBox;
        cBlue = statsBlue(object).Centroid;
        areaBlue = statsBlue(object).Area;
        rectangle('Position',bbBlue,'EdgeColor','r','LineWidth',2)
        plot(cBlue(1),cBlue(2), '-m+')
        a=text(cBlue(1)+15,cBlue(2), strcat('X: ', num2str(round(cBlue(1))), '    Y: ', num2str(round(cBlue(2))), '   Area: ', num2str(round(areaBlue))));
        set(a, 'FontName', 'Arial', 'FontWeight', 'bold', 'FontSize', 12, 'Color', 'yellow');
    end
    hold off
% %     F = getframe;
% %     writeVideo(writerObj,F);
  %%
      pause(0.005)
end
% close(writerObj);
% close(writerObj_bin);