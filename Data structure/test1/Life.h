#include<bits/stdc++.h>
using namespace std;

const int maxrow=20,maxcol=60;

class Life
{
private:
    int grid[maxrow+2][maxcol+2];
    int neighbor_count(int row,int col);
public:
    void initialize();
    void print();
    void update();
};

void Life::initialize()
{
    for(int i=0;i<=maxrow+1;i++)
        for(int j=0;j<=maxcol+1;j++)
            grid[i][j]=0;
    cout<<"List the coordinates for living cells"<<endl;
    cout<<"Terminate the list with special pair(-1,-1):"<<endl;
    int row,col;
    cin>>row>>col;
    while(row!=-1)
    {
        if(row>=1&&row<=maxrow&&col>=1&&col<=maxcol)
                grid[row][col]=1;
        else
            if(!(row>=1&&row<=maxrow))        
                cout<<"row is out of range"<<endl;
            else 
                cout<<"col is out of range"<<endl;
        cin>>row>>col;
    }
}

void Life::print()
{
    cout<<"the current Life configuration is:"<<endl;
    for(int i=1;i<=maxrow;i++)
    {
        for(int j=1;j<=maxcol;j++)
            cout<<grid[i][j];
        cout<<endl;
    }
}

void Life::update()
{
    int new_grid[maxrow+2][maxcol+2],n_c;
    for(int i=1;i<=maxrow;i++)
    {
        for(int j=1;j<=maxcol;j++)
        {
            n_c=neighbor_count(i,j);
            if((n_c==3)||(n_c==2&&grid[i][j]==1))
                new_grid[i][j]=1;
            else 
                new_grid[i][j]=0;
        }
    }
    for(int i=1;i<=maxrow;i++)
    {
        for(int j=1;j<=maxcol;j++)
        {
            grid[i][j]=new_grid[i][j];
        }
    }
}

int Life::neighbor_count(int row,int col)
{
    int cnt=0;
    for(int i=row-1;i<=row+1;i++)
    {
        for(int j=col-1;j<=col+1;j++)
        {
            cnt+=grid[i][j];
        }
    }
    cnt-=grid[row][col];
    return cnt;
}
