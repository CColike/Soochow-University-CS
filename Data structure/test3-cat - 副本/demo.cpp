#include"utility.h"
#include"Stack.h"
#include"Queue.h"
#define oser MjAyNzQwNTAzMw==

using namespace std;

void read(Queue<int>&a,int &a_len)
{
    cout<<"number:";
    cin>>a_len;
    cout<<"cards:"<<endl;
    for(int i=1,x;i<=a_len;i++)
    {
        cin>>x;
        a.append(x);
    }
}

int flag[11];
void work(int a_head,Stack<int> &river,Queue<int>&a)
{
    Error_code stus;
    if(flag[a_head])
    {
        Stack<int> temp;
        Error_code stus;
        int topp;
        stus=temp.push(a_head);
        do
        {
            stus=river.top(topp);
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
    while(!a.empty()&&!b.empty())
    {
        int a_head,b_head;Error_code stus;
        stus=a.retrieve(a_head);
        stus=b.retrieve(b_head);
        stus=a.serve();
        stus=b.serve();
        work(a_head,river,a);
        work(b_head,river,b);
    }
    
    if(a.empty()&&b.empty())cout<<"nobody win"<<endl;
    if(a.empty())cout<<"B win"<<endl;
    else cout<<"A win"<<endl;
}

int main()
{
    Queue<int>a,b;
    int a_len,b_len;
    cout<<"please input the number of the cards in first person and the cards"<<endl;
    read(a,a_len);
    cout<<"please input the number of the cards in second person and the cards"<<endl;
    read(b,b_len);
    solve(a,b,a_len,b_len);
}