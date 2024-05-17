#include <libmysockets/libmysockets.h>

int main(int argc, char *argv[]) {

  const char sendBuf[] = "Hello world!";

  int server = server_create(5000, 10);

  while (1) {
    int fd = server_accept(server);
    write(fd, sendBuf, sizeof sendBuf);
    close(fd);
  }
}
