#!/usr/bin/env python

from __future__ import division
from numpy import *

#v0 is v_i-1
#v is v_i
#phi is in radians

d_theta = .001
g = 9.81
r = 4.
k=2.
m=10.
mu = .3
v0 = 6.
theta = pi/2

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
    b = arctan( (2+4*cos(phi))/(4*sin(phi)) ) - ((pi/2)-phi)
    return b

def Fsn(phi,k,B):
    """The force of the spring in the normal direction"""
    f = k*cos(B(phi))*( sqrt(20+16*cos(phi)) - sqrt(20) )
    return f

def Fst(phi,k,B):
    """The force of the spring in the tangent direction"""
    f = k*sin(B(phi))*( sqrt(20+16*cos(phi)) - sqrt(20) )
    return f

v = lambda phi, v_0: sqrt( (wt(m,g,phi)-(m*v_0**2)/(2*r*d_theta)+mu*(Fsn(phi,k,B)-wn(m,g,phi)-Fst(phi,k,B)))/((m*mu)/(r)-(m)/(2*r*d_theta)) )


# ##Find Final Velocity from given parameters##


while theta > 0: 
    v0 = v(theta, v0)
    theta=theta-d_theta
    
print v0

