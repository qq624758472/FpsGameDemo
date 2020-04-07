
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
using namespace std;


//该结构体发送的是玩家位置。
typedef struct _OtherPlayerlocation
{
    float x; //x轴世界坐标。
    float z; //y轴世界坐标。
}OtherPlayerlocation;



class ServerConnect
{
public:
    ServerConnect();
    ~ServerConnect();


    int port = 0;  //端口号。
    int N = 0;     //连接数。

    int server_sock = 0;


    int ServerSocketInit();    
    int max_fd(int a[], int n);
};

