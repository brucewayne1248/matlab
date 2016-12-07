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
x_0=0; dx_0=0; phi1_0=3*0.0175; dphi1_0=0; phi2_0=0; dphi2_0=0;
x0 = [phi1_0; dphi1_0; phi2_0; dphi2_0];
%% UKF Parameter
alpha = 0.001;
beta = 2;
kappa = 0;
Pk_0 = eye(4);
Rk = 1;
q12 = logspace(-5,3,9); q34 = q12;
Qk = zeros(4,4,9,9);
for k = 1:length(q12)
    for kk = 1:length(q12);
        Qk(1,1,k,kk) = q12(k); Qk(2,2,k,kk) = q12(k);
        Qk(3,3,k,kk) = q34(kk); Qk(4,4,k,kk) = q34(kk);
    end
end

%% Find optimal values for Qk and Rk
open_system('dp_UKF');
paramNameValStruct.SimulationMode = 'normal';
paramNameValStruct.AbsTol         = '1e-5';
paramNameValStruct.SaveState      = 'on';
paramNameValStruct.StateSaveName  = 'xout';
paramNameValStruct.SaveOutput     = 'on';
paramNameValStruct.OutputSaveName = 'yout';
paramNameValStruct.SaveFormat = 'Dataset';
diff_min = Inf;

for ii = 1:length(q12)
    for iii = 1:length(q34)
        set_param('dp_UKF/UKF/Qk', 'Gain', 'Qk(:,:,ii,iii)');
        simOut = sim('dp_UKF',paramNameValStruct);
        outputs = simOut.get('yout');
        phi2_time = (outputs.get('phi2').Values);
        phi2 = phi2_time.Data;
        phi2_est_time = (outputs.get('phi2_est').Values);
        phi2_est = phi2_est_time.Data;
                dphi2_time = (outputs.get('dphi2').Values);
        dphi2 = phi2_time.Data;
        dphi2_est_time = (outputs.get('dphi2_est').Values);
        dphi2_est = dphi2_est_time.Data;
        % criterion for choosing best fit
        diff = sum(sqrt((phi2-phi2_est).^2));   %sse(A-B) % sum((A-B).^2), norm(A-B) % sqrt(sse(A-B))
%         diff = max(abs(phi2-phi2_est)); %norm(A-B,inf) % max(abs(A-B))
        %updating variables to best fit
        if (diff<diff_min)
            diff_min = diff;
            Qk_min = Qk(:,:,ii,iii);
            ii_min = ii; iii_min = iii;
        end
    end
end

%% Set params according to best fit and plot phi2 
set_param('dp_UKF/UKF/Qk', 'Gain', 'Qk(:,:,ii_min,iii_min)');
simOut = sim('dp_UKF',paramNameValStruct);
outputs = simOut.get('yout');
phi2_time = (outputs.get('phi2').Values);
phi2 = phi2_time.Data;
phi2_est_time = (outputs.get('phi2_est').Values);
phi2_est = phi2_est_time.Data;
clf;
h1 = plot(phi2_time); hold on;
h2 = plot(phi2_est_time);
xlabel('time in s'); ylabel('degree'); legend('phi2', 'phi2\_est');

