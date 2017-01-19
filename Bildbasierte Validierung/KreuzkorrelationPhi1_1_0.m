clear all, close all
load('harm_erregung1.0_alu_05.01.mat')
load('video_angles_1.0_alu_05.01.mat')
%%
T_s = 1e-3;
startIndex = find(Daten(:,6),1);
seconds = 14;
Daten = Daten(startIndex:startIndex+seconds*10^3,:); 

tMeas = [];
for k = 1:length(Daten(:,1))
    tMeas(k) = (k-1)*T_s;
end
tVideo = [];
for k = 1:length(phi1)
    tVideo(k) = (k-1)*(1/frameRate);
end

phi1MeasDeg = Daten(:,1);
dphi1MeasDeg = Daten(:,2);
ddphi1MeasDeg = Daten(:,3);
xMeasReal = Daten(:,4);
dxDes = Daten(:,5);
ddxDes = Daten(:,6);

figure(1)
subplot(2,1,1)
plot(tMeas, phi1MeasDeg)
title('Messung')

% Video phi1
subplot(2,1,2)
plot(tVideo, phi1)
title('Video')
%% resampling and cross-correlate
[P,Q] = rat((1/T_s)/frameRate);     
phi1Resample = resample(phi1,P,Q);    % resample the slower measurement
phi1Resample = phi1Resample(1:17e3);
[C, lag] = xcorr(phi1Resample,phi1MeasDeg);
[~,I] = max(C);
lagDiff = lag(I);
timeDiff = lagDiff*T_s;
lagDiffManual= 2930;
timeDiffManual = lagDiffManual*T_s;

figure(1)
plot(lag,C)

figure(2)
subplot(2,1,1)
plot(tMeas, phi1MeasDeg)
title('Messung')

subplot(2,1,2)
plot(tVideo, phi1)
title('Video')

%%
phi1VideoDeg = phi1Resample(lagDiffManual:lagDiffManual+seconds*10^3);
phi2VideoDeg = phi2Resample(lagDiffManual:lagDiffManual+seconds*10^3);
tVideoAlign = (0:length(phi1VideoDeg)-1)*T_s;

corrCoef = corrcoef(phi1MeasDeg,phi1VideoDeg);
corrCoef = corrCoef(1,2);

figure(3)
plot(tMeas,phi1MeasDeg,'r'), hold on
title('Messung und Video')
plot(tVideoAlign, phi1VideoDeg,'b'), legend('Messung','Video')
a = text(0.1,110,strcat('Korrelationskoeffizient: ', num2str(corrCoef)));
set(a, 'FontName', 'Arial', 'FontWeight', 'bold', 'FontSize', 8, 'Color', 'black');
xlabel('t in Sek.'), ylabel('Winkel in Grad');

%%
% save('input_ekf_1.0.mat','tMeas','phi1Meas','xMeas','ddxMeas')