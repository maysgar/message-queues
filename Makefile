all:
	gcc -g -Wall -c -o keys keys.c 
	ar -rv libkeys.a keys.o
	gcc -g -Wall -o client client.c libkeys.a
	gcc -g -Wall -c -o server server.c

clean:
	rm -f keys.o
	rm -f client.o
	rm -f server.o