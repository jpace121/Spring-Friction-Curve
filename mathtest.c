/*
	mathtest.c - a program to solve the design problem given by Dr. Moore
	             summer of 2013.

	Authors: Group 4:  Jane Bartley, Chad Harrel, James Pace

*/

/* TODO:
	* Instead of throwing every value where l_0 is greater than length at a 
	  in Fsn, only throw away points at which l_0 is greater than the 
	  length at that point.  Requires changes in the v loop function.
	* I'm still betting there are even dumber mistakes, especially made when I 
	  started getting desperate and when I started applying the advice given 
	  on the last Thursday which I only sort of understood.
	
*/


#include <stdio.h>
#include <math.h>
#include "mathtest.h"

//declare global constants constants (should be defines?)
//M_PI and M_PI_2 defined in math.h (atleast on OSX)

const double d_phi = .001;
const double g = 9.81;
const double r = 4.;
const double l_max = 6.;
const double l_atA = 4.472135955;

int main(int argc, char *argv[])
{
	/*quickly run 5 values teting to see what happens when each variable
	  is incremented (for testing and verification purposes)*/
	double test1 = findFinalV(10.,15.,.1,10.,4.47);
	double test2 = findFinalV(20.,15.,.1,10.,4.47);
	double test3 = findFinalV(20.,20.,.1,10.,4.47);
	double test4 = findFinalV(20.,20.,.2,10.,4.47);
	double test5 = findFinalV(20.,20.,.2,20.,4.47);
	
	printf(" %f %f %f %f %f\n", test1, test2, test3, test4, test5);
	
	//declare variables needed for the massive loop of evil...
	double v1m1, v1m2, v2m1, v2m2;
	int k; 
	double mu;
	double m1 = 5;
	double m2 = 10;
	double v1 = 3;
	double v2 = 6;
	double l_0;
	
	/* Massive loop starts by looping through possible free spring lengths,
	   mainly because I was freaking out when everything wasn't working and
	   was hoping something cool would happen.
	   The l_max limit is the max length at which the spring would still be
	   pulling, and that wouldn't void our FBD */
	for(l_0 = 0; l_0 < l_max; l_0 +=.5)
	{
		/* We're looking for a range of k's so duh it increments. The max
		   value is slightly arbitrary, but based on the values gotten
		   with the free length being at a, 500 is also really high anyway */
		for(k = 1; k <= 500; k+=1)
		{
			/* mu goes from almost zero to 1., which is pretty high
			   for coefficient of *kinetic* friction */
			for(mu=0.001; mu <= 1.; mu+=.001)
			{	
				/* find all the values at all combinations of extreme 
				velocities and masses, probably could have only tested 
				the lowest and highest values, but plenty fast already */
				v1m1 = findFinalV((double)k,m1,mu,v1,l_0);
				v1m2 = findFinalV((double)k,m2,mu,v1,l_0);
				v2m1 = findFinalV((double)k,m1,mu,v2,l_0);
				v2m2 = findFinalV((double)k,m2,mu,v2,l_0);
				
				/* Print values calculated for debugging purposes.  The !isnan
				   statement throws out the lowest enrgy situations that don't 
				   make it, so I don't have to look at them */
				if(!isnan(v1m1))
				{
					printf("l_0 = %f k = %d mu = %f v1m1 = %f v1m2 = %f" 
					        "v2m1 = %f v2m2 = %f\n",l_0,k,mu,v1m1,v1m2,v2m1,
							v2m2);
				}

				/* Prints values for a "successful" run.  Success defined as all
				   packages have v_fs as less than 1.5 m/s and all packages 
				   make it (aka have non imaginary/nan values. */
			
				if(v1m1 <= 1.5 && !isnan(v1m1) && v1m2 <= 1.5 && !isnan(v1m2) 
				   && v2m1 <= 1.5 && !isnan(v2m1) && v2m2 <= 1.5 && 
				   !isnan(v2m2))
				{
					printf("\n\n\t\t\tSucesss!     k = %d , mu = %f , l_0 = %f" 
					        "\n\n", k, mu, l_0);
				}

			}
		}
	}
     
	
	return 0;
}

double findFinalV(double k, double m, double mu, double v_0, double l_0)
{
	/* Calculates final velocity given the spring force, mass, coefficient
	   of friction and initial velocity */

	//theta = phi, just named willy nilly
	double theta = M_PI_2;
	
	//Define the normal force as a valid value so the while loop works
	double Norm = 1.;
	
	/* Run a loop incrementing the theta values and putting in the the velocity
	   d_phi away back into the equation and calculating the next one.
	   This basically integrates the v equation and is the secret suace to the
	   whole procdure.

	   The !isnan test stops the loop as soon as it is clear the package
	   wouldn't make it.  nan values are the result of a sqrt(-something) and
	   indicates the package wouldn't make it.  By stopping the loop as soon
	   as it is clear the package wouldn't make it, the whole program runs
	   faster.  I cut something like 30 seconds off the run with some test 
	   constraints 
	   
	   The Norm being greater than zero throws out values where the block would
	   leave the track*/
	   
	while((theta > 0) && !isnan(v_0) && (Norm >=0))
	{
		v_0 = v(m, theta, v_0, mu, k, l_0);
		Norm = N(m,theta,k,l_0,v_0);
		theta = theta - d_phi;
	}

	if(Norm >= 0)
	{
		/* If Norm is greater than zero, than the loop ended ok, and
		   the package didn't leave the track, so that's good and we can
		   return a valid v_0 */
		return v_0;
	}
	else
	{
		return (0./0.);  //equivalent to return NAN
	}

	return v_0;
}

double v(double m, double phi, double v_0, double mu, double k, double l_0)
{
	/* Calculates the velocity at a point given the velocity d_phi away 
	   from the point we care about. Derivation explained in lab report. 
	*/ 
	return sqrt(((2*r*d_phi)/m)*(wt(m,phi)-Fst(phi,k,l_0)-mu*wn(m,phi)
	       -mu*Fsn(phi,k,l_0)+((mu*m*pow(v_0,2))/(r))
		   +(m*pow(v_0,2)/(2*r*d_phi))));
}

double wt(double m, double phi)
{
	/* Calculate the weight force tangent to circle given m and phi (the angle
	   between horizontal and r */
	return (m*g*cos(phi));
}

double wn(double m, double phi)
{
	/* Calculate the weight force normal to path given m and phi (the angle
	   between horizontal and r */
	return (m*g*sin(phi));
}

double B(double phi)
{
	/* Translates angle phi into angle B, whcih is used to projec the force
	   of the psring to the normal and tangential directions */
	return (atan( (2+4*cos(phi))/(4*sin(phi)) ) - ((M_PI_2)-phi));
}

double Fsn(double phi, double k, double l_0)
{
	//Calculates the force of the spring in the normal direction
	
	/* If the initial length is greater than the length at point a, and 
	   if Hooke's law was true than the spring would be pushing and 
	   invalidate our FBD, so we throw those values away.
	*/
	if(l_0 > l_atA)  
	{
		return 0;
	}
	else
	{
		return (k*cos(B(phi))*( sqrt(20+16*cos(phi)) - l_0 ));
	}
}

double Fst(double phi, double k, double l_0)
{
	//Calculates the force of the spring in the tangent direction
	/* See function mathtest.c:Fsn(double,double,double) for detailed
	   explanation */
	if(l_0  > l_atA)
	{
		return 0;
	}
	else
	{
		return (k*sin(B(phi))*( sqrt(20+16*cos(phi)) - l_0 ));
	}
}

double N(double m, double phi, double k, double l_0, double v)
{
	//Calculates the normal force under a specific circumstance
	return (wn(m,phi)+Fsn(phi,k,l_0)-(m*pow(v,2))/r);
}


