
k = 100;
m1 = 5;
m2 = 10;
v1 = 3;
v2 = 6;
k = 200;
mu = 1;
v1m1 = v1m2 = v2m1 = v2m2 = 100;

while isreal(v1m1) != 1 || v1m1 > 1.5 || isreal(v1m2) != 1 || v1m2 > 1.5 || isreal(v2m1) != 1 || v2m1 > 1.5 || isreal(v2m2) != 1 || v2m2 > 1.5
	k = k - .05;
	v1m1 = findFinalV(k,m1,mu,v1);
	v1m2 = findFinalV(k,m2,mu,v1);
	v2m1 = findFinalV(k,m1,mu,v2);
	v2m2 = findFinalV(k,m2,mu,v2);
	fprintf(".")
end

fprintf("%.10f",k);
