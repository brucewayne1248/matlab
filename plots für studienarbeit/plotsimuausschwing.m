load('simuausschwingdata.mat')
close all

t = t(1:5:end);
values = values(1:5:end,:);

phi1Est = values(:,1);
dphi1Est = values(:,2);
phi2Est = values(:,3);
dphi2Est = values(:,4);
phi1 = values(:,5);
dphi1 = values(:,6);
phi2 = values(:,7);
dphi2 = values(:,8);

darkred = [0.8,0.2,0.3];

figure(1)
subplot(2,1,1)
plot(t,phi1,'g','LineWidth',1), hold on
plot(t,phi1Est,'b--','LineWidth',1)
plot(t,phi2,'r','LineWidth',1)
plot(t,phi2Est,'k--','LineWidth',1)
grid on; ax = gca; ax.GridLineStyle = ':';
xlabel('Zeit [s]')
ylabel('Winkel [Grad]')
legend('phi1','phi1Est','phi2','phi2Est')
hold off

subplot(2,1,2)
plot(t,dphi1,'g','LineWidth',0.6), hold on
plot(t,dphi1Est,'b--','LineWidth',1.2)
plot(t,dphi2,'r','LineWidth',1.2)
plot(t,dphi2Est,'k--','LineWidth',1.2)
grid on; ax = gca; ax.GridLineStyle = ':';
xlabel('Zeit [s]')
ylabel('Winkelgeschw. [Grad/s]')
legend('dphi1','dphi1Est','dphi2','dphi2Est')
hold off


