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
noise_power = 0.5*0.000000003;
x_0=0; dx_0=0; phi1_0=180*d2r; dphi1_0=0; phi2_0=180*d2r; dphi2_0=0; ddx_0 = 0;
x0 = [phi1_0; dphi1_0; phi2_0; dphi2_0];
x0_ekf = [0*d2r; 10; 300*d2r; -10];
% Anregungsparameter Wagen
A = 5;
f = 2*pi;
phase = 0;
%% EKF
Pk_0 = eye(4);
Rk = 1;
Qk_min = diag([0.0001 1 0.1 10]);
%% Optimierung für Q11 = Q22; Q33 = Q44
% pot_min = -5; pot_max = 3; steps = pot_max - pot_min + 1;
% q12 = logspace(pot_min,pot_max,steps); q34 = q12;
% Qk = zeros(4,4,steps,steps);
% for k = 1:length(q12)
%     for kk = 1:length(q12);
%         Qk(1,1,k,kk) = q12(k); Qk(2,2,k,kk) = q12(k);
%         Qk(3,3,k,kk) = q34(kk); Qk(4,4,k,kk) = q34(kk);
%     end
% end
%% Optimierung für alle Diagonalelemente von Q 
% pot_min = -4; pot_max = 1; steps = pot_max - pot_min + 1;
% qii = logspace(pot_min,pot_max,steps);
% Qk = zeros(4,4,steps,steps,steps,steps);
% for k = 1:length(qii)
%     for kk = 1:length(qii);
%         for kkk = 1:length(qii);
%             for kkkk = 1:length(qii);
%                 Qk(1,1,k,kk,kkk,kkkk) = qii(k); 
%                 Qk(2,2,k,kk,kkk,kkkk) = qii(kk); 
%                 Qk(3,3,k,kk,kkk,kkkk) = qii(kkk); 
%                 Qk(4,4,k,kk,kkk,kkkk) = qii(kkkk); 
%             end
%         end
%     end
% end
%% Find optimal weights for Qk and Rk
open_system('dp_EKF_anregung');
paramNameValStruct.SimulationMode = 'normal';
paramNameValStruct.AbsTol         = '1e-5';
paramNameValStruct.SaveState      = 'on';
paramNameValStruct.StateSaveName  = 'xout';
paramNameValStruct.SaveOutput     = 'on';
paramNameValStruct.OutputSaveName = 'yout';
paramNameValStruct.SaveFormat = 'Dataset';
%% Qii variable 
% for i = 1:length(qii)
%     for ii = 1:length(qii)
%         for iii = 1:length(qii)
%             for iiii = 1:length(qii)
%                 set_param('dp_EKF_anregung/EKF/Qk', 'Gain', 'Qk(:,:,i,ii,iii,iiii)');
%                 simOut = sim('dp_EKF_anregung',paramNameValStruct);
%                 outputs = simOut.get('yout');
%                 phi2_time = (outputs.get('phi2').Values);
%                 phi2 = phi2_time.Data;
%                 phi2_est_time = (outputs.get('phi2_est').Values);
%                 phi2_est = phi2_est_time.Data;
%                 dphi2_time = (outputs.get('dphi2').Values);
%                 dphi2 = phi2_time.Data;
%                 dphi2_est_time = (outputs.get('dphi2_est').Values);
%                 dphi2_est = dphi2_est_time.Data;
%                 % criterion for choosing best fit
%                 diff = sum(sqrt((phi2-phi2_etst).^2)) + sum(sqrt((dphi2-dphi2_est).^2));   %sse(A-B) % sum((A-B).^2), norm(A-B) % sqrt(sse(A-B))
%                 %updating variables to best fit
%                 if (diff<diff_min)
%                     diff_min = diff;
%                     Qk_min = Qk(:,:,i,ii,iii,iiii);
%                     i_min = i; ii_min = ii; iii_min = iii; iiii_min = iiii;
%                 end
%             end
%         end
%     end
% end
%% 
set_param('dp_EKF_anregung/EKF/Qk', 'Gain', 'Qk_min');
simOut = sim('dp_EKF_anregung',paramNameValStruct);
outputs = simOut.get('yout');
data = (outputs.get('data').Values);
t = data.Time;
values = data.Data;


%% Set params according to best fit and plot phi2 
% set_param('dp_EKF_anregung/EKF/Qk', 'Gain', 'Qk(:,:,i_min,ii_min)');
% set_param('dp_EKF_anregung/EKF/Qk', 'Gain', 'Qk(:,:,i_min,ii_min,iii_min, iiii_min)');
% simOut = sim('dp_EKF_anregung',paramNameValStruct);
% outputs = simOut.get('yout');
% phi2_time = (outputs.get('phi2').Values);
% phi2 = phi2_time.Data;
% phi2_est_time = (outputs.get('phi2_est').Values);
% phi2_est = phi2_est_time.Data;
% clf;
% h1 = plot(phi2_time); hold on;
% h2 = plot(phi2_est_time);
% xlabel('time in s'); ylabel('degree'); legend('phi2', 'phi2\_est');
