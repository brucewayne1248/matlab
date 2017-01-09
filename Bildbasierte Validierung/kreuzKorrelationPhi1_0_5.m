clear all, close all
load('harm_erregung0.5_alu_05.01.mat')
load('video_angles_0.5_alu.mat')

%%
T_s = 1e-3;
startIndex = find(Daten(:,6),1);
seconds = 12;
Daten = Daten(startIndex:startIndex+seconds*10^3,:); 

tMeas = [];
for k = 1:length(Daten(:,1))
    tMeas(k) = (k-1)*T_s;
end
tVideo = [];
for k = 1:length(phi1)
    tVideo(k) = (k-1)*(1/frameRate);
end

phi1Meas = Daten(:,1);
dphi1Meas = Daten(:,2);
ddphi1Meas = Daten(:,3);
xMeas = Daten(:,4);
dxMeas = Daten(:,5);
ddxMeas = Daten(:,6);

figure(1)
subplot(2,1,1)
plot(tMeas, phi1Meas)
title('Messung')

subplot(2,1,2)
plot(tVideo, phi1)
title('Video')

%% resampling and cross-correlate
[P,Q] = rat((1/T_s)/frameRate);     
phi1Resample = resample(phi1,P,Q);    % resample the slower measurement
phi1Resample = phi1Resample(30:13.035e3);
[C, lag] = xcorr(phi1Resample,phi1Meas);
[~,I] = max(C);
lagDiff = lag(I);
timeDiff = lagDiff*T_s;
lagDiffManual= -10;
timeDiffManual = lagDiffManual*T_s;

figure(2)
plot(lag,C)



%%
phi1VideoAlign = phi1Resample(-lagDiffManual:-lagDiffManual+seconds*10^3);
tVideoAlign = (0:length(phi1VideoAlign)-1)*T_s;
corrCoef = corrcoef(phi1Meas,phi1VideoAlign);
corrCoef = corrCoef(1,2);

figure(3)
plot(tMeas,phi1Meas,'r'), hold on
title('Messung und Video')
plot(tVideoAlign, phi1VideoAlign,'b'), legend('Messung','Video')
a = text(0.1,130,strcat('Korrelationskoeffizient: ', num2str(corrCoef)));
set(a, 'FontName', 'Arial', 'FontWeight', 'bold', 'FontSize', 8, 'Color', 'black');
xlabel('t in Sek.'), ylabel('Winkel in Grad');

