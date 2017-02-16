clear all; close all;
load('input_ekf_2.5_trapez.mat');
xMeasReal = xMeasReal';
%% herleitung ddx aus xMeasReal
dt = 1e-3;
dxMeas = diff(xMeasReal)/dt;
dxMeasMag = abs(fft(dxMeas));
nfft = length(dxMeasMag);

figure(7),
plot(xMeasReal)

figure(1),
plot([0:1/(nfft/2 - 1):1], dxMeasMag(1:nfft/2)), title('dx ungefiltert Frequenzbereich')

[b, a] = butter(4, 0.005, 'low'); % Tiefpassfilter

H = freqz(b,a, floor(nfft/2));
figure(2),
plot([0:1/(nfft/2 -1):1], abs(H),'r'), title('Filter ‹bertragungsfunktion')

dxMeasFilt = filtfilt(b,a,dxMeas);
dxMeasFilt = [0 dxMeasFilt];

figure(3),
plot(dxMeas), hold on
plot(dxMeasFilt), title('geschwindigkeit'),legend('ungefiltert', 'gefiltert'), hold off


ddxMeas = diff(dxMeas)/dt;
ddxMeasMag = abs(fft(ddxMeas));

figure(4), 
plot([0:1/(nfft/2 - 1):1], ddxMeasMag(1:nfft/2)), title('ddx ungefiltert Frequenzbereich')

ddxMeasFilt = filtfilt(b,a,ddxMeas);
ddxMeasFilt = [0 ddxMeasFilt];

figure(5), title('Gelenkwinkelgeschw. ab ca. 10 Sek. chaotisches Verhalten des ‰uﬂeren Pendels')
plot(ddxMeas), hold on
plot(ddxMeasFilt), legend('ungefiltert', 'gefiltert'), hold off

figure(6)
plot(ddxDes), hold on
plot(ddxMeasFilt), legend('desired', 'gefiltert')