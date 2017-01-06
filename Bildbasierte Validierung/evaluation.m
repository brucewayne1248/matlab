load('harm_erregung1.0_alu_05.01.mat')
load('video_angles_1.0_alu.mat')

T_s = 1e-3;
simulation_time = length(t);
index = find(Daten(:,6),1);
Daten = Daten(index:index+15000,:);
% Daten = Daten(1:15000,:);


for k = 1:length(Daten(:,1))
    t_meas(k) = (k-1)*T_s;
end


phi1_meas = Daten(:,1);
dphi1_meas = Daten(:,2);
ddphi1_meas = Daten(:,3);
x_meas = Daten(:,4);
dx_meas = Daten(:,5);
ddx_meas = Daten(:,6);



%% create time-series objects
 
Daten_ts = timeseries(Daten,t_meas);
phi1_meas_ts = timeseries(phi1_meas,t_meas);
dphi1_meas_ts = timeseries(dphi1_meas,t_meas);
ddphi1_meas_ts = timeseries(ddphi1_meas,t_meas);
x_meas_ts = timeseries(x_meas,t_meas);
dx_meas_ts = timeseries(dx_meas,t_meas);
ddx_meas_ts = timeseries(ddx_meas,t_meas);
%%
t_video = [];
for k = 1:length(phi1)
    t_video(k) = (k-1)*(1/frameRate);
end
%% resampling and cross-correlate
[P,Q] = rat((1/T_s)/frameRate);
phi1_video = resample(phi1,P,Q);
[C, lag] = xcorr(phi1_video,phi1_meas);
[~,I] = max(C);
lagDiff = lag(I);
timeDiff = lagDiff*T_s;
figure(3)
plot(lag,C)
%%
phi1_video_ts = timeseries(phi1,t_video);
phi2_video_ts = timeseries(phi2,t_video);

phi1_video_a = phi1_video(lagDiff:end);
t_video_a = (0:length(phi1_video_a)-1)*T_s;

subplot(2,1,1)
plot(t_video_a, phi1_video_a)
title('video')

subplot(2,1,2)
plot(t_meas,phi1_meas)
title('meas')


%%

figure(1) plot(phi1_meas_ts)
figure(2), plot(phi1_video_ts)