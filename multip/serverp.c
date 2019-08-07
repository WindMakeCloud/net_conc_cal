//服务端主程序
//主要负责接收数据，处理后发送给相应的客户端

#include "common.h"

void process(int connfd);

int main(int argc, char **argv)
{
	struct sockaddr_in serverAddr;
	struct sockaddr_in clientAddr;
	socklen_t clientlen;
	int listenfd, connfd;
	char *server_host;
	int server_port;
	char client_hostname[BUF_SIZE], client_port[BUF_SIZE];
	
	if (argc != 3)
	{
		fprintf(stderr, "usage: %s <host> <port>\n", argv[0]);
		exit(0);
	}
	
	server_host = argv[1];
	server_port = atoi(argv[2]);
	
	//读取服务器IP地址和端口号
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr(server_host);
    serverAddr.sin_port = htons(server_port);
	
	//创建监听socket
	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	if (listenfd < 0)
	{
		perror("listenfd create error");
		exit(-1);
	}
	
	//绑定地址
	if (bind(listenfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0)
	{
		perror("bind error");
		exit(-1);
	}
	
	//监听
	if (listen(listenfd, 5) < 0)
	{
		perror("listen error");
		exit(-1);
	}
	
	while (1)
	{
		clientlen = sizeof(struct sockaddr_in);
		connfd = accept(listenfd, (struct sockaddr *)&clientAddr, &clientlen);
		if(connfd < 0)
		{
			perror("accept error");
			exit(-1);
		}
		
		printf("Connected to (%s, %d)\n",
				inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));
		
		if (fork() == 0)
		{
			close(listenfd);      //子进程关闭监听套接字
			process(connfd);      //子进程处理客户数据并发送给客户
			close(connfd);        //子进程关闭和客户的连接
			exit(0);              //子进程退出
		}
		
		close(connfd);            //父进程关闭已连接的套接字(重要!)
	}
}