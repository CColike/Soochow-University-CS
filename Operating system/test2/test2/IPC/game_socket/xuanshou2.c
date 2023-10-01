#include<stdlib.h>
#include<time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
 
int main()
{
  int sockfd2 =-1;
  char game2;
  int len = 0;
  char ch='A';
  struct sockaddr_in address;
  int result;
  srand((unsigned)time(NULL));


  sockfd2 = socket(AF_INET, SOCK_STREAM, 0);
  address.sin_family = AF_INET;//使用网络套接字
	address.sin_addr.s_addr = inet_addr("127.0.0.1");//服务器地址
	address.sin_port = htons(9736);//服务器所监听的端口
	len = sizeof(address);

  result = connect(sockfd2, (struct sockaddr*)&address, len);

  if(result == -1)
	{
		perror("ops:client\n");
		exit(1);
	}
  for (int i=0;i<=100;i++){
    game2=rand()%3+'0';
  write(sockfd2, &game2, 1);
	//从服务器获取数据
	read(sockfd2, &ch, 1);
	printf("result form server = %c\n", ch);
  printf("game2 form server = %c\n", game2);}
	close(sockfd2);
	exit(0);
}
