clear all, close all
load('ausschwing_0901_alu.mat')
load('video_angles_ausschwing02.mat')

%%
T_s = 1e-3;
t1 = 104.2; t2 = 134;
Daten = Daten(t1/T_s:t2/T_s,:);
d2r = pi/180; r2d = 1/d2r;
tMeas = (0:length(Daten(:,1))-1) * T_s;
tVideo = (0:length(phi1VideoDeg)-1) * 1/frameRate;

%%
phi1MeasDeg = Daten(:,1)';
dphi1MeasDeg = Daten(:,2)';
ddphi1MeasDeg = Daten(:,3)';
xMeasReal = Daten(:,4)';
dxDes = Daten(:,5)';
ddxDes = Daten(:,6)';

% figure(1)
% subplot(2,1,1)
% plot(tMeas, phi1MeasDeg)
% title('Messung')
% 
% subplot(2,1,2)
% plot(tVideo, phi1VideoDeg)
% title('Video')

phi2VideoDeg = r2d*unwrap(d2r*phi2VideoDeg);

%% resampling and cross-correlate
[P,Q] = rat((1/T_s)/frameRate);     
phi1Resample = resample(phi1VideoDeg,P,Q);    % resample the slower measurement
phi1Resample = phi1Resample(30:end-30);
phi2Resample = resample(phi2VideoDeg,P,Q);    % resample the slower measurement
phi2Resample = phi2Resample(30:end-30);
[C, lag] = xcorr(phi1Resample,phi1MeasDeg);
[~,I] = max(C);
lagDiff = lag(I);
timeDiff = lagDiff*T_s;
lagDiffManual= 350;
% timeDiffManual = lagDiffManual*T_s;
figure(4),
plot(lag,C)

figure(2)
subplot(2,1,1)
plot(tMeas, phi1MeasDeg)
title('Messung')

subplot(2,1,2)
plot(tVideo, phi1VideoDeg)
title('Video')

%%
phi1VideoDeg = phi1Resample(lagDiffManual+1:end);
phi2VideoDeg = phi2Resample(lagDiffManual+1:end);
phi1MeasDeg = phi1MeasDeg(1:length(phi1VideoDeg));
dphi1MeasDeg = dphi1MeasDeg(1:length(phi1VideoDeg));
ddphi1MeasDeg = ddphi1MeasDeg(1:length(phi1VideoDeg));
xMeasReal = xMeasReal(1:length(phi1VideoDeg));
dxDes = dxDes(1:length(phi1VideoDeg));
ddxDes = ddxDes(1:length(phi1VideoDeg));

tVideo = (0:length(phi1VideoDeg)-1)*T_s;
% corrCoef = corrcoef(phi1MeasDeg,phi1VideoDeg);
% corrCoef = corrCoef(1,2);

figure(3)
plot(tVideo,phi1MeasDeg,'r'), hold on
title('Messung und Video')
plot(tVideo, phi1VideoDeg,'b'), legend('Messung','Video')
% a = text(0.1,130,strcat('Korrelationskoeffizient: ', num2str(corrCoef)));
% set(a, 'FontName', 'Arial', 'FontWeight', 'bold', 'FontSize', 8, 'Color', 'black');
xlabel('t in Sek.'), ylabel('Winkel in Grad');

%%
save('input_ekf_ausschwing02.mat','tMeas','tVideo','phi1MeasDeg','dphi1MeasDeg','ddphi1MeasDeg','phi1VideoDeg','phi2VideoDeg','xMeasReal','dxDes','ddxDes')