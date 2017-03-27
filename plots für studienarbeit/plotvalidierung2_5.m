clear all; close all;
load('final2_5.mat');

%%
phi1MeasDeg = phi1MeasDeg';

tMeas = tMeas(1:10:end);
phi1MeasDeg = phi1MeasDeg(1:10:end);
phi1EstDeg = phi1EstDeg(1:10:end);
dphi1MeasDeg2FiltLP =  dphi1MeasDeg2FiltLP(1:10:end);
dphi1EstDeg = dphi1EstDeg(1:10:end);
phi2VideoDeg = phi2VideoDeg(1:10:end);
phi2EstDeg = phi2EstDeg(1:10:end);
dphi2VideoDegFiltLP = dphi2VideoDegFiltLP(1:10:end);
dphi2EstDeg = dphi2EstDeg(1:10:end);

%%
figure(1)
subplot(2,1,1)
plot(tMeas,phi1MeasDeg,'r','LineWidth',1.0), hold on
plot(tMeas,phi1EstDeg,'k--','LineWidth',1.0)
grid on; ax = gca; ax.GridLineStyle = ':';
axis([0 20 -inf inf]);
xlabel('Zeit [s]')
ylabel('Winkel [Grad]')
legend('phi1','phi1Est')
hold off
subplot(2,1,2)
plot(tMeas,phi2VideoDeg,'g','LineWidth',1.0), hold on
plot(tMeas,phi2EstDeg,'b--','LineWidth',1.0)
grid on; ax = gca; ax.GridLineStyle = ':';
axis([0 20 -inf inf]);
xlabel('Zeit [s]')
ylabel('Winkel [Grad]')
legend('phi2','phi2Est')
% legend('phi1','phi1Est','phi2','phi2Est')
hold off
 
figure(2),
subplot(2,1,1)
plot(tMeas,dphi1MeasDeg2FiltLP,'r','LineWidth',1.0), hold on
plot(tMeas,dphi1EstDeg,'k--','LineWidth',1.0)
grid on; ax = gca; ax.GridLineStyle = ':';
axis([0 20 -inf inf]);
xlabel('Zeit [s]')
ylabel('Winkelgeschw. [Grad/s]')
legend('dphi1','dphi1Est')
hold off
subplot(2,1,2)
plot(tMeas,dphi2VideoDegFiltLP,'g','LineWidth',1.0), hold on
plot(tMeas,dphi2EstDeg,'b--','LineWidth',1.0)
axis([0 20 -inf inf]);
grid on; ax = gca; ax.GridLineStyle = ':';
xlabel('Zeit [s]')
ylabel('Winkelgeschw. [Grad/s]')
legend('dphi2','dphi2Est')
legend('dphi2','dphi2Est')
hold off