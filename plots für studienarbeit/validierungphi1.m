load('validierungphi1.mat')

% corrcoef = corrcoef(phi1MeasDeg,phi1VideoDeg)

phi1DiffMax =  max(abs(phi1MeasDeg(1:end)-phi1VideoDeg(1:end)))

SSD = sum(sqrt((phi1MeasDeg-phi1VideoDeg).^2))

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
