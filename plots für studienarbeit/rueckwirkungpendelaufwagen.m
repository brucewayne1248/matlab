clear all, close all;

load('D:\Documents\Studienarbeit imes\matlab\Bildbasierte Validierung\validierungEKF_ausschwing01.mat', 'xMeasReal');
T_s = 1e-3;
xMeasReal = xMeasReal(1:10e3) * 1e6;
xMeasReal = xMeasReal - xMeasReal(1); 
[b,a] = butter(2,0.02,'low');
xMeasRealFilt = filtfilt(b,a,xMeasReal);


for k = 1:length(xMeasRealFilt)
    if (mod(k,10) == 0)
    xMeasRealFiltTikz(k/10) = xMeasRealFilt(k);
    end
end    

t = (0:length(xMeasRealFiltTikz)- 1)*T_s*10;

figure(1),
plot(t,xMeasRealFiltTikz, 'LineWidth', 1.1), xlabel('Zeit [s]'), ylabel('Mikrometer [\mum]', 'interpreter', 'tex');
