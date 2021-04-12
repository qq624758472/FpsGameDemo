#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/time.h>
#include <string.h>
#include <sys/select.h>
#include <pthread.h>
#include "ClientConnect.h"
using namespace std;

int main(int argc, char *argv[])
{
    ClientConnect test;
    test.port = 4399;
    test.ClientConnectInit();
}
