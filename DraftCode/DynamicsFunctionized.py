#!/usr/bin/env python

from __future__ import division
from scipy import *
import numpy 

#Global Constants

d_theta = .001
g = 9.81
r = 4.

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

def findVelocity(k,m,mu,v0):
	"""Find Velocity given the spring constant, the mass of the package, the 
	frictional coefficient and the inital velocity""" 
	v = lambda phi, v_0: sqrt( (wt(m,g,phi)-(m*v_0**2)/(2*r*d_theta)+mu*(Fsn(phi,k,B)-wn(m,g,phi)-Fst(phi,k,B)))/((m*mu)/(r)-(m)/(2*r*d_theta)) )

	theta = pi/2
	while theta > 0:
		v0 = v(theta, v0)
		theta=theta-d_theta

	return  v0

def main():
	mu = .3
	m1 = 5
	m2 = 10
	v1 = 3
	v2 = 6
	k = 500 
	v1m1 = v1m2 = v2m1 = v2m2  = nan 

	while type(v1m1) is numpy.complex128 or v1m1 > 1.5 or type(v1m2) is \
	numpy.complex128 or v1m2 >1.5 or type(v2m1) is numpy.complex128 or v2m1 \
	> 1.5 or type(v2m2) is numpy.complex128  or v2m2 >1.5:
		k = k + 10
		v1m1 = findVelocity(k,m1,mu,v1)
		v1m2 = findVelocity(k,m2,mu,v1)
		v2m1 = findVelocity(k,m1,mu,v2)
		v2m2 = findVelocity(k,m2,mu,v2)
		print '.',

	print
	print k

if __name__ == '__main__':
	main()
