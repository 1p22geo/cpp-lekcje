#include "mysockets.h"

int client_connect(char *addr, int port) {
  int sockfd = 0;
  struct sockaddr_in serv_addr;

  /* a socket is created through call to socket() function */
  if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    printf("\n Error : Could not create socket \n");
    return 1;
  }

  memset(&serv_addr, '0', sizeof(serv_addr));

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(port);

  if (inet_pton(AF_INET, addr, &serv_addr.sin_addr) <= 0) {
    printf("\n inet_pton error occured\n");
    return 1;
  }

  /* Information like IP address of the remote host and its port is
   * bundled up in a structure and a call to function connect() is made
   * which tries to connect this socket with the socket (IP address and port)
   * of the remote host
   */
  if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
    printf("\n Error : Connect Failed \n");
    return 1;
  }
  return sockfd;
}
