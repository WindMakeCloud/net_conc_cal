//服务端数据处理函数

#include "common.h"

void process(int connfd)
{
	int recv_num, send_num;
	char temp_buf[BUF_SIZE];
	size_t n;
	char recv_buf[BUF_SIZE], send_buf[BUF_SIZE];
	
	while (1)
	{
		//接收数据
		bzero(recv_buf, BUF_SIZE);
		int len = recv(connfd, recv_buf, BUF_SIZE, 0);
		
		//处理数据
		recv_num = atoi(recv_buf);
		printf("recevied num: %d\n", recv_num);
		send_num = recv_num + 1;
		
		//以字符串形式写入temp_buf
		bzero(temp_buf, BUF_SIZE);
		sprintf(temp_buf, "%d", send_num);
		
		//发送数据
		bzero(send_buf, BUF_SIZE);
		memcpy(send_buf, temp_buf, sizeof(temp_buf));
		send(connfd, send_buf, sizeof(send_buf), 0);
	}
}