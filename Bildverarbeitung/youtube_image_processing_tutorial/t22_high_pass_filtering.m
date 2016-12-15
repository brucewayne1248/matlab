[x,y] = meshgrid(-128:127,-128:127);
z = sqrt(x.^2+y.^2);
x = z>15;  