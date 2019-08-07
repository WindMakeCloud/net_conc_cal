//服务端主程序
//主要负责接收数据，处理后发送给相应的客户端

#include "common.h"

void process(int connfd);
void *thread(void *vargp);

int main(int argc, char **argv)
{
	struct sockaddr_in serverAddr;
	struct sockaddr_in clientAddr;
	socklen_t clientlen;
	int listenfd, *connfdp;
	pthread_t tid;
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
		connfdp = malloc(sizeof(int));
		*connfdp = accept(listenfd, (struct sockaddr *)&clientAddr, &clientlen);
		if(*connfdp < 0)
		{
			perror("accept error");
			exit(-1);
		}
		
		printf("Connected to (%s, %d)\n",
				inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));
		
		pthread_create(&tid, NULL, thread, connfdp);
	}
	//close(listenfd);
}

void *thread(void *vargp)
{
	int connfd = *((int *)vargp);
	pthread_detach(pthread_self());
	free(vargp);
	process(connfd);
	close(connfd);
	return NULL;
}