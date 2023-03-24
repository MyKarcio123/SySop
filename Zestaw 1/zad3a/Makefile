CC = gcc
CFALGS = -Wall

all:
	make testCreated
	
	make clean
	make staticCompile
	./main_static < tests > results_static.txt
	
	make clean
	make sharedCompile
	./main_shared < tests > results_shared.txt
	
	make clean
	make dllCompile
	./main_DLL < tests > results_dynamic.txt
	
testCreated:
	echo "init 50" > tests
	echo "count text.txt" >> tests
	echo "count main.c" >> tests
	echo "show 1" >> tests
	echo "show 0" >> tests
	echo "delete 0" >> tests
	echo "show 0" >>tests
	echo "delete 1" >> tests
	echo "destroy" >> tests
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
