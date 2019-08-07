CC = gcc

# This flag includes the Pthreads library on a Linux box.
# Others systems will probably require something different.
LIB = -lpthread

all: serverp client

serverp: serverp.c process.o common.h
	$(CC) -o serverp serverp.c process.o common.h $(LIB)
	
client: client.c common.h
	$(CC) -o client client.c common.h $(LIB)	

echo.o: process.c
	$(CC) -c process.c

clean:
	rm -f *.o serverp client
