#include "mysockets.h"

int server_create(int port, int connections) {

  int listenfd = 0;
  struct sockaddr_in serv_addr;

  char sendBuff[1025];

  /* creates an UN-named socket inside the kernel and returns
   * an integer known as socket descriptor
   * This function takes domain/family as its first argument.
   * For Internet family of IPv4 addresses we use AF_INET
   */
  listenfd = socket(AF_INET, SOCK_STREAM, 0);
  memset(&serv_addr, '0', sizeof(serv_addr));
  memset(sendBuff, '0', sizeof(sendBuff));

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  serv_addr.sin_port = htons(port);

  /* The call to the function "bind()" assigns the details specified
   * in the structure 『serv_addr' to the socket created in the step above
   */
  int b = bind(listenfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
  if (b) {
    return -1;
  }

  /* The call to the function "listen()" with second argument as 10 specifies
   * maximum number of client connections that server will queue for this
   * listening socket.
   */
  listen(listenfd, connections);
  return listenfd;
}

int server_accept(int listenfd) {
  return accept(listenfd, (struct sockaddr *)NULL, NULL);
}
