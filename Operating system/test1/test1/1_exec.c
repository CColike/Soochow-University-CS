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
    printf("CHILD : 当前处于子进程中\n");
    /*调用exec函数族中的execvp函数执行ls指令*/
    char *argv[] = {"ls","-l",NULL};
    if(execvp("ls",argv)==-1) 
    {
      perror("exec出错!");
      exit(-1);
    }
    else exit(0);
  }
  else if(childpid>0)//fork()的返回值是一个新的pid，表示当前在父进程中
  {
    printf("PARENT: 当前处于父进程中\n");
    printf("PARENT: 我现在会等待我的子进程结束\n");
    int status;
    wait(&status);//等待子进程结束运行，并保存其状态
    printf("PARENT: 子进程的返回值为: %d\n",WEXITSTATUS(status));//输出子进程的返回值
    printf("PARENT: 再见！\n");
    exit(0);//父进程退出
  }
  else//fork()返回-1，这表示进程创建失败 
  {
    perror("fork出错");//显示错误信息
    exit(0);
  }
}