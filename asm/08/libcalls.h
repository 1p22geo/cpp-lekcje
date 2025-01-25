#include <fcntl.h>
// it's not even linked, just for the bitfields and flags

void _print(char *x, unsigned long len);
void _sys_exit(unsigned long code);
void _sys_close(unsigned int fd);

int _sys_write(unsigned int fd, char *x, unsigned long len);
int _sys_read(unsigned int fd, char *x, unsigned long len);

int _sys_open(char *path, int flags);
