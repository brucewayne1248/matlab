%% Reading video
v = VideoReader('20170104_720p_240fps_ausschwing1.mp4');
% v.CurrentTime = 6.95;
frameRate = v.FrameRate;
% v = VideoReader(v);
% for saving into new video
writerObj = VideoWriter('newdp.avi');
writerObj.FrameRate = 1;
% writerObj.FrameRate = v.FrameRate;
% writerObj_bin = VideoWriter('newdp_bin.avi');
open(writerObj);
% open(writerObj_bin);

k = 0;
while hasFrame(v)
    k = k+1;
    image = readFrame(v);
    
    binRed = filterRed(image, 0.14);
    binGreen = filterGreen(image, 0.05);
    binBlue = filterBlue(image, 0.09);
    
% plots to find color levels
%     figure(1), imshowpair(image ,binRed, 'montage'), impixelinfo
%     figure(2), imshowpair(image ,binGreen, 'montage'), impixelinfo
%     figure(3), imshowpair(image ,binBlue, 'montage'), impixelinfo

% manual adjustment 
% red
binRed = manualPreFilter(binRed, 530, 575, 1230, 1280);
binBlue = manualPreFilter(binBlue, 441, 720, 1, 1280);
    
% Remove all those blobs less than certain pixel number
    binRedSize = bwareaopen(binRed, 300);
    binGreenSize = bwareaopen(binGreen, 400);
    binBlueSize = bwareaopen(binBlue, 300);

    % Remove all blobs less than and higher than certain pixel number
%     lbRed = 200; ubRed = 500;
%     binRedSize = xor(bwareaopen(binRed,lbRed), bwareaopen(binRed, ubRed));

%     montage = getframe;
%     writeVideo(writerObj_bin,montage);

    % Label all the connected components in the image.
    bwRed = bwlabel(binRedSize, 8);
    bwGreen = bwlabel(binGreenSize, 8);
    bwBlue = bwlabel(binBlueSize, 8);
    % image blob analysis
    % We get a set of properties for each labeled region.
    statsRed = regionprops(bwRed, 'Area', 'BoundingBox', 'Centroid');
    statsGreen = regionprops(bwGreen, 'Area', 'BoundingBox', 'Centroid');
    statsBlue = regionprops(bwBlue, 'Area', 'BoundingBox', 'Centroid');
    
% Winkelberechnung

try
phi1(k) = winkel(statsGreen.Centroid, statsBlue.Centroid);
catch ME
    phi1(k) = phi1(k-1);
end

try
    phi2(k) = winkel(statsBlue.Centroid, statsRed.Centroid);
catch ME
    phi2(k) = phi2(k-1);
end

 %% debugging
% binTotal = binRedSize + binGreenSize + binBlueSize;
% 
% %     red
% figure(4), imshow(binTotal), impixelinfo, hold on
% %     figure(4), plot(binRedSize), hold on %, impixelinfo, hold on
% %     This is a loop to bound the red objects in a rectangular box.
%     for object = 1:length(statsRed)
%         bbRed = statsRed(object).BoundingBox;
%         cRed = statsRed(object).Centroid;
%         areaRed = statsRed(object).Area;
%         rectangle('Position',bbRed,'EdgeColor','r','LineWidth',2)
%         plot(cRed(1),cRed(2), '-m+')
%         a=text(cRed(1)+15,cRed(2), strcat('X: ', num2str(round(cRed(1))), '    Y: ', num2str(round(cRed(2))), '   Area: ', num2str(round(areaRed))));
%         set(a, 'FontName', 'Arial', 'FontWeight', 'bold', 'FontSize', 12, 'Color', 'yellow');
%         b=text(10,10, strcat('phi1: ', num2str(round(phi1(k))), '  phi2: ', num2str(round(phi2(k)))));
%         set(b, 'FontName', 'Arial', 'FontWeight', 'bold', 'FontSize', 12, 'Color', 'yellow');
%     end
% %     hold off 
% 
% %     green
% %     figure(5),
%     plot(binGreenSize) %, impixelinfo %, hold on
%     % loop for green objects
%     for object = 1:length(statsGreen)
%         bbGreen = statsGreen(object).BoundingBox;
%         cGreen = statsGreen(object).Centroid;
%         areaGreen = statsGreen(object).Area;
%         rectangle('Position',bbGreen,'EdgeColor','r','LineWidth',2)
%         plot(cGreen(1),cGreen(2), '-m+')
%         a=text(cGreen(1)+15,cGreen(2), strcat('X: ', num2str(round(cGreen(1))), '    Y: ', num2str(round(cGreen(2))), '   Area: ', num2str(round(areaGreen))));
%         set(a, 'FontName', 'Arial', 'FontWeight', 'bold', 'FontSize', 12, 'Color', 'yellow');
%     end
% %     hold off 
%      
% %     blue
% %     figure(6),
%     plot(binBlueSize) %, impixelinfo %, hold on
%     %loop for blue objects
%     for object = 1:length(statsBlue)
%         bbBlue = statsBlue(object).BoundingBox;
%         cBlue = statsBlue(object).Centroid;
%         areaBlue = statsBlue(object).Area;
%         rectangle('Position',bbBlue,'EdgeColor','r','LineWidth',2)
%         plot(cBlue(1),cBlue(2), '-m+')
%         a=text(cBlue(1)+15,cBlue(2), strcat('X: ', num2str(round(cBlue(1))), '    Y: ', num2str(round(cBlue(2))), '   Area: ', num2str(round(areaBlue))));
%         set(a, 'FontName', 'Arial', 'FontWeight', 'bold', 'FontSize', 12, 'Color', 'yellow');
%     end
%     F = getframe;
%     writeVideo(writerObj,F);
%     hold off
%     pause(0.05)

  %%
  
end
close(writerObj);
% close(writerObj_bin);