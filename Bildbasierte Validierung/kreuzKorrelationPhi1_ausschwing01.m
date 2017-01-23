clear all, close all
load('ausschwing_0901_alu.mat')
load('video_angles_ausschwing01.mat')

%%
T_s = 1e-3;
t1 = 49; t2 = 71;
Daten = Daten(t1/T_s:t2/T_s,:);

tMeas = (0:length(Daten(:,1))-1) * T_s;
tVideo = (0:length(phi1VideoDeg)-1) * 1/frameRate;

%%
phi1MeasDeg = Daten(:,1);
dphi1MeasDeg = Daten(:,2);
ddphi1MeasDeg = Daten(:,3);
xMeasReal = Daten(:,4);
dxMeasDes = Daten(:,5);
ddxMeasDes = Daten(:,6);

figure(1)
subplot(2,1,1)
plot(tMeas, phi1MeasDeg)
title('Messung')

subplot(2,1,2)
plot(tVideo, phi1VideoDeg)
title('Video')

%% resampling and cross-correlate
[P,Q] = rat((1/T_s)/frameRate);     
phi1Resample = resample(phi1,P,Q);    % resample the slower measurement
phi1Resample = phi1Resample(30:13.035e3);
phi2Resample = resample(phi1,P,Q);    % resample the slower measurement
phi2Resample = phi2Resample(30:13.035e3);
[C, lag] = xcorr(phi1Resample,phi1Meas);
[~,I] = max(C);
lagDiff = lag(I);
timeDiff = lagDiff*T_s;
lagDiffManual= -10;
timeDiffManual = lagDiffManual*T_s;

figure(2)
subplot(2,1,1)
plot(tMeas, phi1MeasDeg)
title('Messung')

subplot(2,1,2)
plot(tVideo, phi1)
title('Video')

%%
phi1VideoDeg = phi1Resample(-lagDiffManual:-lagDiffManual+seconds*10^3);
phi2VideoDeg = phi2Resample(-lagDiffManual:-lagDiffManual+seconds*10^3);
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

%%
save('input_ekf_0.5_v2.mat','tMeas','phi1MeasDeg','dphi1MeasDeg','ddphi1MeasDeg','ddphi1MeasDeg','phi1VideoDeg','phi2VideoDeg','xMeasReal','dxDes','ddxDes')