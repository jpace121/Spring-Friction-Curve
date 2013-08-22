
k = 100000;
m1 = 5;
m2 = 10;
v1 = 3;
v2 = 6;
mu = .25;
v1m1 = v1m2 = v2m1 = v2m2 = 100;

while (isreal(v1m1) == 0) || (v1m1 > 1.5) || (isreal(v1m2) == 0) || (v1m2 > 1.5) || (isreal(v2m1) == 0) || (v2m1 > 1.5) || (isreal(v2m2) == 0) || (v2m2 > 1.5)
	k = k - 10;
	v1m1 = findFinalV(k,m1,mu,v1);
	v1m2 = findFinalV(k,m2,mu,v1);
	v2m1 = findFinalV(k,m1,mu,v2);
	v2m2 = findFinalV(k,m2,mu,v2);
	fprintf(".")
end

fprintf("Success! %.10f",k);
