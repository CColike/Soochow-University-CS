#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
#define N 1000
using namespace std;

int n,m;
int dis[N][N];

void spfa()
{
    for(int k=1;k<=n;k++)
    {
        for(int i=1;i<=n;i++)
        {
            for(int j=1;j<=n;j++)
            {
                dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
            }
        }
    }
}


int main()
{
    cout<<"�����������͹�ϵ����";
    cin>>n>>m;
    memset(dis,inf,sizeof(dis));
    cout<<"����������ÿ����ϵ:"<<endl;
    for(int i=1;i<=m;i++)
    {
        int x,y;
        cin>>x>>y;
        dis[x][y]=1;
        dis[y][x]=1;
    }
    for(int i=1;i<=n;i++)
        dis[i][i]=0;
    spfa();
    cout<<"���������ѯ����"<<endl;
    cin>>m;
    cout<<"����������ÿ��ѯ�ʣ�"<<endl;
    for(int i=1;i<=m;i++)
    {
        int x,y;
        cin>>x>>y;
        if(dis[x][y]==inf)cout<<"���ǲ�������ʶ"<<endl;
        else if(x==y)cout<<"��������ʶ�����Լ���"<<endl;
        else if(dis[x][y]==1)cout<<"����֮������ϵ"<<endl;
        else cout<<"������Ҫ����"<<dis[x][y]-1<<"�ˣ����ǲ��ܹ�����ϵ"<<endl;
    }
}