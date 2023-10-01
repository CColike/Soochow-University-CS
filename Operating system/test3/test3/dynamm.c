#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 640

struct node  //定义分区
{
  int address, size;
  struct node *next;
};
typedef struct node RECT;

/*-----函数定义-------*/
RECT *assignment(RECT *head,int application); //分配分区
void firstfit(RECT *head,RECT *heada,RECT *back1); //针对首次适应分配算法回收分区
void bestfit(RECT *head,RECT *heada,RECT *back1);  //针对最佳适应分配算法回收分区
int backcheck(RECT *head,RECT *back1); //合法性检查
void print(RECT *head);   //输出已分配分区表或空闲分区
/*-----变量定义-------*/
RECT *head,*heada,*back,*assign1,*p;
int application1,maxblocknum;
char way;  //用于定义分配方式：首先适应、最佳适应、最差适应等，目前未使用
int main()
{
  char choose;
  int check;
  RECT *allocated;
  head=malloc(sizeof(RECT)); //建立空闲分区表的初始状态
  p=malloc(sizeof(RECT));
  head->size=MAX;
  head->address=0;
  head->next=p;
  maxblocknum=1;
  p->size=MAX;
  p->address=0;
  p->next=NULL;
  print(head);  //输出空闲分区表的初始状态
  printf("Enter the way (best or first (b/f))\n");
  scanf("%c",&way);
  heada=malloc(sizeof(RECT)); //建立已分配分区表的初始状态
  heada->size=0;
  heada->address=0;
  heada->next=NULL;
  //print(heada);  //输出空闲分区表的初始状态
  //way='f';
  do
  {     
    printf("Enter the allocate or reclaim (a/r),or press other key to exit.\n"); 
    scanf(" %c",&choose);     //选择分配或回收       
    if(tolower(choose)=='a')                 //a为分配
    {
      printf("Input application:\n");
      scanf("%d",&application1);              //输入申请空间大小
      assign1=assignment(head,application1);  //调用分配函数分配内存
      if (assign1->address==-1)               //分配不成功
        printf("Too large application! Allocation fails! \n\n");
      else                                    //分配成功
        printf("Allocation Success! ADDRESS=%5d\n",assign1->address);
      printf("\n*********Unallocated Table*************\n");
      print(head);  //输出
      printf("\n*********Allocated Table***  **********\n");
      print(heada);
    }
    else if (tolower(choose)=='r')          //回收内存
    {
      back=malloc(sizeof(RECT));
      printf("Input address and Size:\n");
      scanf("%d%d",&back->address,&back->size);//输入回收地址和大小
      check=backcheck(head,back);
      if (check==1)
      {
        if(tolower(way)=='f')
          firstfit(head,heada,back);    //首先适应算法回收
        else
          bestfit(head,heada,back);
        printf("\n*********Unallocated Table*************\n");
        print(head);  //输出
        printf("\n*********Allocated Table***  **********\n");
        print(heada);
       }
    }
  }while(tolower(choose)=='a'||tolower(choose)=='r');
  exit(0);
} //main() end.

/*-------内存分配函数-------*/
RECT *assignment(RECT *head,int application)
{
  RECT *after,*before,*assign;
  assign=malloc(sizeof(RECT));     //申请分配空间
  assign->size=application;
  assign->next=NULL;
  if(application>head->size || application<0)
    assign->address=-1;            //申请无效
  else
  {
    before=head;
    after=head->next;
    while(after->size < application)//遍历链表，查找合适到节点
    {
      before=before->next;
      after=after->next;
    }
    if(after->size==application)    //若节点大小等于申请大小则完全分配
    {
      if(after->size==head->size) maxblocknum--;
      before->next=after->next;
      assign->address=after->address;
      free(after);
    }
    else
    {
      if(after->size==head->size) maxblocknum--;
      after->size=after->size-application; //大于申请空间则截取相应大小分配
      assign->address=after->address+after->size;
    }
    if (maxblocknum==0)    //修改最大数和头节点
    {
      before=head;
      head->size=0;
      maxblocknum=1;
      while(before!=NULL)
      {
        if(before->size > head->size)
        {
          head->size=before->size;
          maxblocknum=1;
        }
        else if(before->size==head->size)
          maxblocknum++;
        before=before->next;
      }
    }
  }
  assign1=assign;
  
  //修改已分配分区表，添加节点
  after=heada;
  while(after->next!=NULL)
    after=after->next;
  after->next=assign;
  heada->size++;

  return assign1;    //返回分配给用户到地址
}

/*------------------首先适应分配算法------------*/
void firstfit(RECT *head,RECT *heada,RECT *back1)
{
  RECT *before,*after,*back2;
  int insert,del;
  back2=malloc(sizeof(RECT));
  back2->address=back1->address;
  back2->size=back1->size;
  back2->next=back1->next;
  before=head;
  after=head->next;
  insert=0;
  while(!insert)      //将回收区插入空闲区表
  {
    if((after==NULL)||((back1->address<=after->address)&&(back1->address>=before->address)))
    {
      before->next=back1;
      back1->next=after;
      insert=1;
    }
    else
    {
      before=before->next;
      after=after->next;
    }
  } 

  if(back1->address==before->address+before->size) //与上一块合并
  {
    before->size=before->size+back1->size;
    before->next=back1->next;
    free(back1);
    back1=before;
  }

  if((after!=NULL) &&(after->address==back1->address+back1->size))//与下一块合并
  {
    back1->size=back1->size+after->size;
    back1->next=after->next;
    free(after);
  }

  if(head->size<back1->size) //修改最大块值和最大块个数
  {
    head->size=back1->size;
    maxblocknum=1;
  }
  else 
    if(head->size==back1->size) maxblocknum++;

  //修改已分配分区表，删除相应节点
  before=heada;
  after=heada->next;
  del=0;
  while(!del||after!=NULL)  //将回收区从已分配分区表中删除
  {
    if((after->address==back2->address)&&(after->size==back2->size))
    {
      before->next=after->next;
      free(after);
      del=1;
    }
    else
    {
      before=before->next;
      after=after->next;
    }
  }
  heada->size--;
}

/*-----------------最佳适应分配算法,back1为回收节点到地址--------------*/
void bestfit(RECT *head,RECT *heada,RECT *back1)
{
  RECT *before,*after,*back2;
  int insert=0,del;
  back2=malloc(sizeof(RECT));
  back2->address=back1->address;
  back2->size=back1->size;
  back2->next=back1->next;
  before=head;
  after=head->next;
  if(head->next==NULL)
  {
    head->size=back1->size;
    head->next=back1;
    maxblocknum++;
    back1->next=NULL;
  }
  else
  {
    while(after!=NULL)
     if(back1->address==after->size+after->address) /*与上一块合并*/
     {
       before->next=after->next;
       back->size=after->size+back1->size;
       free(after);
       after=NULL;
     }
     else
     {
       after=after->next;
       before=before->next;
     }
     before=head;
     after=head->next;
     while(after!=NULL)
      if(after->address==back1->size+back1->address)   /*与下一块合并*/
      {
        back1->size=back1->size+after->size;
        before->next= after->next;
        free(after);
        after=NULL;
      }
      else
      {
        before=before->next;
        after=after->next;
      }
      before=head;                 /*将回收节点插入到合适到位置*/
      after=head->next;
      do{
        if(after==NULL||(after->size>back1->size))
        {
          before->next=back1;
          back1->next=after;
          insert=1;
        }
        else
        {
          before=before->next;
          after=after->next;
        }
      }while(!insert);
      if(head->size<back1->size)    /*修改最大块值和最大块数*/
      {
        head->size=back1->size;
        maxblocknum++;
      }
      else
      {
        if(head->size==back1->size)
          maxblocknum++;
       }
  }

  //修改已分配分区表，删除相应节点
  before=heada;
  after=heada->next;
  del=0;
  while(!del||after!=NULL)  //将回收区从已分配分区表中删除
  {
    if((after->address==back2->address)&&(after->size==back2->size))
    {
      before->next=after->next;
      free(after);
      del=1;
    }
    else
    {
      before=before->next;
      after=after->next;
    }
  }
  heada->size--;
}

        
/*-----------------打印输出链表--------------*/
void print(RECT *output)
{
  RECT *before;
  int index;
  before=output->next;
  index=0;
  if(output->next==NULL)
    printf("NO part for print!\n");
  else
  {
    printf("index****address****end*****size**** \n");
    while(before!=NULL)
    {
      printf("------------------------------------\n");
      printf(" %-9d%- 9d%- 9d%- 9d\n",index,before->address,before->address+before->size-1,before->size);
      printf("-------------------------------------\n");
      index++;
      before=before->next;
    }
  }
}

/*检查回收块到合法性，back1为要回收到节点地址*/
int backcheck(RECT *head,RECT *back1)
{
  RECT *before;
  int check=1;
  if(back1->address<0 || back1->size<0) check=0;  //地址和大小不能为负数
  before=head->next;
  while((before!=NULL)&&check) //地址不能和空闲区表中节点出现重叠
  if(((back1->address<before->address)&&(back1->address+back1->size>before->address))||((back1->address>=before->address)&&(back1->address<before->address+before->size)))
    check=0;
  else
    before=before->next;
  if(check==0) printf("Error input!\n");
  return check;     
}
