#include <math.h>
#include <stdio.h>
#include <string.h>

//TODO:  Make this take arbitrary free length of spring values

//declare constants (should be defines?)
//And yeah, they're global, sue me!

const double d_phi = .001;
const double g = 9.81;
const double r = 4.;
const double l_max = 4.472135955;

double wt(double m, double phi)
{
	//calculate the weight force tangent to circle given m and phi
	return (m*g*cos(phi));
}

double wn(double m, double phi)
{
	//calculate the weight force normal to path given m and phi
	return (m*g*sin(phi));
}

double B(double phi)
{
	//translates phi into B
	return (atan( (2+4*cos(phi))/(4*sin(phi)) ) - ((M_PI_2)-phi));
}

double Fsn(double phi, double k, double l_0)
{
	//Calculates the force of the spring in the normal direction
	return (k*cos(B(phi))*( sqrt(20+16*cos(phi)) - l_0 ));
}

double Fst(double phi, double k, double l_0)
{
	//Calculates the force of the spring in the tangent direction
	return (k*sin(B(phi))*( sqrt(20+16*cos(phi)) - l_0 ));
}

double v(double m, double phi, double v_0, double mu, double k, double l_0)
{
	//Calculates v using the derived equation and requring a negative d_phi
	return (sqrt( ((pow(v_0,2)*m)/(2*r*d_phi)+(wt(m,phi))-(mu*wn(m,phi))-(mu*Fsn(phi,k,l_0))-(Fst(phi,k,l_0)))/((m)/(2*r*d_phi)-(mu*m)/(r)) ));
}

double findFinalV(double k, double m, double mu, double v_0, double l_0)
{
	//Calculates final velocity given the spring force, mass, coefficient
	//of friction and initial velocity

	//theta = phi, just named willy nilly
	double theta = M_PI_2;
	
	while((theta > 0) && !isnan(v_0))
	{
		v_0 = v(m, theta, v_0, mu, k, l_0);
		theta = theta - d_phi;
	}

	return v_0;
}

int main(int argc, char *argv[])
{
	
	double test1 = findFinalV(10.,15.,.1,10.,4.47);
	double test2 = findFinalV(20.,15.,.1,10.,4.47);
	double test3 = findFinalV(20.,20.,.1,10.,4.47);
	double test4 = findFinalV(20.,20.,.2,10.,4.47);
	double test5 = findFinalV(20.,20.,.2,20.,4.47);
	
	printf(" %f %f %f %f %f\n", test1, test2, test3, test4, test5);
	

	double v1m1, v1m2, v2m1, v2m2;
	int k; 
	double mu;
	double m1 = 5;
	double m2 = 10;
	double v1 = 3;
	double v2 = 6;
	double l_0;
	
	for(l_0 = 0; l_0 < l_max; l_0 +=.1)
	{
		for(k = 1; k <= 300; k+=1)
		{
			for(mu=0.001; mu <= 1; mu+=.001)
			{	
				v1m1 = findFinalV((double)k,m1,mu,v1,l_0);
				v1m2 = findFinalV((double)k,m2,mu,v1,l_0);
				v2m1 = findFinalV((double)k,m1,mu,v2,l_0);
				v2m2 = findFinalV((double)k,m2,mu,v2,l_0);
				
				if(!isnan(v1m1))
				{
					printf("l_0 = %f k = %d mu = %f v1m1 = %f v1m2 = %f v2m1 = %f v2m2 = %f\n",l_0,k,mu,v1m1,v1m2,v2m1,v2m2);
				}
			
				if(v1m1 <= 1.5 && !isnan(v1m1) && v1m2 <= 1.5 && !isnan(v1m2) && v2m1 <= 1.5 && !isnan(v2m1) && v2m2 <= 1.5 && !isnan(v2m2))
				{
					printf("\n\n\t\t\tSucesss!     k = %d , mu = %f , l_0 = %f \n\n", k, mu, l_0);
				}

			}
		}
	}
     
	
	return 0;
}

