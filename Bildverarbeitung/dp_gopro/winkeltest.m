%% skript zum testen der winkelberechnung
r2d = 180/pi;
% 1. Quadrant
x1 = 100; y1 = 300; x2 = 200; y2 = 100;
c11 = [x1 y1]; c12 = [x2 y2];
y = y2-y1; x = x2-x1;
alpha1 = atan2(y,x)*r2d
phi1 = 270 + alpha1
phi1_test = winkel(c11,c12)

%% 2. Quadrant
x1 = 100; y1 = 300; x2 = 200; y2 = 100;
c21 = [x1 y1]; c22 = [x2 y2];
y = y2-y1; x = x2-x1;
alpha2 = atan2(y,x)*r2d
phi2 = 270 + alpha2
phi2_test = winkel(c21,c22)
%% 3. Quadrant
x1 = 200; y1 = 300; x2 = 100; y2 = 100;
c31 = [x1 y1]; c32 = [x2 y2];
y = y2-y1; x = x2-x1;
alpha3 = atan2(y,x)*r2d
phi3 = 270 + alpha3
phi3_test = winkel(c31,c32)
%% 4. Quadrant
x1 = 200; y1 = 100; x2 = 100; y2 = 300;
c41 = [x1 y1]; c42 = [x2 y2];
y = y2-y1; x = x2-x1;
alpha4 = atan2(y,x)*r2d
phi4 = alpha4 -90
phi4_test = winkel(c41,c42)
