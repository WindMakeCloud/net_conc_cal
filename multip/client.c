//客户端主程序
//发送需要计算的数据给服务器
//从服务器接收处理后的数据
#include "common.h"

int main(int argc, char **argv)
{
	struct sockaddr_in serverAddr;
	int clientfd;
	char *server_host;
	char buf[BUF_SIZE]; //标准输入读取缓存
	int server_port;
	
	int pid;
	int pipefd[2];
	
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
	
	//创建socket
	clientfd = socket(AF_INET, SOCK_STREAM, 0);
    if (clientfd < 0)
    {
        perror("socket error");
        exit(-1);
    }
	
	//连接服务器
	if (connect(clientfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0)
	{
		perror("connect error");
		exit(-1);
	}
	
	//从标准输入读取字符，发送给服务器
	//从服务器接收字符，给标准输出
	while (fgets(buf, BUF_SIZE, stdin) != NULL)
	{
		send(clientfd, buf, sizeof(buf), 0);
		recv(clientfd, buf, sizeof(buf), 0);
		fputs(buf, stdout);
		printf("\n");
	}
	close(clientfd);
	exit(0);
}