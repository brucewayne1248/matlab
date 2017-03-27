clear all; close all;
load('input_ekf_2.5_v2.mat');

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
d2r = pi/180;
r2d = 180/pi;
x_0=0; dx_0=0; phi1_0=180*d2r; dphi1_0=0; phi2_0=180*d2r; dphi2_0=0;
x0 = [phi1_0; dphi1_0; phi2_0; dphi2_0];
x0_ekf = [210*d2r; 1; 150*d2r; -3];
phi1MeasRad = d2r*phi1MeasDeg;
para_sys = [g l_1 l_2 m_1 m_2 m_3 d_p1 d_p2];

%% EKF Parameter
Pk_0 = eye(4);
Rk = 0.01;
% Qk_min = 0.01*diag([0.0001 1 0.1 10]); % aus Simulation
Qk =  1e-6*eye(4);
% Qk = diag([1e-9 1e-7 1e-5 1e-8]); % optimales Q für phi2
Qk = diag([1e-5 0.01 1e-3 0.1]);
QkMin = Qk;
% Qk = diag([1e-6 0.1 1e-3 1e-6]);

%% differentiating and filtering phi2Video
Fs = 1/T_s;
dt = T_s;
phi2VideoRad = unwrap(phi2VideoDeg*d2r);
phi2VideoDeg = r2d*phi2VideoRad;
dphi2VideoDeg = diff(phi2VideoDeg)/dt;  % diff 
dphi2VideoDegMag = abs(fft(dphi2VideoDeg)); % magnitude
nfft = length(dphi2VideoDegMag);

dphi1MeasDeg2 = diff(phi1MeasDeg)/dt;
dphi1MeasDeg2Mag = abs(fft(dphi1MeasDeg2));

figure(6),
plot([0:1/(nfft/2 -1):1], dphi1MeasDeg2Mag(1:nfft/2)), title('dphi1 Frequenzbereich')

figure(2)
plot([0:1/(nfft/2 -1):1], dphi2VideoDegMag(1:nfft/2)), title('dphi2 Frequenzbereich')

[b, a] = butter(2, 0.02, 'low'); % Tiefpassfilter
% [b,a] = butter(2, [0.4 0.6],'bandpass');

H = freqz(b,a, floor(nfft/2));
figure(3),
plot([0:1/(nfft/2 -1):1], abs(H),'r'), title('Filter Übertragungsfunktion')

dphi1MeasDeg2FiltLP = filtfilt(b,a,dphi1MeasDeg2); 
dphi1MeasDeg2FiltLP = [0 dphi1MeasDeg2FiltLP'];
dphi2VideoDegFiltLP = filtfilt(b,a,dphi2VideoDeg);
dphi2VideoDegFiltLP = [0  dphi2VideoDegFiltLP ];

figure(1),
plot(dphi2VideoDeg), title('dphi2 gefiltert vs ungefiltert'), hold on,
plot(dphi2VideoDegFiltLP), legend('ungefiltert', 'gefiltert')

%% calculating phi2 with loops for Qk weightings
q = logspace(-5,-1,5);
errMin = Inf;
phi1VideoRad = d2r * phi1VideoDeg;
% for j = 1:length(q)
%     for jj = 1:length(q)
%         for jjj = 1:length(q)
%             for jjjj = 1:length(q)
%                 Qk = diag([q(j) q(jj) q(jjj) q(jjjj)]);
                phi1EstRad = zeros(1,length(phi1MeasRad)); 
                dphi1EstRad = zeros(1,length(phi1MeasRad)); 
                phi2EstRad = zeros(1,length(phi1MeasRad)); 
                dphi2EstRad = zeros(1,length(phi1MeasRad)); K = [];
                init = 1;
                for k = 1:length(phi1MeasRad)   % calculating states
                    [states, K] = extended_kalman_filter(Pk_0, Qk, Rk, x0, para_sys, T_s, ddxDes(k), phi1VideoRad(k), init);
                    init = 0;
                    phi1EstRad(k) = states(1);
                    dphi1EstRad(k) = states(2);
                    phi2EstRad(k) = states(3);
                    dphi2EstRad(k) = states(4);
                end
                
                phi1EstDeg = zeros(1,length(phi1MeasRad)); 
                dphi1EstDeg = zeros(1,length(phi1MeasRad));
                phi2EstDeg = zeros(1,length(phi1MeasRad));
                dphi2EstDeg = zeros(1,length(phi1MeasRad)); 
                phi1EstDeg = r2d*phi1EstRad;
                dphi1EstDeg = r2d*dphi1EstRad;
                phi2EstDeg = r2d*phi2EstRad;
                dphi2EstDeg = r2d*dphi2EstRad;
                
                % Fehler zwischen Messung und EKF
                err = sqrt(sum((phi2EstDeg(1:9.5e3)-phi2VideoDeg(1:9.5e3)).^2));
%                 if (err < errMin)
%                     errMin = err;
%                     QkMin = Qk;
%                 end
%                 
%             end
%         end
%     end
% end

%% plots of states and measurements
figure(4)
subplot(2,1,1),
plot(tMeas, phi1EstDeg),ylabel('Gelenkwinkel [Grad]'), xlabel('Zeit [s]'), title('Gelenkwinkel ab ca. 10 Sek. chaotisches Verhalten des äußeren Pendels'), hold on
plot(tMeas, phi1VideoDeg), ylabel('Gelenkwinkel [Grad]'), xlabel('Zeit [s]')
%plot(tMeas, phi1MeasDeg),ylabel('Gelenkwinkel [Grad]'), xlabel('Zeit [s]'),
legend('phi1\_est', 'phi1_video')
hold off

subplot(2,1,2),
plot(tMeas, phi2EstDeg),ylabel('Gelenkwinkel [Grad]'), xlabel('Zeit [s]'), hold on
plot(tMeas, phi2VideoDeg),ylabel('Gelenkwinkel [Grad]'), xlabel('Zeit [s]'), legend('phi2\_est', 'phi2\_ video')
hold off

figure(5), 
subplot(2,1,1),
plot(tMeas,dphi1EstDeg),ylabel('Gelenkwinkelgeschw. [Grad/s]'), xlabel('Zeit [s]'), title('Gelenkwinkelgeschw. ab ca. 10 Sek. chaotisches Verhalten des äußeren Pendels'), hold on
plot(tMeas,dphi1MeasDeg2FiltLP), 
%plot(tMeas,dphi1MeasDeg)
legend('dphi1\_est','dphi1\_filtfilt')
hold off

phi2VideoDegFunc = spline(tMeas, phi2VideoDeg);
dphi2VideoDegFunc = fnder(phi2VideoDegFunc);
dphi2VideoDeg = diff(phi2VideoDeg)*1000;
dphi2VideoDeg(end+1) = dphi2VideoDeg(end);
subplot(2,1,2),
plot(tMeas,dphi2EstDeg),hold on,ylabel('Gelenkwinkelgeschw. [Grad/s]'), xlabel('Zeit [s]'),
% fnplt(dphi2VideoDegFunc)
plot(tMeas,dphi2VideoDegFiltLP), legend('dphi2\_est', 'dphi2\_video')
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