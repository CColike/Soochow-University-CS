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
  int sockfd1 =-1;
  char game1;
  int len = 0;
  struct sockaddr_in address;
  int result;
  char ch='A';
  srand((unsigned)time(NULL));
 

  sockfd1 = socket(AF_INET, SOCK_STREAM, 0);
  address.sin_family = AF_INET;
	address.sin_addr.s_addr = inet_addr("127.0.0.1");
	address.sin_port = htons(9736);
	len = sizeof(address);

  result = connect(sockfd1, (struct sockaddr*)&address, len);

  if(result == -1)
	{
		perror("ops:client\n");
		exit(1);
	}
  for (int i=0;i<=100;i++){
    game1=rand()%3+'0';
  write(sockfd1, &game1, 1);

	read(sockfd1, &ch, 1);
	printf("result form server = %c\n",ch);
  printf("game1 form server = %c\n",game1);}
	close(sockfd1);
	exit(0);
}
