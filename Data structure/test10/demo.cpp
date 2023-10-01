#include<bits/stdc++.h>
using namespace std;

int a[10][10];
vector<pair<int,int>>ans;

void create()
{
    ans.clear();
    srand((int)time(0));
    for(int i=1;i<=8;i++)
    {
        for(int j=1;j<=8;j++)
        {
            a[i][j]=rand()%2;
        }
    }
    for(int i=0;i<=9;i++)
    {
        a[i][0]=1;
        a[0][i]=1;
        a[9][i]=1;
        a[i][9]=1;
    }
    a[1][1]=a[8][8]=0;
}

void show_arr()
{
    cout<<"the aray is:\n";
    for(int i=1;i<=8;i++)
    {
        for(int j=1;j<=8;j++)
        {
            cout<<a[i][j]<<' ';
        }
        cout<<endl;
    }
}

bool judge(int x,int y)
{
    // cout<<x<<' '<<y<<endl;
    if(x==8&&y==8)return true;
    a[x][y]=1;
    for(int dx=-1;dx<=1;dx++)
    {
        for(int dy=-1;dy<=1;dy++)
        {
            if(!(a[x+dx][y+dy]))
            {
                if(judge(x+dx,y+dy))
                {
                    ans.push_back(make_pair(x,y));
                    return true;
                }
            }
        }
    }
    return false;
}

void show_ans()
{
    int len=ans.size();
    if(!len)
    {
        cout<<"there is no way to the final(7,7)";
        return;
    }
    cout<<"there exist ways to the final(7,7):\n(0,0)\n";
    for(int i=len-1;i>=0;i--)
    {
        cout<<"("<<ans[i].first-1<<','<<ans[i].second-1<<")"<<endl;
    }
    cout<<"(7,7)\n";
}


int main()
{
    create();
    show_arr();
    judge(1,1);
    // show();    
    show_ans();
    // cout<<ans.size()<<endl;
}