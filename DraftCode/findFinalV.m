function [ v_0 ] = findFinalV(k, m, mu, v_0)
%findFinalV(k,m,mu,v_0)
%   Takes spring constant, mass, coefficient of friction and initial velocity

%define constants
d_phi = -.001;
g = 9.81;
r = 4 ;

%define anonymous functions that the larger velocity equation deoends on

wt = @(m, g, phi) m*g*cos(phi);
wn = @(m, g, phi) m*g*sin(phi); 
B = @(phi) atan( (2+4*cos(phi))/(4*sin(phi)) ) - ((pi/2)-phi);
Fsn = @(phi,k,B) k*cos(B(phi))*( sqrt(20+16*cos(phi)) - sqrt(20) );
Fst = @(phi,k,B) k*sin(B(phi))*( sqrt(20+16*cos(phi)) - sqrt(20) );

%define v
v = @(phi, v_0) sqrt( (wt(m,g,phi)-(m*v_0^2)/(2*r*d_phi)-mu*(Fsn(phi,k,B)+wn(m,g,phi))-Fst(phi,k,B))/((m*mu)/(r)-(m)/(2*r*d_phi)) );

%calculate the real v final by moving? out v
theta = pi/2;

while theta > 0
    v_0 = v(theta, v_0);
    theta = theta+d_phi;

end



end

