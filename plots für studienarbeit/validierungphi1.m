load('validierungphi1.mat')

tVideo = tVideo(1:10:10001);
phi1VideoDeg = phi1VideoDeg(1:10:10001);
phi1MeasDeg = phi1MeasDeg(1:10:10001);

figure(1),
plot(tVideo,phi1MeasDeg,'r'), hold on
plot(tVideo,phi1VideoDeg,'b')
xlabel('Zeit [s]')
ylabel('Winkel [Grad]')
grid on; ax = gca; ax.GridLineStyle = ':';
legend('Messung','Kameraaufnahme')
hold off
