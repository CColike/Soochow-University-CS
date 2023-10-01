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
    cout<<"请输入人数和关系数：";
    cin>>n>>m;
    memset(dis,inf,sizeof(dis));
    cout<<"请依次输入每条关系:"<<endl;
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
    cout<<"请输入你的询问数"<<endl;
    cin>>m;
    cout<<"请依次输入每个询问："<<endl;
    for(int i=1;i<=m;i++)
    {
        int x,y;
        cin>>x>>y;
        if(dis[x][y]==inf)cout<<"他们不可能认识"<<endl;
        else if(x==y)cout<<"人总是认识他们自己的"<<endl;
        else if(dis[x][y]==1)cout<<"他们之间有联系"<<endl;
        else cout<<"至少需要经过"<<dis[x][y]-1<<"人，他们才能构成联系"<<endl;
    }
}