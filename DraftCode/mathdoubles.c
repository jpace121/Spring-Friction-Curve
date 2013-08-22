#include <math.h>
#include <stdio.h>

//TODO:  Make this take arbitrary free length of spring values

//declare constants (should be defines?)
//And yeah, they're global, sue me!

const double d_phi = .0001;
const double g = 9.81;
const double r = 4;

double wt(double m, double phi)
{
	//calculate the weight force tangent to circle given m and phi
	double wt = m*g*cos(phi);
	return wt;
}

double wn(double m, double phi)
{
	//calculate the weight force normal to path given m and phi
	double wn = m*g*sin(phi);
	return wn;
}

double B(double phi)
{
	//translates phi into B
	double B = atan( (2+4*cos(phi))/(4*sin(phi)) ) - ((M_PI_2)-phi);
	return B;
}

double Fsn(double phi, double k)
{
	//Calculates the force of the spring in the normal direction
	double Fsn = k*cos(B(phi))*( sqrt(20+16*cos(phi)) - sqrt(20) );
	return Fsn;
}

double Fst(double phi, double k)
{
	//Calculates the force of the spring in the tangent direction
	double Fst = k*sin(B(phi))*( sqrt(20+16*cos(phi)) - sqrt(20) );
	return Fst;
}

double v(double m, double phi, double v_0, double mu, double k)
{
	//Calculates v using the derived equation and requring a negative d_phi
	double v = sqrt( ((pow(v_0,2)*m)/(2*r*d_phi)+(wt(m,phi))-(mu*wn(m,phi))-(mu*Fsn(phi,k))-(Fst(phi,k)))/((m)/(2*r*d_phi)-(mu*m)/(r)) ); 
	return v;
}

double findFinalV(double k, double m, double mu, double v_0)
{
	//Calculates final velocity given the spring force, mass, coefficient
	//of friction and initial velocity

	//theta = phi, just named willy nilly
	double theta = M_PI_2;
	
	while(theta > 0)
	{
		v_0 = v(m, theta, v_0, mu, k);
		theta = theta - d_phi;
	}

	return v_0;
}

int main()
{

	double test1 = findFinalV(100,15,.2,10);
	double test2 = findFinalV(200,15,.2,10);
	double test3 = findFinalV(200,20,.2,10);
	double test4 = findFinalV(200,20,.3,10);
	double test5 = findFinalV(200,20,.3,20);
	
	printf(" %f %f %f %f %f\n", test1, test2, test3, test4, test5);

	/*
	double v1m1, v1m2, v2m1, v2m2;
	double k, mu;
	double m1 = 5;
	double m2 = 10;
	double v1 = 3;
	double v2 = 6;
	
	for(k=0; k <= 1000000; k+=1)
	{
		printf("New K = %f\n",k);
		for(mu=0; mu <= 1; mu+=.0001)
		{
			v1m1 = findFinalV(k,m1,mu,v1);
			v1m2 = findFinalV(k,m2,mu,v1);
			v2m1 = findFinalV(k,m1,mu,v2);
			v2m2 = findFinalV(k,m2,mu,v2);

			if(v1m1 <= 1.5 && !isnan(v1m1) && v1m2 <= 1.5 && !isnan(v1m2) && v2m1 <= 1.5 && !isnan(v2m1) && v2m2 <= 1.5 && !isnan(v2m2))
			{
				printf("Sucesss!     k = %f , mu = %f\n", k, mu);
			}

		}
	}
	*/
	
	return 0;
}

