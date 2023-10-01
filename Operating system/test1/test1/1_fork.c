#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<errno.h>
#include<sys/wait.h>
#include<stdlib.h>

int main()
{
   /*创建一个新进程*/
   pid_t childpid=fork();
   if(childpid==0)//fork()的返回值为0，表示当前在子进程中
   {
      printf("CHILD : 我是子进程\n");
      printf("CHILD : 子进程的pid为: %d\n", getpid());   //输出当前进程pid
      printf("CHILD : 我的父进程的pid为: %d\n", getppid()); //输出当前进程的父进程的pid
      printf("CHILD : fork()的返回值是: %d\n",childpid); //输出fork()的返回值
      printf("CHILD : 睡眠一秒\n");
      sleep(1);   //让进程睡眠一秒
      printf("CHILD : 输入一个返回值(0~255): ");
      int retval;
      scanf("%d",&retval); //输入子进程完成后的返回值
      printf("CHILD : 再见！\n");
      exit(retval);  //子进程退出，返回值为用户给定的返回值
   }
   else if(childpid>0)  //fork()的返回值是一个新的pid，表示当前在父进程中
   {
      printf("PARENT: 我是父进程\n");
      printf("PARENT: 父进程的pid为: %d\n",getpid()); //输出当前进程的pid
      printf("PARENT: 我的子进程的pid为: %d \n",childpid);  //输出当前进程的子进程的pid
      printf("PARENT: 我现在会等待我的子进程结束\n");
      int status;
      wait(&status); //等待子进程结束运行，并保存其状态
      printf("PARENT: 子进程的返回值为: %d\n",WEXITSTATUS(status));  //输出子进程的返回值
      printf("PARENT: 再见！\n");
      exit(0); //父进程退出
   }
   else  //fork()返回-1，这表示进程创建失败 
   {
      perror("fork出错");  //显示错误信息
      exit(0);
   }
}