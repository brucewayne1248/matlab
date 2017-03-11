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
noise_power = 0.5*0.000000003;
x_0=0; dx_0=0; phi1_0=1*0.0175; dphi1_0=0; phi2_0=0; dphi2_0=0;
x0 = [phi1_0; dphi1_0; phi2_0; dphi2_0];
d2r = pi/180;
r2d = 1/d2r;
x0_ekf = [50*d2r; 5; -50*d2r; -4]; 

%% EKF
Pk_0 = eye(4);
Rk = 1;
Qk_min = diag([0.0001 1 0.1 10]);   % Anregung
% Qk_min = diag([0.01 10 10 0.0001]);   % ausschwing

%% Optimierung für alle Diagonalelemente von Q 
% pot_min = -4; pot_max = 1; steps = pot_max - pot_min + 1;
% q = logspace(pot_min,pot_max,steps);

open_system('dp_EKF_ausschwing');
paramNameValStruct.SimulationMode = 'normal';
paramNameValStruct.AbsTol         = '1e-5';
paramNameValStruct.SaveState      = 'on';
paramNameValStruct.StateSaveName  = 'xout';
paramNameValStruct.SaveOutput     = 'on';
paramNameValStruct.OutputSaveName = 'yout';
paramNameValStruct.SaveFormat = 'Dataset';
diff_min = Inf;

% for i = 1:length(q)
%     for ii = 1:length(q)
%         for iii = 1:length(q)
%             for iiii = 1:length(q)
%                 Qk = diag([q(i) q(ii) q(iii) q(iiii)]);
%                 set_param('dp_EKF_ausschwing/EKF/Gain', 'Gain', 'Qk');
%                 simOut = sim('dp_EKF_ausschwing',paramNameValStruct);
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
%                 diff = sum(sqrt((phi2-phi2_est).^2)) + sum(sqrt((dphi2-dphi2_est).^2));  
%                 % updating variables to best fit
%                 if (diff<diff_min)
%                     diff_min = diff;
%                     Qk_min = Qk;
%                 end
%             end
%         end
%     end
% end

%%
set_param('dp_EKF_ausschwing/EKF/Gain', 'Gain', 'Qk_min');
simOut = sim('dp_EKF_ausschwing',paramNameValStruct);
outputs = simOut.get('yout');
data = (outputs.get('data').Values);
t = data.Time;
values = data.Data;

phi1_time = (outputs.get('phi1').Values);
dphi1_time = (outputs.get('dphi1').Values);
phi2_time = (outputs.get('phi2').Values);
dphi2_time = (outputs.get('dphi2').Values);
phi1_est_time = (outputs.get('phi1_est').Values);
dphi1_est_time = (outputs.get('dphi1_est').Values);
phi2_est_time = (outputs.get('phi2_est').Values);
dphi2_est_time = (outputs.get('dphi2_est').Values);
phi1 = phi1_time.Data;
dphi1 = dphi1_time.Data;
phi2 = phi2_time.Data;
dphi2 = dphi2_time.Data;
phi1_est = phi1_est_time.Data;
dphi1_est = dphi1_est_time.Data;
phi2_est = phi2_est_time.Data;
dphi2_est = dphi2_est_time.Data;
t = phi1_est_time.Time;
