all:
	clang -Wall mathtest.c -o mathtest

clean:
	rm -rf mathtest
