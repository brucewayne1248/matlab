function [ y ] = round2( u, s )
%ROUND2 rounds for a specified number of digits after the comma.
%   e.g. ROUND2(pi, 3) ---> 3.142

%(C) Tobias Plüss

if s >= 0
s = round(s);

factor = 10^s;
tmp = u .* factor;

tmp = round(tmp);

y = tmp ./ factor;
end;
end

