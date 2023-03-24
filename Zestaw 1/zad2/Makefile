CC = gcc
CFALGS = -Wall

all:
	make staticCompile
	make sharedCompile
	make dllCompile
	
staticCompile: lib.o
	ar rcs liblib.a lib.o
	${CC} ${CFLAGS} main.c -o main_static -L. -llib

sharedCompile: lib.o
	${CC} ${CFLAGS} -shared -fPIC -o liblib.so lib.o
	${CC} ${CFLAGS} main.c -o main_shared -L. -llib -Wl,-rpath=`pwd`

dllCompile: lib.o
	${CC} ${CFLAGS} -shared -fPIC -o liblib.so lib.o
	${CC} ${CFLAGS} main.c -o main_DLL -L. -ldl -D DLL
	
lib.o: lib.c
	${CC} ${CFLAGS} -c lib.c
	
clean:
	rm -rf *o *a
