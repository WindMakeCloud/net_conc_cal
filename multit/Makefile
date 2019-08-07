CC = gcc

# This flag includes the Pthreads library on a Linux box.
# Others systems will probably require something different.
LIB = -lpthread

all: servert client

servert: servert.c process.c
	$(CC) -o servert servert.c process.c $(LIB)
	
client: client.c
	$(CC) -o client client.c $(LIB)	

clean:
	rm -f *.o servert client
