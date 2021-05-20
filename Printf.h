
#define LEN 1024
#define BLEN 4096

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory>
#include <stdarg.h>
#include <ctime>

#include <errno.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>


int Printf(int fd, const char *format, ...);
int Readf(int fd, char *buf);


