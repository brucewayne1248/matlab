%% Konstanten
% Dichte Alu: 2.7g/cm^3=2700kg/m^3, Dichte Eisen: 7.874g/cm^3= 7874kg/m^3,
% ca 3 mal so schwer
% Konstanten benötigt für momentengesteuerte Regelung

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
x_0=0; dx_0=0; phi1_0=3*0.0175; dphi1_0=0; phi2_0=0; dphi2_0=0;
x0 = [phi1_0; dphi1_0; phi2_0; dphi2_0];
%% Zustandsraum des linearisierten Systems
mn = 4*m_1+3*m_2+12*m_3;

a21=  (3*g*(2*m_1+4*m_2+4*m_3))/...
      (l_1*mn);
a22=  -(3*(4*d_p1*l_2+6*d_p2*l_1+4*d_p2*l_2))/...
      (l_1^2*l_2*mn);
a23=  (-9*g*m_2)/...
      (l_1*mn);
a24=  (3*d_p2*(6*l_1+4*l_2))/...
      (l_1^2*l_2*mn);
a41=  -3*g*(3*m_1+6*m_2+6*m_3)/...
      (l_2*mn);
a42=  3*(d_p2*l_1*(4*m_1+12*m_2+12*m_3)+6*l_2*m_2*(d_p1+d_p2))/...
      (l_1*l_2^2*m_2*mn);
a43=  3*g*(2*m_1+6*m_2+6*m_3)/...
      (l_2*mn);
a44=  -3*(d_p2*l_1*(4*m_1+12*m_2+12*m_3)+6*d_p2*l_2*m_2)/...
      (l_1*l_2^2*m_2*mn);
  
A = [0 1 0 0;
     a21 a22 a23 a24;
     0 0 0 1;
     a41 a42 a43 a44];

A6 = [0 1 0 0 0 0;
      0 0 0 0 0 0;
      0 0 0 1 0 0;
      0 0 a21 a22 a23 a24;
      0 0 0 0 0 1;
      0 0 a41 a42 a43 a44];

b2=  3*(2*m_1+m_2+4*m_3)/(l_1*mn);
b4=  (-3*m_1)/(l_2*mn);
B = [0; b2; 0; b4];
B6 = [0;1; 0; b2; 0; b4];

C = [1 0 0 0;
     0 0 1 0];

C6 = [1 0 0 0 0 0;
      0 0 1 0 0 0;
      0 0 0 0 1 0];

D = [0;0];
D6 = [0;0;0;];
sys = ss(A,B,C,D);
sys6 = ss(A6,B6,C6,D6);
sysd = c2d(sys,0.0001);
Ad = sysd.a;
Bd = sysd.b;
Cd = sysd.c;
sys6d = c2d(sys6,T_s);
Ad6 = sys6d.a;
Bd6 = sys6d.b;
Cd6 = sys6d.c;
%% Steuerbarkeit, Beobachtbarkeit nach Kalman
S = ctrb(sys);
r_S = rank(S);
S6 = ctrb(sys6);
r_S6=rank(S6);

O = obsv(sys);
r_O = rank(O);
O6 = obsv(sys6);
r_O6 = rank(O6);
%% Zustandsrückführung mittels LQR
% Maximalwerte für Zustände festsetzen
x_max = 0.2;
dx_max = 5;
phi1_max = 0.087;
dphi1_max = 2;
phi2_max = 0.087;
dphi2_max = 2;
% Einträge der Wichtungsmatrix
Q_11 = 1/(x_max^2);
Q_22 = 1/(dx_max^2);
Q_33 = 1/(phi1_max^2);
Q_44 = 1/(dphi1_max^2);
Q_55 = 1/(phi2_max^2);
Q_66 = 1/(dphi2_max^2);
Q = diag([Q_33 Q_44 Q_55 Q_66]);
Q6 = diag([Q_11 Q_22 Q_33 Q_44 Q_55 Q_66]);
% Q_3 = diag([100 1 100 1]);
% Wichtungsfaktor für Wagenbeschleunigung
% ddx_max = 20;
% R = 1/ddx_max^2;
R_2 = 1/20;
% [K_lqr,S_lqr,eig_lqr] = lqr(A,B,Q,R);
[K6_lqr,S6_lqr,eig6_lqr]=lqr(A6,B6,Q6,R_2);
%% Zustandsrückführung durch Polvorgabe
% p_A = eig(A);
% p_s = 1.9*[-3 -3.5 -4 -4.5];
% p_s6 = 0.9*[-15+1i -15-1i -8 -7 -2 -1];
% K = place(A,B,p_s);
% K6 = place(A6,B6,p_s6);
% eig_K6 = eig(A6-B6*K6')

%% EKF
Pk_0 = eye(4);
Rk = 1;
%% Optimierung für Q11 = Q22; Q33 = Q44
% pot_min = -5; pot_max = 1; steps = pot_max - pot_min + 1;
% q12 = logspace(pot_min,pot_max,steps); q34 = q12;
% Qk = zeros(4,4,steps,steps);
% for k = 1:length(q12)
%     for kk = 1:length(q12);
%         Qk(1,1,k,kk) = q12(k); Qk(2,2,k,kk) = q12(k);
%         Qk(3,3,k,kk) = q34(kk); Qk(4,4,k,kk) = q34(kk);
%     end
% end
%% Optimierung für alle Diagonalelemente von Q 
pot_min = -4; pot_max = 1; steps = pot_max - pot_min + 1;
qii = logspace(pot_min,pot_max,steps);
Qk = zeros(4,4,steps,steps,steps,steps);
for k = 1:length(qii)
    for kk = 1:length(qii);
        for kkk = 1:length(qii);
            for kkkk = 1:length(qii);
                Qk(1,1,k,kk,kkk,kkkk) = qii(k); 
                Qk(2,2,k,kk,kkk,kkkk) = qii(kk); 
                Qk(3,3,k,kk,kkk,kkkk) = qii(kkk); 
                Qk(4,4,k,kk,kkk,kkkk) = qii(kkkk); 
            end
        end
    end
end
%% Find optimal weights for Qk and Rk
open_system('dp_EKF');
paramNameValStruct.SimulationMode = 'normal';
paramNameValStruct.AbsTol         = '1e-5';
paramNameValStruct.SaveState      = 'on';
paramNameValStruct.StateSaveName  = 'xout';
paramNameValStruct.SaveOutput     = 'on';
paramNameValStruct.OutputSaveName = 'yout';
paramNameValStruct.SaveFormat = 'Dataset';
diff_min = Inf;
%% Q11 = Q22, Q33 = Q44;
% for i = 1:length(q12)
%     for ii = 1:length(q34)
%         set_param('dp_EKF/EKF/Qk', 'Gain', 'Qk(:,:,i,ii)');
%         simOut = sim('dp_EKF',paramNameValStruct);
%         outputs = simOut.get('yout');
%         phi2_time = (outputs.get('phi2').Values);
%         phi2 = phi2_time.Data;
%         phi2_est_time = (outputs.get('phi2_est').Values);
%         phi2_est = phi2_est_time.Data;
%         dphi2_time = (outputs.get('dphi2').Values);
%         dphi2 = phi2_time.Data;
%         dphi2_est_time = (outputs.get('dphi2_est').Values);
%         dphi2_est = dphi2_est_time.Data;
%         % criterion for choosing best fit
%         diff = sum(sqrt((phi2-phi2_est).^2)) + sum(sqrt((dphi2-dphi2_est).^2));   
%         %updating variables to best fit
%         if (diff<diff_min)
%             diff_min = diff;
%             Qk_min = Qk(:,:,i,ii);
%             i_min = i; ii_min = ii;
%         end
%     end
% end
%% Qii variable 
for i = 1:length(qii)
    for ii = 1:length(qii)
        for iii = 1:length(qii)
            for iiii = 1:length(qii)
                set_param('dp_EKF/EKF/Qk', 'Gain', 'Qk(:,:,i,ii,iii,iiii)');
                simOut = sim('dp_EKF',paramNameValStruct);
                outputs = simOut.get('yout');
                phi2_time = (outputs.get('phi2').Values);
                phi2 = phi2_time.Data;
                phi2_est_time = (outputs.get('phi2_est').Values);
                phi2_est = phi2_est_time.Data;
                dphi2_time = (outputs.get('dphi2').Values);
                dphi2 = phi2_time.Data;
                dphi2_est_time = (outputs.get('dphi2_est').Values);
                dphi2_est = dphi2_est_time.Data;
%                 criterion for choosing best fit
                diff = sum(sqrt((phi2-phi2_est).^2)) + sum(sqrt((dphi2-dphi2_est).^2));  
%                 updating variables to best fit
                if (diff<diff_min)
                    diff_min = diff;
                    Qk_min = Qk(:,:,i,ii,iii,iiii);
                    i_min = i; ii_min = ii; iii_min = iii; iiii_min = iiii;
                end
            end
        end
    end
end

%% Set params according to best fit and plot phi2 
% set_param('dp_EKF/EKF/Qk', 'Gain', 'Qk(:,:,i_min,ii_min)');
set_param('dp_EKF/EKF/Qk', 'Gain', 'Qk(:,:,i_min,ii_min,iii_min, iiii_min)');
simOut = sim('dp_EKF',paramNameValStruct);
% outputs = simOut.get('yout');
% phi2_time = (outputs.get('phi2').Values);
% phi2 = phi2_time.Data;
% phi2_est_time = (outputs.get('phi2_est').Values);
% phi2_est = phi2_est_time.Data;
% clf;
% h1 = plot(phi2_time); hold on;
% h2 = plot(phi2_est_time);
% xlabel('time in s'); ylabel('degree'); legend('phi2', 'phi2\_est');