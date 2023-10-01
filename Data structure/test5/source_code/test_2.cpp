#include<bits/stdc++.h>
#include<windows.h>
using namespace std;

vector <int> a;
// int b[10000000];

void search_ShunXu(const vector<int> &a,int n,int m,int &success,int &failure,int &sum_success_time,int &sum_failure_time,double &sum_success_clock,double &sum_failure_clock)
{
    success=0;failure=0;//找到和没找到次数
    sum_success_time=0;sum_failure_time=0;//对比次数
    sum_success_clock=0;sum_failure_clock=0;//时间
    LARGE_INTEGER t1,t2,tc;

    for(int i=1;i<=m;i++)
    {
        int target=rand()%n,j=1;

        QueryPerformanceFrequency(&tc);
        QueryPerformanceCounter(&t1);
        for(j=1;j<=n;j++)
        {
            if(a[j]==target)
                break;
        }
        QueryPerformanceCounter(&t2);

        if(j<n+1)
        {
            success++;
            sum_success_time+=j;
            sum_success_clock+=(double)(t2.QuadPart-t1.QuadPart)/(double)tc.QuadPart;
        }
        else
        {
            failure++;
            sum_failure_time+=n;
            sum_failure_clock+=(double)(t2.QuadPart-t1.QuadPart)/(double)tc.QuadPart;
        }
    }

}

void search_ErFen(const vector<int> &a,int n,int m,int &success,int &failure,int &sum_success_time,int &sum_failure_time,double &sum_success_clock,double &sum_failure_clock)
{
    success=0;failure=0;//找到和没找到次数
    sum_success_time=0;sum_failure_time=0;//对比次数
    sum_success_clock=0;sum_failure_clock=0;//时间
    LARGE_INTEGER t1,t2,tc;
    
    for(int i=1;i<=m;i++)
    {
        int target=rand()%n,l=1,r=n,mid,ans=-1,cnt=0;
        QueryPerformanceFrequency(&tc);
        QueryPerformanceCounter(&t1);
        while(l<=r)
        {
            cnt++;
            mid=(l+r)/2;
            if(a[mid]<=target)
            {
                ans=mid;
                l=mid+1;
            }
            else
            {
                r=mid-1;
            }
        }
        QueryPerformanceCounter(&t2);
        if(a[ans]==target)
        {
            success++;
            sum_success_time+=cnt;
            sum_success_clock+=(double)(t2.QuadPart-t1.QuadPart)/(double)tc.QuadPart;
        }
        else
        {
            failure++;
            sum_failure_time+=cnt;
            sum_failure_clock+=(double)(t2.QuadPart-t1.QuadPart)/(double)tc.QuadPart;
            // if(b[target])cout<<"wa!!"<<endl;
        }
    }


}


void print(const int &n,const int &m,int &success,int &failure,int &sum_success_time,int &sum_failure_time,double &sum_success_clock,double &sum_failure_clock)
{
    cout<<"在长为"<<n<<"的表，共"<<m<<"次查找中："<<endl;
    cout<<"     共有"<<success<<"次成功查询"<<endl;
    cout<<"     平均每次成功查找需要"<<(sum_success_time*1.0)/(success*1.0)<<"次比较"<<endl;
    // printf("%.20f\n",sum_success_clock);
    printf("     平均每次查找耗时%.20f秒\n",sum_success_clock/(success*1.0));
    printf("     成功查找总耗时%.20f秒\n\n",sum_success_clock);
    cout<<"     共有"<<failure<<"次失败查询"<<endl;
    cout<<"     平均每次失败查找需要"<<(sum_failure_time*1.0)/(failure*1.0)<<"次比较"<<endl;
    // printf("%.20f\n",sum_failure_clock);
    printf("     平均每次查找耗时%.20f秒\n",sum_failure_clock/(failure*1.0));
    printf("     失败查找总耗时%.20f秒\n",sum_failure_clock);
    printf("          算法总耗时%.20f秒\n\n",sum_success_clock+sum_failure_clock);
}


int main()
{
    a.push_back(0);
    int n,m;
    cout<<"请输入n：";cin>>n;
    cout<<"请输入m：";cin>>m;
    /*生成排序的随机数列*/
    for(int i=1;i<=n;i++)
    {
        int r=rand()%n;
        a.push_back(r);
        // b[r]=1;
    }    
    sort(a.begin()+1,a.end());

    int success,failure;//找到和没找到次数
    int sum_success_time,sum_failure_time;//对比次数
    double sum_success_clock,sum_failure_clock;//时间
    search_ShunXu(a,n,m,success,failure,sum_success_time,sum_failure_time,sum_success_clock,sum_failure_clock);
    cout<<"在顺序查找中："<<endl;
    print(n,m,success,failure,sum_success_time,sum_failure_time,sum_success_clock,sum_failure_clock);
    search_ErFen (a,n,m,success,failure,sum_success_time,sum_failure_time,sum_success_clock,sum_failure_clock);
    cout<<"在二分查找中："<<endl;
    print(n,m,success,failure,sum_success_time,sum_failure_time,sum_success_clock,sum_failure_clock);
    
}
    