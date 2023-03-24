CC=gcc
CFLAGS=-Wall

all:
	make lib_static
	make lib_shared
	
lib_static: lib.c
	${CC} ${CFLAGS} -c lib.c
	ar rcs lib.a lib.o
	
lib_shared: lib.c
	${CC} ${CFLAGS} -c -fPIC lib.c
	${CC} -shared -o lib.so lib.o
clean:
	rm -rf *o *a
