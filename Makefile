all:
	clang -Wall -O4 mathtest.c -o mathtest

clean:
	rm -rf mathtest
