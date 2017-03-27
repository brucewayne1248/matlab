load('simuanregungdata.mat')



%% Winkel abweichung
phi1DiffMax =  max(abs(phi1(1001:end)-phi1Est(1001:end)))
phi2DiffMax =  max(abs(phi2(1001:end)-phi2Est(1001:end)))

%% plots
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
plot(t,phi1,'r','LineWidth',1.1), hold on
plot(t,phi1Est,'k--','LineWidth',1.1)
grid on; ax = gca; ax.GridLineStyle = ':';
xlabel('Zeit [s]')
ylabel('Winkel [Grad]')
legend('phi1','phi1Est')
hold off
subplot(2,1,2)
plot(t,phi2,'g','LineWidth',1.1), hold on
plot(t,phi2Est,'k--','LineWidth',1.1)
grid on; ax = gca; ax.GridLineStyle = ':';
xlabel('Zeit [s]')
ylabel('Winkel [Grad]')
legend('phi2','phi2Est')
hold off

figure(2),
subplot(2,1,1)
plot(t,dphi1,'r','LineWidth',0.5), hold on
plot(t,dphi1Est,'k--','LineWidth',1.1)
grid on; ax = gca; ax.GridLineStyle = ':';
xlabel('Zeit [s]')
ylabel('Winkelgeschw. [Grad/s]')
axis([0 5 -2000 2000])
legend('dphi1','dphi1Est')
hold off
subplot(2,1,2)
plot(t,dphi2,'g','LineWidth',1.1), hold on
plot(t,dphi2Est,'k--','LineWidth',1.1)
grid on; ax = gca; ax.GridLineStyle = ':';
xlabel('Zeit [s]')
ylabel('Winkelgeschw. [Grad/s]')
axis([0 5 -2000 2000])
legend('dphi2','dphi2Est')
hold off


