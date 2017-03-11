clear all; close all;
%% Reading video
v = VideoReader('D:\Documents\Studienarbeit imes\Aufnahmen\trapez_erregung5_1002.MP4');
frameRate = v.FrameRate;
%counter
% v.CurrentTime = 4;
k = 0;

while hasFrame(v)
    % while (v.CurrentTime <= 2)
    k = k+1;
    % save each frame in image
    image = readFrame(v);
    
    % filter{Reg,Green,Blue} Funktion segmentiert das Bild entsprechend der
    % Farbintensität [0...1] und liefert schwarzweiß Bild, Werte zw.
    % 0.05-0.15 hilfreich
    
    binRed = filterRed(image, 0.07);
    binGreen = filterGreen(image, 0.065);
    binBlue = filterBlue(image, 0.1);
     
    % manuelPreFilter setzt alle werte im gegebenen Pixelbereich auf 0
    % eines Binärbildes. Reihenfolge Werte: ymin, ymax, xmin, xmax
    binRed = manualPreFilter(binRed, 639, 720, 954, 1175);
%     binGreen = manualPreFilter(binGreen, 1, 720, 670, 1280);
    binBlue = manualPreFilter(binBlue, 537, 720, 970, 1280);
    
    % Entfernen von allen Farbblobs, die weniger als x Pixel haben
    binRed = bwareaopen(binRed, 100);
    binGreen = bwareaopen(binGreen, 30);
    binBlue = bwareaopen(binBlue, 200);
    
    % montage des Binär- und Farbbildes zum Finden der richtigen Paramter
    % und debuggen
    %     figure(1), imshowpair(binRed, image, 'montage'), impixelinfo
    %     figure(2), imshowpair(binGreen, image, 'montage'), impixelinfo
    %     figure(3), imshowpair(binBlue, image, 'montage'), impixelinfo
    
    % Entfernen von Farbblobs mit weniger als min und mehr als max Pixel
    %     min = 200; max = 500;
    %     binRedSize = xor(bwareaopen(binRed,min), bwareaopen(binRed, max));
    
    
    % image blob Analyse
    % Über regionprops, die benötigten blob-Eigenschaften ermitteln
    % (für jeden erkannten blob)
    statsRed = regionprops(binRed, 'Area', 'BoundingBox', 'Centroid');
    statsGreen = regionprops(binGreen, 'Area', 'BoundingBox', 'Centroid');
    statsBlue = regionprops(binBlue, 'Area', 'BoundingBox', 'Centroid');
    
    %% Winkelberechnung über Funktion winkel, die den Winkel vom "inneren" zum "äußeren" Pendelende berechnet benötigt
    
    try
        if ( isempty(statsGreen) )
            centroidGreen = cGreen;
            phi1VideoDeg(k) = winkel(centroidGreen, statsBlue.Centroid);
        else
            phi1VideoDeg(k) = winkel(statsGreen.Centroid, statsBlue.Centroid);
        end
    catch ME
        phi1VideoDeg(k) = phi1VideoDeg(k-1);
    end
    
    try
        phi2VideoDeg(k) = winkel(statsBlue.Centroid, statsRed.Centroid);
    catch ME
        phi2VideoDeg(k) = phi2VideoDeg(k-1);
    end
    
    %% debugging: zeigt binär bild
    
    binTotal = binRed + binGreen + binBlue;
    
    %     red
    figure(4), imshow(binTotal), hold on%, impixelinfo, hold on
    for object = 1:length(statsRed)
        bbRed = statsRed(object).BoundingBox;
        cRed = statsRed(object).Centroid;
        areaRed = statsRed(object).Area;
        rectangle('Position',bbRed,'EdgeColor','r','LineWidth',2)
        plot(cRed(1),cRed(2), '-m+')
        a=text(cRed(1)+20,cRed(2), strcat('rot: u_s: ', num2str(round(100*cRed(1))/100), '    v_s: ', num2str(round(100*cRed(2))/100)));
        set(a, 'FontName', 'Arial', 'FontWeight', 'bold', 'Fontsize', 30, 'Color', 'yellow');
        b=text(80,40, strcat('phi_1: ', num2str(round2(phi1VideoDeg(k),2)), '  phi_2: ', num2str(round2(phi2VideoDeg(k),2))));
        set(b, 'FontName', 'Arial', 'FontWeight', 'bold', 'Fontsize', 30, 'Color', 'yellow');
    end
    %     green
    plot(binGreen)
    for object = 1:length(statsGreen)
        bbGreen = statsGreen(object).BoundingBox;
        cGreen = statsGreen(object).Centroid;
        areaGreen = statsGreen(object).Area;
        rectangle('Position',bbGreen,'EdgeColor','r','LineWidth',2)
        plot(cGreen(1),cGreen(2), '-m+')
        a=text(cGreen(1)+20,cGreen(2), strcat('grün: u_s: ', num2str(round(100*cGreen(1))/100), '    v_s: ', num2str(round(100*cGreen(2))/100)));
        set(a, 'FontName', 'Arial', 'FontWeight', 'bold', 'Fontsize', 30, 'Color', 'yellow');
    end
    % %     blue
    plot(binBlue) %, impixelinfo %, hold on
    %loop for blue objects
    for object = 1:length(statsBlue)
        bbBlue = statsBlue(object).BoundingBox;
        cBlue = statsBlue(object).Centroid;
        areaBlue = statsBlue(object).Area;
        rectangle('Position',bbBlue,'EdgeColor','r','LineWidth',2)
        plot(cBlue(1),cBlue(2), '-m+')
        a=text(cBlue(1)+20,cBlue(2), strcat('blau u_s: ', num2str(round(100*cBlue(1))/100), '    v_s: ', num2str(round(100*cBlue(2))/100)));
        set(a, 'FontName', 'Arial', 'FontWeight', 'bold', 'Fontsize', 30, 'Color', 'yellow');
    end
    hold off

    %% Pause wird für das Anzeigen der bilder benötigt. Für winkelberechnung ohne anzeigen von Bildern auskommentieren
    pause(0.05)     
end

%% save the calculated angles
d2r = pi/180;
r2d = 1/d2r;
phi1VideoRad = unwrap(phi1VideoDeg*d2r);
phi2VideoRad = unwrap(phi2VideoDeg*d2r);
phi1VideoDeg = phi1VideoRad * r2d;
phi2VideoDeg = phi2VideoRad * r2d;

% save('video_angles_5_trapez_1002.mat', 'phi1VideoDeg','phi1VideoRad','phi2VideoDeg','phi2VideoRad','frameRate','k');