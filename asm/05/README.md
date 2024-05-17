# Simple example of socket programming using the `mysocket` library.

## Building and running

This code requires the `mysocket` or `libmysocket.so` and `libmysocket.h` library.
To build and run it refer to [example 06](../06/README.md)

```shell
make all
./server # will start a server, run it in the background if possible
./client 127.0.0.1 # will connect to the server, run while the server is running
```
