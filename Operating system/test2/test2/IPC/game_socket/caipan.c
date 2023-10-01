#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<signal.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main()
 {
     int server_sockfd = -1;
     int client_sockfd1 = -1;
     int client_sockfd2= -1;
     int client_len1 = 0;
     int client_len2 = 0;
     struct sockaddr_in server_addr;
     struct sockaddr_in client_addr1;
     struct sockaddr_in client_addr2;
     char game1;
     char game2;
     int count=0;
     int result;
     char ch='H';
     

     server_sockfd = socket(AF_INET,SOCK_STREAM,0);

     server_addr.sin_family = AF_INET;
     server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
     server_addr.sin_port = htons(9736);

     bind(server_sockfd,(struct sockaddr*)&server_addr,sizeof(server_addr));

     listen(server_sockfd, 100);

     signal(SIGCHLD, SIG_IGN);

   
         client_len1= sizeof(client_addr1);
         client_len2= sizeof(client_addr2);
         printf("Server waiting\n");

         client_sockfd1 =accept(server_sockfd,(struct sockaddr*)&client_addr1,&client_len1);
         client_sockfd2 =accept(server_sockfd,(struct sockaddr*)&client_addr2,&client_len2);
            for(int i=0;i<=100;i++)
            {
          
                read(client_sockfd2,&game2,1);
                read(client_sockfd1,&game1,1);
                
                sleep(3);
                if(game1==game2)
                {
                    ch='D';
                }
                if( (game1=='2'&&game2=='1')||(game1=='1'&&game2=='0')||(game1=='0'&&game2=='2'))
                {
                    ch='W';
                }
                if((game2=='2'&&game1=='1')||(game2=='1'&&game1=='0')||(game2=='0'&&game1=='2'))
                {
                    ch='L';
                }
                printf("game1:%c\n",game1);
                printf("game2:%c\n",game2);
                printf("%c\n",ch);
                write(client_sockfd1,&ch,1);
                write(client_sockfd2,&ch,1);
             } close(client_sockfd1);
                close(client_sockfd2);
                exit(0);
            
            /*else
            {
                /*close(client_sockfd1);
                close(client_sockfd2);
            }*/
            
 }  