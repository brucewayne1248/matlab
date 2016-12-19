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
d2r = pi/180;
noise_power = 0.5*0.000000003;
x_0=0; dx_0=0; phi1_0=2*d2r; dphi1_0=0; phi2_0=0*d2r; dphi2_0=0;
x0 = [phi1_0; dphi1_0; phi2_0; dphi2_0];
x0_ukf = x0;

%% EKF Parameter
<<<<<<< HEAD
alpha = 0.0001;
=======
alpha = 0.01;
>>>>>>> 3003dd7af9d65cf83e5f85ff7eb245b367eb16a2
beta = 2;
kappa = 0;
Pk_0 = eye(4);
Rk = 1;
<<<<<<< HEAD
pot_min = -3; pot_max = 3; steps = pot_max - pot_min + 1;
q12 = logspace(pot_min,pot_max,steps); q34 = q12;
Qk = zeros(4,4,steps,steps);
% Qk = zeros(4,4);
=======
pot_min = -5; pot_max = 3; steps = pot_max-pot_min +1;
q12 = logspace(pot_min, pot_max, steps); q34 = q12;
Qk = zeros(4,4,steps,steps);
>>>>>>> 3003dd7af9d65cf83e5f85ff7eb245b367eb16a2

for k = 1:length(q12)
    for kk = 1:length(q12);
        Qk(1,1,k,kk) = q12(k); Qk(2,2,k,kk) = q12(k);
        Qk(3,3,k,kk) = q34(kk); Qk(4,4,k,kk) = q34(kk);
    end
end

 %% Find optimal values for Qk and Rk
open_system('dp_UKF_anregung');
paramNameValStruct.SimulationMode = 'normal';
paramNameValStruct.AbsTol         = '1e-5';
paramNameValStruct.SaveState      = 'on';
paramNameValStruct.StateSaveName  = 'xout';
paramNameValStruct.SaveOutput     = 'on';
paramNameValStruct.OutputSaveName = 'yout';
paramNameValStruct.SaveFormat = 'Dataset';
diff_min = Inf;
<<<<<<< HEAD
t_sim_max = 0;
err = {length(q12),length(q34)};
    
for ii = 1:length(q12)
    for iii = 1:length(q34)
        try
        set_param('dp_UKF_anregung/UKF/Qk', 'Gain', 'Qk(:,:,ii,iii)');
        simOut = sim('dp_UKF_anregung',paramNameValStruct);
%         simOut = sim('dp_UKF_anregung', 'CaptureErrors', 'on');
=======

for ii = 1:length(q12)
    for iii = 1:length(q34)
        set_param('dp_UKF_anregung/UKF/Qk', 'Gain', 'Qk(:,:,ii,iii)');
%         simOut = sim('dp_UKF_anregung',paramNameValStruct);
        simOut = sim('dp_UKF_anregung','CaptureErrors','on');
>>>>>>> 3003dd7af9d65cf83e5f85ff7eb245b367eb16a2
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
<<<<<<< HEAD
        t_sim = length(tout);
%         diff = sum(sqrt((phi2-phi2_est).^2));   %sse(A-B) % sum((A-B).^2), norm(A-B) % sqrt(sse(A-B))
%         diff = max(abs(phi2-phi2_est)); %norm(A-B,inf) % max(abs(A-B))
        %updating variables to best fit
%         if (diff<diff_min)
%             diff_min = diff;
%             Qk_min = Qk(:,:,ii,iii);
%             ii_min = ii; iii_min = iii;
%         end
        if (t_sim > t_sim_max)
            t_sim_max = t_sim;
            Qk_min = Qk(:,:,ii,iii);
            ii_min = ii; iii_min = iii;
        end
        catch ME
            err{ii,iii} = ME.message;
        end
    end
end

 %% Set params according to best fit and plot phi2 
% set_param('dp_UKF_anregung/EKF/Qk', 'Gain', 'Qk(:,:,ii_min,iii_min)');
=======
        diff = 
%         diff = sum(sqrt((phi2-phi2_est).^2));   %sse(A-B) % sum((A-B).^2), norm(A-B) % sqrt(sse(A-B))
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
set_param('dp_UKF_anregung/UKF/Qk', 'Gain', 'Qk(:,:,ii_min,iii_min)');
>>>>>>> 3003dd7af9d65cf83e5f85ff7eb245b367eb16a2
% simOut = sim('dp_UKF_anregung',paramNameValStruct);
% outputs = simOut.get('yout');
% phi2_time = (outputs.get('phi2').Values);
% phi2 = phi2_time.Data;
% phi2_est_time = (outputs.get('phi2_est').Values);
% phi2_est = phi2_est_time.Data;
% clf;
% h1 = plot(phi2_time); hold on;
% h2 = plot(phi2_est_time);
% xlabel('time in s'); ylabel('degree'); legend('phi2', 'phi2\_est');

