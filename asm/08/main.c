#include "libcalls.h"
#include "server.h"

void handle_connection(int client_fd) {

  char *b;
  char *b2;
  int content_len = 0;
  char data[4096];
  char response[4096];

  int fd = _sys_open("index.html", O_RDONLY);
  content_len = _sys_read(fd, data, 4096);

  char *begin =
      "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nServer: "
      "ASSEMBLY YEEAAAA\r\nConnection: Closed\r\nContent-Length: \x00";
  b = begin;
  b2 = response;
  while (*b != '\x00') {
    *b2 = *b;
    b++;
    b2++;
  }

  int a = content_len;
  int content_length_length = 0;

  while (a != 0) {
    a -= a % 10;
    a /= 10;
    content_length_length++;
  }
  a = content_len;

  b2 += content_length_length;

  int counter = 1;

  while (a != 0) {
    *(b2 - counter) = a % 10 + 0x30;
    a -= a % 10;
    a /= 10;
    counter++;
  }

  // I don't give a shit.
  *b2 = '\r';
  b2++;
  *b2 = '\n';
  b2++;
  *b2 = '\r';
  b2++;
  *b2 = '\n';
  b2++;

  for (int i = 0; i < content_len; i++) {
    *b2 = data[i];
    b2++;
  }

  int res_length = b2 - response;

  _print(response, res_length);

  _sys_write(client_fd, response, res_length);

  _sys_close(client_fd);

  return;
}

void _start() {
  create_server(8080, &handle_connection);

  _print("helo\n", 5);

  _sys_exit(0);
}
