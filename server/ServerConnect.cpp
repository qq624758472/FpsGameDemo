
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
using namespace std;

extern _playerLocation ClientInfo[MAXPEOPLE];

ServerConnect::ServerConnect()
{
}

ServerConnect::~ServerConnect()
{
}
/*
fd_set（它比较重要所以先介绍一下）是一组文件描述字(fd)的集合，它用一位来表示一个fd（下面会仔细介绍），对于fd_set类型通过下面四个宏来操作：
FD_ZERO(fd_set *fdset);将指定的文件描述符集清空，在对文件描述符集合进行设置前，必须对其进行初始化，如果不清空，
                        由于在系统分配内存空间后，通常并不作清空处理，所以结果是不可知的。
FD_SET(fd_set *fdset);用于在文件描述符集合中增加一个新的文件描述符。
FD_CLR(fd_set *fdset);用于在文件描述符集合中删除一个文件描述符。
FD_ISSET(int fd,fd_set *fdset);用于测试指定的文件描述符是否在该集合中。
*/
int ServerConnect::ServerSocketInit()
{
    if (N > FD_SETSIZE)
    {
        N = FD_SETSIZE;
    }

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));

    if ((server_sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        cout << "create socket error" << endl;
        exit(-1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(port);

    if (bind(server_sock, (struct sockaddr *)&server_addr, sizeof(sockaddr)) == -1)
    {
        cout << "bind error" << endl;
        exit(-1);
    }

    if (listen(server_sock, 5) == -1)
    {
        cout << "listent error" << endl;
        exit(-1);
    }

    fd_set fd[2];
    FD_ZERO(&fd[0]);
    FD_SET(server_sock, &fd[0]);
    int *sock = new int[N];
    memset(sock, 0, sizeof(int) * N);
    sock[0] = server_sock;
    int count = 0;

    while (1)
    {
        struct timeval tv = {5, 0}; //超时时间。 设置为NULL 表示阻塞。
        FD_ZERO(&fd[1]);
        fd[1] = fd[0];                                                  //select 会清空没有响应的描述符。  所以需要备份一个。
        int ret = select(max_fd(sock, N) + 1, &fd[1], NULL, NULL, &tv); //用来等待文件描述词状态的改变。
        //int ret = select(max_fd(sock, N) + 1, &fd[1], NULL, NULL, NULL); //用来等待文件描述词状态的改变。 1：描述符可读事件。2.可写事件监听。
        if (ret < 0)
        {
            cout << "select error" << endl;
        }
        else if (ret == 0)
        {
            //cout << "time out  ";
        }
        else
        {
            if (FD_ISSET(sock[0], &fd[1]) && count < N - 1)
            {
                struct sockaddr_in client_addr;
                memset(&client_addr, 0, sizeof(client_addr));
                unsigned int len = sizeof(client_addr);
                int new_sock = accept(sock[0], (struct sockaddr *)&client_addr, &len);
                if (new_sock == -1)
                {
                    cout << "accept error" << endl;
                }
                else
                {
                    for (int i = 1; i < N; i++)
                    {
                        if (sock[i] == 0)
                        {
                            sock[i] = new_sock;
                            FD_SET(new_sock, &fd[0]);
                            count++;
                            cout << "new connect success!\n";
                            break;
                        }
                    }
                }
            }
            playerLocation clientPosion;
            char recvbuf[1024] = {0};
            char sendbuf[1024] = {0};
            //int nNetTimeout=1000;//1秒，设置接收超时时间。
            //setsockopt(socket,SOL_SOCKET,SO_RCVTIMEO,(char *)&nNetTimeout,sizeof(int));
            for (int i = 1; i < N; i++)
            {
                if (FD_ISSET(sock[i], &fd[1]))
                {
                    int tmp = recv(sock[i], recvbuf, sizeof(recvbuf), 0);
                    if (tmp < 0)
                    {
                        cout << "recv error" << endl;
                        perror("recv error code:");
                        FD_CLR(sock[i], &fd[0]);
                        close(sock[i]);
                        sock[i] = 0;
                        count--;
                        continue;
                    }
                    else if (tmp == 0)
                    {
                        /* code */
                        //perror("error code:");
                        cout << "recv = 0\n";
                        FD_CLR(sock[i], &fd[0]);
                        close(sock[i]);
                        sock[i] = 0;
                        count--;
                        continue;
                    }
                    else
                    {
                        //成功获取客户端位置，然后打印出来。
                        memcpy(&clientPosion, recvbuf, strlen(recvbuf));
                        if (clientPosion.x > 0 && clientPosion.x < 0.001)
                            clientPosion.x = 0.0;
                        if (clientPosion.z > 0 && clientPosion.z < 0.001)
                            clientPosion.z = 0.0;
                        cout << "clientPosion: x:" << clientPosion.x << "   z:" << clientPosion.z << endl;
                        // //说明有人在移动， 将该位置同步到其他所有客户端中。
                        for (int j = 1; j < N; j++)
                        {
                            if (j == i)
                                continue;
                            strcpy(sendbuf, recvbuf);
                            if (sock[j] != 0)  //只给有效的socket发送位置消息。
                            {
                                tmp = send(sock[j], sendbuf, sizeof(sendbuf), 0);
                                if (tmp <= 0)
                                {
                                    cout << "send error" << endl;
                                    perror("send error code:");
                                    FD_CLR(sock[j], &fd[0]);
                                    close(sock[j]);
                                    sock[j] = 0;
                                    count--;
                                    continue;
                                }
                                else
                                {
                                }
                            }
                        }
                    }
                }
            } //end for
        }
    } //end while
    return 1;
}

int ServerConnect::max_fd(int a[], int n)
{
    int max = 0;
    for (int i = 0; i < n; i++)
    {
        if (max < a[i])
        {
            max = a[i];
        }
    }

    return max;
}