function [ phiExt ] = angle_extender( phi )
%ANGLEEXTENDER extends vectors of angles in degree from 0...360° to +- Inf
%   Detailed explanation here

rot = 0;
degPerSpin = 360;
[row, col] = size(phi);
if (col == 1)
    phi = [phi; phi(end)];
elseif (row == 1)
    phi = [phi phi(end)];
end

phiExt = zeros(row, col);
for k = 1:length(phi)-1
    phiExt(k) = degPerSpin * rot + phi(k);
    
    if (phi(k)-phi(k+1) >350)
        rot = rot + 1;
    elseif (phi(k) - phi(k+1) < -355)
        rot = rot - 1;
    end
    
end

end

