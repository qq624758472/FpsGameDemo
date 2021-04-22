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
#include "ServerConnect.h"
#include "MyDB.h"
using namespace std;


_playerLocation ClientInfo[MAXPEOPLE];

int main(int argc, char *argv[])
{
    //init
    memset(&ClientInfo,0,sizeof(ClientInfo));


#if 0
    //网络链接测试
    ServerConnect serverConnect;
    serverConnect.port = 4399;
    serverConnect.N = 4;
    serverConnect.ServerSocketInit();
#endif

#if 1
    //数据库操作测试
    MyDB db;
    db.initDb("127.0.0.1","root","000000","test");
    db.execSql("select * from player");
#endif
}
