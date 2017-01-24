clear all; close all;
load('input_ekf_ausschwing02.mat');
%% Konstanten
g = 9.81;
l_1 = 0.194;
l_2 = 0.1855;   
m_1 = 0.0313; 
m_2 = 0.0313; 
m_3 = 0.0308; 
d_p1= 5.3239e-4;
d_p2= 5.3239e-4;
T_s = 0.001;
Fs = 1/T_s;
dt = T_s;
d2r = pi/180;
r2d = 180/pi;
x_0=0; dx_0=0; phi1_0=90*d2r; dphi1_0=0; phi2_0=180*d2r; dphi2_0=0;
x0 = [phi1_0; dphi1_0; phi2_0; dphi2_0];
x0_ekf = [210*d2r; 1; 150*d2r; -3];
phi1MeasRad = d2r*phi1MeasDeg;
phi1VideoRad = d2r*phi1VideoDeg;
para_sys = [g l_1 l_2 m_1 m_2 m_3 d_p1 d_p2];

%% EKF Parameter
Pk_0 = eye(4);
Rk = 0.01;
% Qk_min = 0.001*diag([0.0001 1 0.1 10]); % aus Simulation
% Qk = Qk_min;
Qk = eye(4);
%% calculating phi2 with loops for Qk weightings
q = logspace(-7,-2,6);
errMin = Inf;

% for j = 1:length(q)
%     for jj = 1:length(q)
%         for jjj = 1:length(q)
%             for jjjj = 1:length(q)
%                 Qk = diag([q(j) q(jj) q(jjj) q(jjjj)]);
                
                Qk = QkMin;
                phi1EstRad = zeros(1,length(phi1MeasRad)); 
                dphi1EstRad = zeros(1,length(phi1MeasRad));
                phi2EstRad = zeros(1,length(phi1MeasRad)); 
                dphi2EstRad = zeros(1,length(phi1MeasRad)); 
                K = zeros(4,1);
                init = 0; % variable to make the loop work
                for k = 1:length(phi1MeasRad)
                    [states, K] = extended_kalman_filter(Pk_0, Qk, Rk, x0, para_sys, T_s, ddxDes(k), phi1MeasRad(k), init);
                    init = 1;
                    phi1EstRad(k) = states(1);
                    dphi1EstRad(k) = states(2);
                    phi2EstRad(k) = states(3);
                    dphi2EstRad(k) = states(4);
                end
                
                phi1EstDeg = zeros(1,length(phi1EstRad)); dphi1EstDeg = zeros(1,length(phi1EstRad)); phi2EstDeg = zeros(1,length(phi1EstRad)); dphi2EstDeg = zeros(1,length(phi1EstRad)); 
                phi1EstDeg = r2d*phi1EstRad;
                dphi1EstDeg = r2d*dphi1EstRad;
                phi2EstDeg = r2d*phi2EstRad;
                dphi2EstDeg = r2d*dphi2EstRad;
                % Fehler zwischen Messung und EKF
                err = sqrt(sum((phi2EstDeg-phi2VideoDeg).^2));
%                 if (err <= errMin)
%                     errMin = err;
%                     QkMin = Qk;
%                 end
%             end
%         end
%     end
% end
%% differentiating and filtering phi2Video
dphi2VideoDeg = diff(phi2VideoDeg)/dt;  % diff 
dphi2VideoDegMag = abs(fft(dphi2VideoDeg));

nfft = length(dphi2VideoDegMag);

figure(2)
plot([0:1/(nfft/2 -1):1], dphi2VideoDegMag(1:nfft/2)), title('dphi2 Frequenzbereich')

[blow, alow] = butter(2, 0.04, 'low');
[bbp, abp] = butter(4, [0.4 0.6], 'bandpass'); 

Hlow = freqz(blow,alow, floor(nfft/2));
Hbp = freqz(bbp, abp, floor(nfft/2));
figure(3),
plot([0:1/(nfft/2 -1):1], abs(Hlow),'r'), title('Filter Übertragungsfunktion'), hold on
plot([0:1/(nfft/2 -1):1], abs(Hbp),'b'), legend('lowpass', 'bandpass')

dphi2VideoDegFiltLP = filter(blow,alow,dphi2VideoDeg);
dphi2VideoDegFiltLP = [0  dphi2VideoDegFiltLP ];
dphi2VideoDegFiltBP = filter(bbp,abp,dphi2VideoDeg);
dphi2VideoDegFiltBP = [0  dphi2VideoDegFiltBP ];

figure(1),
plot(dphi2VideoDeg), title('dphi2 ungefiltert vs gefiltert'), hold on
plot(dphi2VideoDegFiltLP), 
% plot(dphi2VideoDegFiltBP),legend('ungefiltert', 'gefiltert tiefpass','gefiltert bandpass')

%% plots of states and measurements
figure(4),
subplot(2,1,1),
plot(tVideo, phi1EstDeg),hold on
plot(tVideo, phi1MeasDeg),legend('phi1\_est', 'phi1\_Meas')
xlabel('t in Sek.')
ylabel('Grad')
title('Zustände: Winkel')
hold off

subplot(2,1,2),
plot(tVideo, phi2EstDeg),hold on
plot(tVideo, phi2VideoDeg), legend('phi2\_est', 'phi2\_video')
xlabel('t in Sek.')
ylabel('Grad')
hold off

figure(5),
subplot(2,1,1),
plot(tVideo,dphi1EstDeg),hold on
plot(tVideo,dphi1MeasDeg),legend('dphi1\_est', 'dphi1\_Meas')
xlabel('t in Sek.')
ylabel('Grad/s')
title('Zustände: Winkelgeschwindigkeiten')
hold off

phi2VideoDegFunc = spline(tVideo, phi2VideoDeg);
dphi2VideoDegFunc = fnder(phi2VideoDegFunc);
dphi2VideoDeg = diff(phi2VideoDeg)*1000;
dphi2VideoDeg(end+1) = dphi2VideoDeg(end);
subplot(2,1,2),
plot(tVideo,dphi2EstDeg),hold on
% fnplt(dphi2VideoDegFunc)
plot(tVideo,dphi2VideoDegFiltLP), legend('dphi2\_est', 'dphi2\_video')
xlabel('t in Sek.')
ylabel('Grad/s')
hold off

%% 
% dphi2VideoFFT = fft(dphi2VideoDeg);
% nfft = length(dphi2VideoFFT);
% dphi2VideoFFTMag = abs(dphi2VideoFFT);
% dphi2VideoFFTMag = dphi2VideoFFTMag(1:nfft/2);
% f = (0:nfft/2-1)*(1/T_s)/nfft;
% 
% figure(3)
% % plot(f,dphi2VideoFFTMag)
% % plot(dphi2VideoFFTMag)