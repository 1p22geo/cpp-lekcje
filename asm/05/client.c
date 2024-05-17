#include <libmysockets/libmysockets.h>
#include <stdio.h>

#define BUFSIZE 1024

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("\n Usage: %s <ip of server> \n", argv[0]);
    return 1;
  }

  int fd = client_connect(argv[1], 5000);

  char *buff = malloc(BUFSIZE);
  memset(buff, 0x00, BUFSIZE);

  read(fd, buff, 1024);

  printf("%s", buff);

  close(fd);

  return 0;
}
