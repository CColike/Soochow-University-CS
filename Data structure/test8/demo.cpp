#include<bits/stdc++.h>
using namespace std;

struct node
{
    int x;
    int y;
}a[10020];

int n,l,ans=0x3f3f3f3f,tag[10020];

const int island[9]={7,7,7,6,6,5,4,2};
vector<int> ans_arr,path;

bool check(int k,int i)
{
    if(tag[i])return false;
    if(!k)
    {
        if(abs(a[i].x)>7&&abs(a[i].y)>7)return false;
        if(abs(a[i].x)<=7)if(abs(a[i].y)<=abs(island[abs(a[i].x)]+l))return true;
        if(abs(a[i].y)<=7)if(abs(a[i].x)<=abs(island[abs(a[i].y)]+l))return true;
        return false;
    }
    else
    {
        if((a[k].x==a[i].x&&abs(a[k].y-a[i].y)<=l)||(a[k].y==a[i].y&&abs(a[k].x-a[i].x)<=l))
            return true;
        else 
            return false;
    }
}

void search(int k,int cnt)
{
    if(k==n+1)
    {
        if(ans>cnt)
        {
            ans_arr=path;
            ans=cnt;
        }
        return;
    }
    tag[k]=1;path.push_back(k);
    for(int i=1;i<=n+1;i++)
    {
        // cout<<i<<endl;
        if(check(k,i))
            search(i,cnt+1);
    }
    tag[k]=0;path.pop_back();
}

int main()
{
    memset(tag,0,sizeof(tag));
    ans_arr.clear();
    path.clear();
    cout<<"请输入鳄鱼个数与James Bond可以跳的最大距离（中间以空格隔开）："<<endl;
    cin>>n>>l;
    a[0].x=0;a[0].y=0;
    a[n+1].x=50;a[n+1].y=50;
    cout<<"请输入各个鳄鱼的坐标："<<endl;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i].x;
        cin>>a[i].y;
    }
    search(0,0);
    if(ans==0x3f3f3f3f)cout<<"can't escape!";
    else 
    {
        cout<<"最短路径长度为：";
        cout<<ans<<endl;
        cout<<"最优路径为"<<endl;
        for(int i=0;i<ans-1;i++)
        {
            cout<<"第"<<i+1<<"步：("<<a[ans_arr[i]].x<<','<<a[ans_arr[i]].y<<")--->("<<a[ans_arr[i+1]].x<<','<<a[ans_arr[i+1]].y<<")\n";
        }
        cout<<"第"<<ans<<"步：("<<a[ans_arr[ans-1]].x<<','<<a[ans_arr[ans-1]].y<<")--->(50,50)\n";
    }
    
}   