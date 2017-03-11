%%

xplot = x.Data(1:3001);
xplot = xplot(1:10:end);
phi1plot = phi1.Data(1:3001);
phi1plot = phi1plot(1:10:end);
phi2plot = phi2.Data(1:3001);
phi2plot = phi2plot(1:10:end);
t = (0:length(xplot)-1)*T_s*10;

figure(1),
subplot(2,1,1)
plot(t,100*xplot, 'LineWidth', 1.1), hold on
grid on; ax = gca; ax.GridLineStyle = ':';
xlabel('Zeit [s]')
ylabel('Wagenposition [cm]')
title('')
plot([0 3],[0 0], 'k--')
hold off

subplot(2,1,2)
plot(t,phi1plot*r2d,'r', 'LineWidth', 1.1), hold on,
plot(t,phi2plot*r2d,'g', 'LineWidth', 1.1),
grid on; ax = gca; ax.GridLineStyle = ':';
xlabel('Zeit [s]')
ylabel('Pendelwinekl [Grad]')
legend('Pendel 1', 'Pendel 2')
plot([0 3],[0 0], 'k--')
hold off
