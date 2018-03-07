
gcc -g -Wall -c keys.c
ar -rv keys.a keys.o
gcc -g -Wall -o client client.c keys.a
gcc -g -Wall -c -o server server.c
