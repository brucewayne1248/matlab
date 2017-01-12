clear all; close all;
load('input_ekf_1.5.mat');
%% Konstanten
g = 9.81;
l_1 = 0.194;    
l_2 = 0.1855;   
m_w = 0.8101;
m_1 = 0.0313; 
m_2 = 0.0313; 
m_3 = 0.0308; 
d_p1 = 0.001;   % d_p1= 5.3239e-4;
d_p2 = 0.001;   % d_p2= 5.3239e-4;
T_s = 0.001;
d2r = pi/180;
r2d = 180/pi;
x_0=0; dx_0=0; phi1_0=180*d2r; dphi1_0=0; phi2_0=180*d2r; dphi2_0=0;
x0 = [phi1_0; dphi1_0; phi2_0; dphi2_0];
x0_ekf = [210*d2r; 1; 150*d2r; -3];%x0;

para_sys = [g l_1 l_2 m_1 m_2 m_3 d_p1 d_p2];

%% EKF Parameter
Pk_0 = eye(4);
Rk = 0.001;
Qk_min = 0.001*diag([0.0001 1 0.1 10]);
Qk = Qk_min;
Qk = eye(4);
%% calculating phi2 
phi1Meas = d2r*phi1Meas;
x_est = [];
phi1_est = [];
phi2_est = [];

K_kalman = [];
for k = 1:length(phi1Meas)
[states, K] = extended_kalman_filter(Pk_0, Qk, Rk, x0, para_sys, T_s, ddxMeas(k), phi1Meas(k));
phi1_est(k) = states(1);
phi2_est(k) = states(3);
end
%%
phi1_est = r2d*phi1_est;
phi2_est = r2d*phi2_est;
figure(1),
plot(phi2_est),hold on
plot(phi2VideoAlign)
hold off

phi1Meas = r2d*phi1Meas;
figure(2),
plot(phi1_est),hold on
plot(phi1Meas)
hold off


