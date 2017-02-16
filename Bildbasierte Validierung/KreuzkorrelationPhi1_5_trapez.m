clear all, close all
load('trapez_erregung5_1002.mat');
load('video_angles_5_trapez_1002.mat');
%% plot für jour fixe
% figure, 
% subplot(2,1,1), plot(t,Daten(:,1)), xlabel('t in Sek.'), ylabel('Winkel in Grad'), legend('phi 1'), title('Messung mittels Resolver')
% tplot = (0:length(phi1)-1)*1/frameRate;
% subplot(2,1,2), plot(tplot,phi1), xlabel('t in Sek.'), ylabel('Winkel in Grad'), legend('phi 1'), title('Bildbasierte Ermittlung')

%%
T_s = 1e-3;
startIndex = find(Daten(:,7),1);
seconds = 10;
Daten = Daten(startIndex:startIndex+seconds*10^3,:); 

tMeas = (0:length(Daten(:,1))-1)*T_s;
tVideo = (0:length(phi1VideoDeg)-1)*(1/frameRate);

phi1MeasDeg = Daten(:,1);
phi1MeasDeg = (180/pi)*unwrap(phi1MeasDeg*pi/180);
dphi1MeasDeg = Daten(:,2);
ddphi1MeasDeg = Daten(:,3);
xMeasReal = Daten(:,4);
dxDes = Daten(:,5);
ddxDes = Daten(:,7);

figure(1)
plot(tMeas, phi1MeasDeg), hold on
title('Messung')
plot(tVideo, phi1VideoDeg)
title('Video'), legend('messung','video')

%% resamplen des langsameren Kamerasignals und Kreuzkorrelation
[P,Q] = rat((1/T_s)/frameRate);     
phi1Resample = resample(phi1VideoDeg,P,Q);    % resample the slower measurement
phi1Resample = phi1Resample(35:end-35);
phi2Resample = resample(phi2VideoDeg,P,Q);    % resample the slower measurement
phi2Resample = phi2Resample(35:end-35);

[C, lag] = xcorr(phi1Resample,phi1MeasDeg);
[~,I] = max(C);
lagDiff = lag(I);
timeDiff = lagDiff*T_s;

figure(2),
plot(lag,C)
lagDiffManual= 250;
timeDiffManual = lagDiffManual*T_s;

%% 
phi1VideoDeg = phi1Resample(lagDiff:lagDiff+seconds*10^3)+0.75;
phi2VideoDeg = phi2Resample(lagDiff:lagDiff+seconds*10^3)+0.75;
% phi1VideoDeg = phi1Resample(lagDiffManual:lagDiffManual+seconds*10^3)+0.5;
% phi2VideoDeg = phi2Resample(lagDiffManual:lagDiffManual+seconds*10^3)+0.5;
tVideoAlign = (0:length(phi1VideoDeg)-1)*T_s;

corrCoef = corrcoef(phi1MeasDeg,phi1VideoDeg);
corrCoef = corrCoef(1,2);

figure(3)
plot(tMeas,phi1MeasDeg,'r'), hold on
title('Messung und Video')
plot(tVideoAlign, phi1VideoDeg,'b'), legend('Messung','Video')
a = text(0.1,90,strcat('Korrelationskoeffizient: ', num2str(corrCoef)));
set(a, 'FontName', 'Arial', 'FontWeight', 'bold', 'FontSize', 8, 'Color', 'black');
xlabel('t in Sek.'), ylabel('Winkel in Grad');

%%
save('input_ekf_5_trapez.mat','tMeas','phi1MeasDeg','dphi1MeasDeg','ddphi1MeasDeg','phi1VideoDeg','phi2VideoDeg','xMeasReal','dxDes','ddxDes', 'vmax')