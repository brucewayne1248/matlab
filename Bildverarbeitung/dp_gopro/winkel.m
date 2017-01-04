function [ phi ] = winkel( c1, c2 )
%WINKEL_BERECHNUNG Calculates the angle from centroid 1 to centroid 2 
%   Der Winkel wird von der y-Achse aus in positiver Zählrichtung berechnet
%   von 0 bis 360 Grad

x1 = c1(1);
y1 = -c1(2);
x2 = c2(1);
y2 = -c2(2);

x = x2-x1;
y = y2-y1;
r2d = 180/pi;
alpha = atan2(y,x)*r2d;

if y <= 0 && x <= 0
    phi = alpha - 90;
else
    phi = alpha - 90;
end

if phi <0
    phi = 360 + phi;
end

end

