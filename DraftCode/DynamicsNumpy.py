#!/usr/bin/env python

from __future__ import division
from numpy import *
from sympy import *

init_printing()

#v0 is v_i-1
#v is v_i
#phi is in radians

d_theta = .001
g = 9.81
r = 4 
v_0, m, phi, mu, k = var('v_0 m phi mu k')

def wt(m, g, phi):
    """Calculate the weight force in the tangent direction."""
    w = m*g*cos(phi)
    return w

def wn(m,g,phi):
    """Calculate the weight force in the normal direction"""
    w = m*g*sin(phi)
    return w

def B(phi):
    """The angle beta, in terms of phi"""
    b = atan( (2+4*cos(phi))/(4*sin(phi)) ) - ((pi/2)-phi)
    return b

def Fsn(phi,k,B):
    """The force of the spring in the normal direction"""
    f = k*cos(B(phi))*( sqrt(20+16*cos(phi)) - sqrt(20) )
    return f

def Fst(phi,k,B):
    """The force of the spring in the tangent direction"""
    f = k*sin(B(phi))*( sqrt(20+16*cos(phi)) - sqrt(20) )
    return f

v = sqrt( (wt(m,g,phi)-(m*v_0**2)/(2*r*d_theta)+mu*(Fsn(phi,k,B)-wn(m,g,phi)-Fst(phi,k,B)))/((m*mu)/(r)-(m)/(2*r*d_theta)) )

print v

# ##Find Final Velocity from given parameters##

v0 = 6
theta = pi/2
v = v.subs(k,500).subs(m,10).subs(mu,.2)

while theta > 0: 
    v0 = v.subs(phi,theta).subs(v_0,v0)
    theta=theta-d_theta
    
print v0
