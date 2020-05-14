CC=gcc
CFLAGS= -g -Wall -D_LINUX 
OBJS=hello.o
all: ${OBJS}
	    ${CC}  ${CFLAGS}  -o hello.exe  ${OBJS}
		    rm -fr *.o

hello.o : hello.c
	    ${CC}  ${DBG} ${CFLAGS}  ${INCLUDE}  -c hello.c
clean: rm -rf hello.exe *.o

