%% Berechnung der Steuerbarkeits- und Beobachterkeitsmatrix, des Rückführvektors und des Beobachters des Inversen Doppelpendels

if ~(exist('m_1', 'var')), syms m_1; end
if ~(exist('m_2', 'var')), syms m_2; end
if ~(exist('m_3', 'var')), syms m_3; end

if ~(exist('l_1', 'var')), syms l_1; end
if ~(exist('l_2', 'var')), syms l_2; end

if ~(exist('d_m', 'var')), syms d_m; end
if ~(exist('dp_1', 'var')), syms dp_1; end
if ~(exist('dp_2', 'var')), syms dp_2; end


%% Berechnung der Hilfsvariablen

J_1 = 1/12*m_1*l_1^2; % Massenträgheitsmoment des 1. Pendelstabs (um den Schwerpunkt)
J_2 = 1/12*m_2*l_2^2; % Massenträgheitsmoment des 2. Pendelstabs (um den Schwerpunkt)

g = 9.81; % Erdbeschleunigung

k1 = -2 / ( l_1^2*(m_1+4*m_2+4*m_3) + 4*J_1 );

k2 = -2 / ( l_2^2*m_2 + 4*J_2 );

k3 = (k1*k2*l_1*l_2*m_2) / (1 - k1*k2*l_1^2*l_2^2*m_2^2);

k4 = k1 / (1 - k1*k2*l_1^2*l_2^2*m_2^2);


%% Anlegen der A-Matrix, des B-Vektors und des C-Vektors

A = [ 0,1,0,0 ;
    3*(-2*l_1*g*m_1*l_2-4*l_1*g*m_2*l_2-4*l_1*g*m_3*l_2)*(1/l_1^2)*(1/l_2)*(1/(-3*m_2-12*m_3-4*m_1)) , 3*(4*dp_1*l_2+6*dp_2*l_1-4*dp_2*l_2)*(1/l_1^2)*(1/l_2)*(1/(-3*m_2-12*m_3-4*m_1)) , 9*g*m_2*(1/l_1)*(1/(-3*m_2-12*m_3-4*m_1)) , 3*(-6*dp_2*l_1+4*dp_2*l_2)*(1/l_1^2)*(1/l_2)*(1/(-3*m_2-12*m_3-4*m_1)) ;
    0,0,0,1 ;
    -3*(-3*g*m_2*m_1*l_2*l_1-6*g*(m_2^2)*l_2*l_1-6*g*m_3*m_2*l_2*l_1)*(1/l_2^2)*(1/l_1)*(1/(-3*m_2-12*m_3-4*m_1))*(1/m_2) , -3*(6*dp_1*m_2*l_2+4*dp_2*m_1*l_1+12*dp_2*m_2*l_1+12*dp_2*m_3*l_1-6*dp_2*m_2*l_2)*(1/l_2^2)*(1/l_1)*(1/(-3*m_2-12*m_3-4*m_1))*(1/m_2) , -3*(2*g*m_2*m_1*l_2*l_1+6*g*(m_2^2)*l_2*l_1+6*g*m_3*m_2*l_2*l_1)*(1/l_2^2)*(1/l_1)*(1/(-3*m_2-12*m_3-4*m_1))*(1/m_2) , -3*(-4*dp_2*m_1*l_1-12*dp_2*m_2*l_1-12*dp_2*m_3*l_1+6*dp_2*m_2*l_2)*(1/l_2^2)*(1/l_1)*(1/(-3*m_2-12*m_3-4*m_1))*(1/m_2) ];

% x und dx als zusätzliche Zustände
A_6 = [ 0,1,0,0,0,0 ;
    6*(m_1+2*m_2+2*m_3)*g/(l_1*(4*m_1+3*m_2+12*m_3)) , 6*(2*dp_2*l_2-3*dp_2*l_1-2*dp_1*l_2)/(l_1^2*l_2*(4*m_1+3*m_2+12*m_3)) , -9*g*m_2/(l_1*(4*m_1+3*m_2+12*m_3)) , 6*dp_2*(3*l_1-2*l_2)/(l_1^2*l_2*(4*m_1+3*m_2+12*m_3)) , 0 , 0 ;
    0,0,0,1,0,0 ;
    -9*g*(m_1+2*m_2+2*m_3)/(l_2*(4*m_1+3*m_2+12*m_3)) , 6*(3*dp_1*m_2*l_2+dp_2*(2*m_1*l_1+6*m_2*l_1+6*m_3*l_1-3*m_2*l_2))/(m_2*l_1*l_2^2*(4*m_1+3*m_2+12*m_3)) , 6*g*(m_1+3*m_2+3*m_3)/(l_2*(4*m_1+3*m_2+12*m_3)) , -6*dp_2*(2*m_1*l_1+6*m_2*l_1+6*m_3*l_1-3*m_2*l_2)/(m_2*l_1*l_2^2*(4*m_1+3*m_2+12*m_3)) , 0 , 0 ;
    0,0,0,0,0,1 ;
    0,0,0,0,0,0 ];

B = [ 0 ;
    (3*(-2*m_1*l_1*l_2-m_2*l_2*l_1-4*m_3*l_1*l_2))/(l_1^2*l_2*(-3*m_2-12*m_3-4*m_1)) ;
    0 ;
    3*m_1/(l_2*(-3*m_2-12*m_3-4*m_1)) ];

% x und dx als zusätzliche Zustände
B_6 = [ 0 ;
    3*(2*m_1+m_2+4*m_3)/(l_1*(4*m_1+3*m_2+12*m_3)) ;
    0 ;
    -3*m_1/(l_2*(4*m_1+3*m_2+12*m_3)) ;
    0 ;
    1 ];

C = [ 1 , 0 , 0 , 0 ]; % nur phi_1 wird gemessen

% x und dx als zusätzliche Zustände
C_6 = [ 1 , 0 , 0 , 0 , 0 , 0 ]; % nur phi_1 wird gemessen


%% Zeitdiskretisierung des Zustandsraummodells

T = 0.001; % 1 Millisekunde als Abtastzeit

Ad = expm(A*T);
A_6d = expm(A_6*T);

fun = @(t) expm( A*(T-t) )*B;
fun_6 = @(t) expm( A_6*(T-t) )*B_6;
Bd = integral(fun,0,T,'ArrayValued',true);
B_6d = integral(fun_6,0,T,'ArrayValued',true);


%% Berechnen der Steuerbarkeitsmatrix, Ausgeben der Determinante und des Ranges

Q_S = [ B_6 , A_6*B_6 , A_6*A_6*B_6 , A_6*A_6*A_6*B_6 , A_6*A_6*A_6*A_6*B_6 , A_6*A_6*A_6*A_6*A_6*B_6 ];

det(Q_S)
rank(Q_S)

%% Berechnen der Beobachtbarkeitsmatrix nach Kalman, Ausgeben der Determinante und des Ranges

Q_B = [ C;
        C*A;
        C*A*A;
        C*A*A*A ];

det(Q_B)
rank(Q_B)

%% Berechnung des Rückführvektors

% zeitkontinuierliche Pole
p   = [-4 -5 -6 -7]*0.8;        % Pole für 4 Systemzustände (ohne Wagen)
p_6 = [-4 -5 -6 -7 -8 -9]*0.8;  % Pole für 6 Systemzustände (mit Wagen)

% Berechnung der Rückführvektoren
K   = place(A,B,p)
K_6 = place(A_6,B_6,p_6);

% Zeitdiskretisierung der Rückführvektoren
Kd   = K
K_6d = K_6;


%% Berechnen des Luenberger-Beobachters

% zeitkontinuierlich
p = 6*p_6(:,1:4);
H = place(A',C',p).'

% zeitdiskret
pd = [exp(p(1)*T) exp(p(2)*T) exp(p(3)*T) exp(p(4)*T)] % (Eigenwerte des geschlossenen, diskretisierten Regelkreises: "eig( expm( (A-H*C)*0.001) )", "exp(p*T)" )
Hd = place(Ad',C',pd).'