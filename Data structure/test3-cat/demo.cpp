#include"utility.h"
#include"Stack.h"
#include"Queue.h"

using namespace std;

void read(Queue<int>&a,int &a_len)
{
    cout<<"number:";
    cin>>a_len;
    if(a_len>0)cout<<"cards:";
    for(int i=1,x;i<=a_len;i++)
    {
        cin>>x;
        if(a.append(x)!=success)error_exit();
    }
}


void judge(const Queue<int>&a,const Queue<int>&b)
{
    if(a.empty()&&b.empty())
    {
        cout<<endl<<"nobody win"<<endl;
        exit(0);
    }
    if(a.empty())
    {
        cout<<endl<<"B win"<<endl;
        exit(0);
    }
    if(b.empty())
    {
        cout<<endl<<"A win"<<endl;
        exit(0);
    }
}


void print(const Stack<int> &river,const Queue<int>&a,const Queue<int>&b)
{
    cout<<"the river:";river.show();
    cout<<"A's hand:";a.show();
    cout<<"B's hand:";b.show();
}


int flag[11];
void work(int a_head,Stack<int> &river,Queue<int>&a)
{
    Error_code stus;
    if(flag[a_head])
    {
        Stack<int> temp;//中转
        Error_code stus;
        int topp;
        stus=temp.push(a_head);
        do
        {
            stus=river.top(topp);//在必定不会出现错误的地方不用判断
            if(temp.push(topp)==overflow)error_exit();
            stus=river.pop();
            flag[topp]=0;
        } while (topp!=a_head);
        while(!temp.empty())
        {
            stus=temp.top(topp);
            stus=temp.pop();
            if(a.append(topp)==overflow)error_exit();
        }
    }
    else 
    {
        if(river.push(a_head)==overflow)error_exit();
        flag[a_head]=1;
    }
}

void solve(Queue<int>&a,Queue<int>&b,int a_len,int b_len)
{
    Stack<int> river;
    judge(a,b);
    while(1)
    {
        int a_head,b_head;Error_code stus;
        
        cout<<endl<<"after A put a card in river :"<<endl;
        stus=a.retrieve(a_head);
        stus=a.serve();
        work(a_head,river,a);
        print(river,a,b);
        judge(a,b);

        cout<<endl<<"after B put a card in river :"<<endl; 
        stus=b.retrieve(b_head);
        stus=b.serve();
        work(b_head,river,b);
        print(river,a,b);
        judge(a,b);
    }
}

int main()
{
    Queue<int>a,b;
    int a_len,b_len;

    cout<<endl<<"A's cards in the beginning"<<endl;
    read(a,a_len);
    cout<<endl<<"B's cards in the beginning"<<endl;
    read(b,b_len);

    solve(a,b,a_len,b_len);
}