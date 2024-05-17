#include <arpa/inet.h>
#include <errno.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

/*
create a server socket and bind to it.
listens on all addresses on specified port,
and accepts specified number of parallel
connections.
*/
int server_create(int port, int connections);
/*
accepts a connection to a server fd,
returned by `server_create`,
returns connection socket fd
*/
int server_accept(int serverfd);

/*
connects to `addr`:`port`
the address is an actual string,
not whatever it is in socket.h
*/
int client_connect(char *addr, int port);
