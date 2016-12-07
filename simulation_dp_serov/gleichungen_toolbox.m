% Gleichungen in Vektor Schreibweise
[x_2;
    
1/(l_1^2*(9*cos(x_1-x_3)^2*m_2-4*m_1-12*m_2-12*m_3)*l_2)*(9*x_2^2*cos(x_1-x_3)*sin(x_1-x_3)*l_1^2*l_2*m_2+6*m_2*l_1*l_2^2*sin(x_1-x_3)*x_4^2+9*u*cos(x_1-x_3)*cos(x_3)*l_1*l_2*m_2+9*cos(x_1-x_3)*sin(x_3)*g*l_1*l_2*m_2-6*l_1*cos(x_1)*u*m_1*l_2-12*l_1*cos(x_1)*u*m_2*l_2-12*l_1*cos(x_1)*u*m_3*l_2-6*l_1*g*sin(x_1)*m_1*l_2-12*l_1*g*sin(x_1)*m_2*l_2-12*l_1*g*sin(x_1)*m_3*l_2+18*x_2*cos(x_1-x_3)*d_p2*l_1-18*x_4*cos(x_1-x_3)*d_p2*l_1+12*x_2*d_p1*l_2+12*x_2*d_p2*l_2-12*d_p2*x_4*l_2);

x_4;

-1/(l_1*l_2^2*(9*cos(x_1-x_3)^2*m_2-4*m_1-12*m_2-12*m_3)*m_2)*(12*x_2*d_p2*l_1*m_1+36*x_2*d_p2*l_1*m_2+36*x_2*d_p2*l_1*m_3-12*x_4*d_p2*l_1*m_1-36*x_4*d_p2*l_1*m_2-36*x_4*d_p2*l_1*m_3-9*cos(x_1)*u*cos(x_1-x_3)*l_1*l_2*m_1*m_2-18*cos(x_1)*u*cos(x_1-x_3)*l_1*l_2*m_2*m_3-9*cos(x_1-x_3)*sin(x_1)*g*l_1*l_2*m_1*m_2-18*cos(x_1-x_3)*sin(x_1)*g*l_1*l_2*m_2*m_3+9*x_4^2*cos(x_1-x_3)*sin(x_1-x_3)*l_1*l_2^2*m_2^2+ 6*x_2^2*sin(x_1-x_3)*l_1^2*l_2*m_1*m_2+ 18*x_2^2*sin(x_1-x_3)*l_1^2*l_2*m_2*m_3-18*cos(x_1)*u*cos(x_1-x_3)*l_1*l_2*m_2^2-18*cos(x_1-x_3)*sin(x_1)*g*l_1*l_2*m_2^2 +6*u*cos(x_3)*l_1*l_2*m_1*m_2+18*u*cos(x_3)*l_1*l_2*m_2*m_3+6*sin(x_3)*g*l_1*l_2*m_1*m_2+18*sin(x_3)*g*l_1*l_2*m_2*m_3 + 18*(x_2)^2*sin(x_1-x_3)*l_1^2*l_2*m_2^2+18*u*cos(x_3)*l_1*l_2*m_2^2+18*sin(x_3)*g*l_1*l_2*m_2^2+18*x_2*cos(x_1-x_3)*d_p1*l_2*m_2 + 18*x_2*cos(x_1-x_3)*d_p2*l_2*m_2-18*x_4*cos(x_1-x_3)*d_p2*l_2*m_2)];

%% Diese Matrix sollte prinzipiell keinen Einfluss auf die Toolbox haben
C1 = [1 0 0 0]; % nur phi1 wird dem EKF zur Verfügung gestellt
C2 = [1 0 0 0; 0 1 0 0]; % phi1 und dphi1 wird dem EKF zur Verfügung gestellt
                         % falls das möglich ist da dphi1, kein Ausgang des
                         % Systems
% Parametervektor
[g l_1 l_2 m_1 m_2 m_3 d_p1 d_p2];