function [x, K]  = extended_kalman_filter(P, Q, R, x0, para_sys, T_s, u, y, init)
% Extended Kalman Filter (EKF) fuer nichtlineare Systeme
% Das Extended Kalman Filter praediziert den Zustand eines nichtlinearen
% Systems durch Linearisierung im Arbeistpunkt.
% R ist die Kovarianzmatrix fuer das Messrauschen.
% Q ist die Kovarianzmatrix fuer das Prozessrauschen.
% Das Verhaeltnis von Q und R gibt die Dynamik des Filters vor.

persistent x_p P_p
% Parameter

g = para_sys(1);
l_1 = para_sys(2);
l_2 = para_sys(3);
m_1 = para_sys(4);
m_2 = para_sys(5);
m_3 = para_sys(6);
d_p1 = para_sys(7);
d_p2 = para_sys(8);

if (isempty(x_p) || init == 1)
   x_p = x0;
   P_p = P;
   x = x_p;
   K = zeros(4,1);
else
%% Discrete Kalman filter time update equations

 x_1 = x_p(1);
 x_2 = x_p(2);
 x_3 = x_p(3);
 x_4 = x_p(4);

x = [x_1 + T_s*x_2;x_2 + (T_s*(12*d_p2*l_2*x_4 - 12*d_p1*l_2*x_2 - 12*d_p2*l_2*x_2 - cos(x_1 - x_3)*(18*d_p2*l_1*x_2 - 18*d_p2*l_1*x_4 + 9*l_1*l_2*m_2*u*cos(x_3) + 9*g*l_1*l_2*m_2*sin(x_3) + 9*l_1^2*l_2*m_2*x_2^2*sin(x_1 - x_3)) + 6*l_1*l_2*m_1*u*cos(x_1) + 12*l_1*l_2*m_2*u*cos(x_1) + 12*l_1*l_2*m_3*u*cos(x_1) + 6*g*l_1*l_2*m_1*sin(x_1) + 12*g*l_1*l_2*m_2*sin(x_1) + 12*g*l_1*l_2*m_3*sin(x_1) - 6*l_1*l_2^2*m_2*x_4^2*sin(x_1 - x_3)))/(l_1^2*l_2*(4*m_1 + 12*m_2 + 12*m_3 - 9*m_2*cos(x_1 - x_3)^2));x_3 + T_s*x_4;x_4 + (T_s*(sin(x_1 - x_3)*(36*l_1^2*l_2*m_2^2*x_2^2 + 12*l_1^2*l_2*m_1*m_2*x_2^2 + 36*l_1^2*l_2*m_2*m_3*x_2^2) + 24*d_p2*l_1*m_1*x_2 + 72*d_p2*l_1*m_2*x_2 - 24*d_p2*l_1*m_1*x_4 + 72*d_p2*l_1*m_3*x_2 - 72*d_p2*l_1*m_2*x_4 - 72*d_p2*l_1*m_3*x_4 + 36*d_p1*l_2*m_2*x_2*cos(x_1 - x_3) + 36*d_p2*l_2*m_2*x_2*cos(x_1 - x_3) - 36*d_p2*l_2*m_2*x_4*cos(x_1 - x_3) + 18*l_1*l_2*m_2^2*u*cos(x_3) + 18*g*l_1*l_2*m_2^2*sin(x_3) + 9*l_1*l_2^2*m_2^2*x_4^2*sin(2*x_1 - 2*x_3) - 18*l_1*l_2*m_2^2*u*cos(2*x_1 - x_3) - 18*g*l_1*l_2*m_2^2*sin(2*x_1 - x_3) + 3*l_1*l_2*m_1*m_2*u*cos(x_3) + 18*l_1*l_2*m_2*m_3*u*cos(x_3) + 3*g*l_1*l_2*m_1*m_2*sin(x_3) + 18*g*l_1*l_2*m_2*m_3*sin(x_3) - 9*l_1*l_2*m_1*m_2*u*cos(2*x_1 - x_3) - 18*l_1*l_2*m_2*m_3*u*cos(2*x_1 - x_3) - 9*g*l_1*l_2*m_1*m_2*sin(2*x_1 - x_3) - 18*g*l_1*l_2*m_2*m_3*sin(2*x_1 - x_3)))/(l_1*l_2^2*m_2*(8*m_1 + 15*m_2 + 24*m_3 - 9*m_2*cos(2*x_1 - 2*x_3)))];
       
        % Jacobian Matrix
A = [1, T_s, 0, 0;- (T_s*(6*l_1*l_2*m_1*u*sin(x_1) - sin(x_1 - x_3)*(18*d_p2*l_1*x_2 - 18*d_p2*l_1*x_4 + 9*l_1*l_2*m_2*u*cos(x_3) + 9*g*l_1*l_2*m_2*sin(x_3) + 9*l_1^2*l_2*m_2*x_2^2*sin(x_1 - x_3)) + 12*l_1*l_2*m_2*u*sin(x_1) + 12*l_1*l_2*m_3*u*sin(x_1) + 9*l_1^2*l_2*m_2*x_2^2*cos(x_1 - x_3)^2 - 6*g*l_1*l_2*m_1*cos(x_1) - 12*g*l_1*l_2*m_2*cos(x_1) - 12*g*l_1*l_2*m_3*cos(x_1) + 6*l_1*l_2^2*m_2*x_4^2*cos(x_1 - x_3)))/(l_1^2*l_2*(4*m_1 + 12*m_2 + 12*m_3 - 9*m_2*cos(x_1 - x_3)^2)) - (18*T_s*m_2*cos(x_1 - x_3)*sin(x_1 - x_3)*(12*d_p2*l_2*x_4 - 12*d_p1*l_2*x_2 - 12*d_p2*l_2*x_2 - cos(x_1 - x_3)*(18*d_p2*l_1*x_2 - 18*d_p2*l_1*x_4 + 9*l_1*l_2*m_2*u*cos(x_3) + 9*g*l_1*l_2*m_2*sin(x_3) + 9*l_1^2*l_2*m_2*x_2^2*sin(x_1 - x_3)) + 6*l_1*l_2*m_1*u*cos(x_1) + 12*l_1*l_2*m_2*u*cos(x_1) + 12*l_1*l_2*m_3*u*cos(x_1) + 6*g*l_1*l_2*m_1*sin(x_1) + 12*g*l_1*l_2*m_2*sin(x_1) + 12*g*l_1*l_2*m_3*sin(x_1) - 6*l_1*l_2^2*m_2*x_4^2*sin(x_1 - x_3)))/(l_1^2*l_2*(4*m_1 + 12*m_2 + 12*m_3 - 9*m_2*cos(x_1 - x_3)^2)^2), 1 - (T_s*(12*d_p1*l_2 + 12*d_p2*l_2 + cos(x_1 - x_3)*(18*d_p2*l_1 + 18*l_1^2*l_2*m_2*x_2*sin(x_1 - x_3))))/(l_1^2*l_2*(4*m_1 + 12*m_2 + 12*m_3 - 9*m_2*cos(x_1 - x_3)^2)), (T_s*(cos(x_1 - x_3)*(9*l_1*l_2*m_2*u*sin(x_3) - 9*g*l_1*l_2*m_2*cos(x_3) + 9*l_1^2*l_2*m_2*x_2^2*cos(x_1 - x_3)) - sin(x_1 - x_3)*(18*d_p2*l_1*x_2 - 18*d_p2*l_1*x_4 + 9*l_1*l_2*m_2*u*cos(x_3) + 9*g*l_1*l_2*m_2*sin(x_3) + 9*l_1^2*l_2*m_2*x_2^2*sin(x_1 - x_3)) + 6*l_1*l_2^2*m_2*x_4^2*cos(x_1 - x_3)))/(l_1^2*l_2*(4*m_1 + 12*m_2 + 12*m_3 - 9*m_2*cos(x_1 - x_3)^2)) + (18*T_s*m_2*cos(x_1 - x_3)*sin(x_1 - x_3)*(12*d_p2*l_2*x_4 - 12*d_p1*l_2*x_2 - 12*d_p2*l_2*x_2 - cos(x_1 - x_3)*(18*d_p2*l_1*x_2 - 18*d_p2*l_1*x_4 + 9*l_1*l_2*m_2*u*cos(x_3) + 9*g*l_1*l_2*m_2*sin(x_3) + 9*l_1^2*l_2*m_2*x_2^2*sin(x_1 - x_3)) + 6*l_1*l_2*m_1*u*cos(x_1) + 12*l_1*l_2*m_2*u*cos(x_1) + 12*l_1*l_2*m_3*u*cos(x_1) + 6*g*l_1*l_2*m_1*sin(x_1) + 12*g*l_1*l_2*m_2*sin(x_1) + 12*g*l_1*l_2*m_3*sin(x_1) - 6*l_1*l_2^2*m_2*x_4^2*sin(x_1 - x_3)))/(l_1^2*l_2*(4*m_1 + 12*m_2 + 12*m_3 - 9*m_2*cos(x_1 - x_3)^2)^2), (T_s*(12*d_p2*l_2 + 18*d_p2*l_1*cos(x_1 - x_3) - 12*l_1*l_2^2*m_2*x_4*sin(x_1 - x_3)))/(l_1^2*l_2*(4*m_1 + 12*m_2 + 12*m_3 - 9*m_2*cos(x_1 - x_3)^2));0, 0, 1, T_s;(T_s*(cos(x_1 - x_3)*(36*l_1^2*l_2*m_2^2*x_2^2 + 12*l_1^2*l_2*m_1*m_2*x_2^2 + 36*l_1^2*l_2*m_2*m_3*x_2^2) - 36*d_p1*l_2*m_2*x_2*sin(x_1 - x_3) - 36*d_p2*l_2*m_2*x_2*sin(x_1 - x_3) + 36*d_p2*l_2*m_2*x_4*sin(x_1 - x_3) + 18*l_1*l_2^2*m_2^2*x_4^2*cos(2*x_1 - 2*x_3) - 36*g*l_1*l_2*m_2^2*cos(2*x_1 - x_3) + 36*l_1*l_2*m_2^2*u*sin(2*x_1 - x_3) + 18*l_1*l_2*m_1*m_2*u*sin(2*x_1 - x_3) + 36*l_1*l_2*m_2*m_3*u*sin(2*x_1 - x_3) - 18*g*l_1*l_2*m_1*m_2*cos(2*x_1 - x_3) - 36*g*l_1*l_2*m_2*m_3*cos(2*x_1 - x_3)))/(l_1*l_2^2*m_2*(8*m_1 + 15*m_2 + 24*m_3 - 9*m_2*cos(2*x_1 - 2*x_3))) - (18*T_s*sin(2*x_1 - 2*x_3)*(sin(x_1 - x_3)*(36*l_1^2*l_2*m_2^2*x_2^2 + 12*l_1^2*l_2*m_1*m_2*x_2^2 + 36*l_1^2*l_2*m_2*m_3*x_2^2) + 24*d_p2*l_1*m_1*x_2 + 72*d_p2*l_1*m_2*x_2 - 24*d_p2*l_1*m_1*x_4 + 72*d_p2*l_1*m_3*x_2 - 72*d_p2*l_1*m_2*x_4 - 72*d_p2*l_1*m_3*x_4 + 36*d_p1*l_2*m_2*x_2*cos(x_1 - x_3) + 36*d_p2*l_2*m_2*x_2*cos(x_1 - x_3) - 36*d_p2*l_2*m_2*x_4*cos(x_1 - x_3) + 18*l_1*l_2*m_2^2*u*cos(x_3) + 18*g*l_1*l_2*m_2^2*sin(x_3) + 9*l_1*l_2^2*m_2^2*x_4^2*sin(2*x_1 - 2*x_3) - 18*l_1*l_2*m_2^2*u*cos(2*x_1 - x_3) - 18*g*l_1*l_2*m_2^2*sin(2*x_1 - x_3) + 3*l_1*l_2*m_1*m_2*u*cos(x_3) + 18*l_1*l_2*m_2*m_3*u*cos(x_3) + 3*g*l_1*l_2*m_1*m_2*sin(x_3) + 18*g*l_1*l_2*m_2*m_3*sin(x_3) - 9*l_1*l_2*m_1*m_2*u*cos(2*x_1 - x_3) - 18*l_1*l_2*m_2*m_3*u*cos(2*x_1 - x_3) - 9*g*l_1*l_2*m_1*m_2*sin(2*x_1 - x_3) - 18*g*l_1*l_2*m_2*m_3*sin(2*x_1 - x_3)))/(l_1*l_2^2*(8*m_1 + 15*m_2 + 24*m_3 - 9*m_2*cos(2*x_1 - 2*x_3))^2), (T_s*(sin(x_1 - x_3)*(72*l_1^2*l_2*m_2^2*x_2 + 24*l_1^2*l_2*m_1*m_2*x_2 + 72*l_1^2*l_2*m_2*m_3*x_2) + 24*d_p2*l_1*m_1 + 72*d_p2*l_1*m_2 + 72*d_p2*l_1*m_3 + 36*d_p1*l_2*m_2*cos(x_1 - x_3) + 36*d_p2*l_2*m_2*cos(x_1 - x_3)))/(l_1*l_2^2*m_2*(8*m_1 + 15*m_2 + 24*m_3 - 9*m_2*cos(2*x_1 - 2*x_3))), (18*T_s*sin(2*x_1 - 2*x_3)*(sin(x_1 - x_3)*(36*l_1^2*l_2*m_2^2*x_2^2 + 12*l_1^2*l_2*m_1*m_2*x_2^2 + 36*l_1^2*l_2*m_2*m_3*x_2^2) + 24*d_p2*l_1*m_1*x_2 + 72*d_p2*l_1*m_2*x_2 - 24*d_p2*l_1*m_1*x_4 + 72*d_p2*l_1*m_3*x_2 - 72*d_p2*l_1*m_2*x_4 - 72*d_p2*l_1*m_3*x_4 + 36*d_p1*l_2*m_2*x_2*cos(x_1 - x_3) + 36*d_p2*l_2*m_2*x_2*cos(x_1 - x_3) - 36*d_p2*l_2*m_2*x_4*cos(x_1 - x_3) + 18*l_1*l_2*m_2^2*u*cos(x_3) + 18*g*l_1*l_2*m_2^2*sin(x_3) + 9*l_1*l_2^2*m_2^2*x_4^2*sin(2*x_1 - 2*x_3) - 18*l_1*l_2*m_2^2*u*cos(2*x_1 - x_3) - 18*g*l_1*l_2*m_2^2*sin(2*x_1 - x_3) + 3*l_1*l_2*m_1*m_2*u*cos(x_3) + 18*l_1*l_2*m_2*m_3*u*cos(x_3) + 3*g*l_1*l_2*m_1*m_2*sin(x_3) + 18*g*l_1*l_2*m_2*m_3*sin(x_3) - 9*l_1*l_2*m_1*m_2*u*cos(2*x_1 - x_3) - 18*l_1*l_2*m_2*m_3*u*cos(2*x_1 - x_3) - 9*g*l_1*l_2*m_1*m_2*sin(2*x_1 - x_3) - 18*g*l_1*l_2*m_2*m_3*sin(2*x_1 - x_3)))/(l_1*l_2^2*(8*m_1 + 15*m_2 + 24*m_3 - 9*m_2*cos(2*x_1 - 2*x_3))^2) - (T_s*(cos(x_1 - x_3)*(36*l_1^2*l_2*m_2^2*x_2^2 + 12*l_1^2*l_2*m_1*m_2*x_2^2 + 36*l_1^2*l_2*m_2*m_3*x_2^2) - 36*d_p1*l_2*m_2*x_2*sin(x_1 - x_3) - 36*d_p2*l_2*m_2*x_2*sin(x_1 - x_3) + 36*d_p2*l_2*m_2*x_4*sin(x_1 - x_3) - 18*g*l_1*l_2*m_2^2*cos(x_3) + 18*l_1*l_2*m_2^2*u*sin(x_3) + 18*l_1*l_2^2*m_2^2*x_4^2*cos(2*x_1 - 2*x_3) - 18*g*l_1*l_2*m_2^2*cos(2*x_1 - x_3) + 18*l_1*l_2*m_2^2*u*sin(2*x_1 - x_3) + 9*l_1*l_2*m_1*m_2*u*sin(2*x_1 - x_3) + 18*l_1*l_2*m_2*m_3*u*sin(2*x_1 - x_3) - 3*g*l_1*l_2*m_1*m_2*cos(x_3) - 18*g*l_1*l_2*m_2*m_3*cos(x_3) + 3*l_1*l_2*m_1*m_2*u*sin(x_3) + 18*l_1*l_2*m_2*m_3*u*sin(x_3) - 9*g*l_1*l_2*m_1*m_2*cos(2*x_1 - x_3) - 18*g*l_1*l_2*m_2*m_3*cos(2*x_1 - x_3)))/(l_1*l_2^2*m_2*(8*m_1 + 15*m_2 + 24*m_3 - 9*m_2*cos(2*x_1 - 2*x_3))), 1 - (T_s*(24*d_p2*l_1*m_1 + 72*d_p2*l_1*m_2 + 72*d_p2*l_1*m_3 + 36*d_p2*l_2*m_2*cos(x_1 - x_3) - 18*l_1*l_2^2*m_2^2*x_4*sin(2*x_1 - 2*x_3)))/(l_1*l_2^2*m_2*(8*m_1 + 15*m_2 + 24*m_3 - 9*m_2*cos(2*x_1 - 2*x_3)))];
C = [1 0 0 0];

%% Discrete Kalman filter measurement update equations
P   = A * P_p * A' + Q;
K   = P * C'/( C * P * C' + R);
x   = x + (K * (y - C * x));
P_p  = (eye(size(A)) - K * C) * P;
x_p  = x;
end