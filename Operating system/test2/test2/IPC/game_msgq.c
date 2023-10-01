#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <sys/wait.h>

struct Game 
{
    int Round;
    long Type;
};

void result_send(int msgid)     //利用消息机制发送随机的出拳信息
{
    struct Game game;
    game.Type = 1;
    game.Round = rand() % 3;
    msgsnd(msgid, &game, sizeof(int), 0);
}
int judge(int a, int b)    //判断输赢
{
    if (a == b)     //draw
        return 0;    
    else if ((a==0&&b==1)||(a==1&&b==2)||(a==2&&b==0))   //A win
        return -1;    
    else        //B win
        return 1;    
}
void writeFile(int *result_list, int len)   //保存结果至result.txt
{
    int A_win = 0; 
    int B_win = 0;
    int draw=0;
    FILE *fin;
    if( (fin = fopen( "result.txt", "w" )) == NULL )  //文件打开失败
    {
        fprintf(stderr, "This file wasn't opened" );
        exit(EXIT_FAILURE);
    }
    
    for (int i = 0; i < len ; i++)  //查看每次猜拳结果并写入至控制台与txt中
    {
        if(result_list[i]==-1)
        {
            A_win++;
            fprintf(fin, "ROUND.%d:A win\n", i + 1);
            printf("ROUND.%d:A win\n", i + 1);
        }
        else if(result_list[i]==0)
        {
            draw++;
            fprintf(fin, "ROUND.%d:end in a draw\n", i + 1);
            printf("ROUND.%d:end in a draw\n", i + 1);
        }
        else
        {
            B_win++;
            fprintf(fin, "ROUND.%d:B win\n", i + 1);
            printf("ROUND.%d:B win\n", i + 1);
        }
    }
    printf("\nThe final result:\n A win:%d \n B win:%d \n end in a draw:%d\n",A_win,B_win,draw);
    fprintf(fin, "\nThe final result:\n A win:%d \n B win:%d \n end in a draw:%d\n",A_win,B_win,draw);
    fclose(fin);
}
int main()
{
    int  key1 = 1111, key2 = 2222, *result_list, times;
    pid_t  pid1, pid2;  

    int msgid1,msgid2;
    /*创建消息队列*/
    msgid1 = msgget(key1, IPC_CREAT | 0666); 
    msgid2 = msgget(key2, IPC_CREAT | 0666); 
    if(msgid2 == -1 || msgid2 == -1) //创建消息通道失败
    {
        fprintf(stderr, "failed with msgget error!");
        exit(EXIT_FAILURE);
    }
    printf("Game start,please input rounds:");
    scanf("%d", &times);
    result_list=(int*)malloc(times*sizeof(int));
    for (int i = 0; i < times; i++)
    {
        pid1 = fork();   //创建选手1
        if (pid1 == 0) 
        {
            srand((unsigned)time(0) * 3000 ); 
            result_send(msgid1);  //生成选手1的出拳信息并发送到信息队列
            exit(-1);
        }
        pid2 = fork();   //创建选手2
        if (pid2 == 0) 
        {
            srand((unsigned)time(NULL)*i );
            result_send(msgid2);  //生成选手2的出拳信息并发送到信息队列
            exit(-1);
        }

        if (pid1 < 0 || pid2 < 0)  //存在某个进程创建失败
        {
            fprintf(stderr, "Fork Failed");
            exit(-1);
        }
        else  //在主进程中
        {
            wait(NULL);//等待两个孩子优先
            wait(NULL);
            struct Game game1;
            struct Game game2;
            msgrcv(msgid1, &game1, sizeof(game1) - sizeof(long), 0, 0);//从消息队列读取消息
            msgrcv(msgid2, &game2, sizeof(game2) - sizeof(long), 0, 0); 
            result_list[i] = judge(game1.Round, game2.Round);
        }
    }
    //将比赛结果写入文件
    writeFile(result_list, times);
    //删除消息队列
    if (msgctl(msgid1, IPC_RMID, 0) == -1 || msgctl(msgid2, IPC_RMID, 0) == -1)
    {
        fprintf(stderr, "msgctl(IPC_RMID) failed\n");
        exit(EXIT_FAILURE);
    }
        
    exit(EXIT_SUCCESS);
}

