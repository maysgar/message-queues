all:
	gcc -g -Wall -pthread -c keys.c -lrt
	ar -rv libkeys.a keys.o
	gcc -g -Wall -pthread -o client client.c libkeys.a -lrt
	gcc -g -Wall -pthread -o server server.c -lrt

clean:
	rm -f keys.o
	rm -f client.o
	rm -f server.o
