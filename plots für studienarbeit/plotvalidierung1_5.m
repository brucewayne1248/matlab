clear all; close all;
load('final_harm1_5.mat');

phi1MeasDeg = phi1MeasDeg';
dphi1MeasDeg = dphi1MeasDeg';
%%
dt = 1/1000;
dphi1MeasDegFilt = diff(phi1MeasDeg)/dt;  % diff 
dphi1MeasDegMag = abs(fft(dphi2VideoDegFiltLP)); % magnitude

% figure(1),
% plot(dphi2VideoDeg), title('dphi2 ungefiltert')

nfft = length(dphi1MeasDegMag);

% figure(2)
% plot([0:1/(nfft/2 -1):1], dphi2VideoDegMag(1:nfft/2)), title('dphi2 Frequenzbereich')

[b, a] = butter(2, 0.02, 'low'); % Tiefpassfilter

H = freqz(b,a, floor(nfft/2));
% figure(3),
% plot([0:1/(nfft/2 -1):1], abs(H),'r'), title('Filter Übertragungsfunktion')

dphi1MeasDegFiltLP = filter(b,a,dphi1MeasDegFilt);
dphi1MeasDegFiltLP = [0  dphi1MeasDegFiltLP ];


%% Winkel abweichung
phi1DiffMax =  max(abs(phi1EstDeg(2001:end)-phi1MeasDeg(2001:end)))
phi2DiffMax =  max(abs(phi2EstDeg(2001:end)-phi2VideoDeg(2001:end)))

%% plots
tMeas = tMeas(1:10:end);

phi1EstDeg = phi1EstDeg(1:10:end);
phi1MeasDeg = phi1MeasDeg(1:10:end);
phi2EstDeg = phi2EstDeg(1:10:end);
phi2VideoDeg = phi2VideoDeg(1:10:end);
dphi1EstDeg = dphi1EstDeg(1:10:end);
dphi1MeasDeg = dphi1MeasDeg(1:10:end);
dphi2EstDeg= dphi2EstDeg(1:10:end);
dphi2VideoDegFiltLP= dphi2VideoDegFiltLP(1:10:end);
dphi1MeasDegFiltLP = dphi1MeasDegFiltLP(1:10:end);


figure(1)
subplot(2,1,1)
plot(tMeas,phi1MeasDeg,'r','LineWidth',1.0), hold on
plot(tMeas,phi1EstDeg,'k--','LineWidth',1.0)
grid on; ax = gca; ax.GridLineStyle = ':';
axis([0 10 -inf inf]);
xlabel('Zeit [s]')
ylabel('Winkel [Grad]')
% hold off
% subplot(2,1,2)
plot(tMeas,phi2VideoDeg,'g','LineWidth',1.0) %, hold on
plot(tMeas,phi2EstDeg,'b--','LineWidth',1.0)
grid on; ax = gca; ax.GridLineStyle = ':';
axis([0 10 -inf inf]);
xlabel('Zeit [s]')
ylabel('Winkel [Grad]')
% legend('phi2','phi2Est')
legend('phi1','phi1Est','phi2','phi2Est')
hold off

% figure(2),
subplot(2,1,2)
% plot(tMeas,dphi1MeasDeg,'r','LineWidth',1.0), hold on
%, hold on
plot(tMeas,dphi1MeasDegFiltLP,'r','LineWidth',1.0), hold on 
plot(tMeas,dphi1EstDeg,'k--','LineWidth',1.0)
grid on; ax = gca; ax.GridLineStyle = ':';
axis([0 10 -inf inf]);
xlabel('Zeit [s]')
ylabel('Winkelgeschw. [Grad/s]')
% hold off
% subplot(2,1,2)
plot(tMeas,dphi2VideoDegFiltLP,'g','LineWidth',1.0)%, hold on
plot(tMeas,dphi2EstDeg,'b--','LineWidth',1.0)
axis([0 10 -inf inf]);
grid on; ax = gca; ax.GridLineStyle = ':';
xlabel('Zeit [s]')
ylabel('Winkelgeschw. [Grad/s]')
% legend('dphi2','dphi2Est')
legend('dphi1','dphi1Est','dphi2','dphi2Est')
hold off
