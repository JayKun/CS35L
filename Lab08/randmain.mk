OPTIMIZE = -O2
CFLAGS = $(OPTIMIZE) -g3 -Wall -Wextra -march=native -mtune=native -mrdrnd

randlibsw.so: randlibsw.o
	gcc $(CFLAGS) -shared -o randlibsw.so randlibsw.o

randlibhw.so: randlibhw.o
	gcc $(CFLAGS) -shared -o randlibhw.so randlibhw.o

randlibsw.o: randlibsw.c
	gcc $(CFLAGS) -fPIC -c randlibsw.c -o randlibsw.o

randlibhw.o: randlibhw.c
	gcc $(CFLAGS) -fPIC -c randlibhw.c -o randlibhw.o

randcpuid.o: randcpuid.c
	gcc $(CFLAGS) -c randcpuid.c -o randcpuid.o

randmain.o: randmain.c
	gcc $(CFLAGS) -c randmain.c -o randmain.o

randmain:randmain.o randcpuid.o randlibsw.so randlibhw.so
	gcc $(CFLAGS) randmain.o randcpuid.o -ldl -Wl,-rpath=$PWD -o randmain
