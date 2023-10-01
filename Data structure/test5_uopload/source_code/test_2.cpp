#include<bits/stdc++.h>
#include<windows.h>
using namespace std;

vector <int> a;
// int b[10000000];

void search_ShunXu(const vector<int> &a,int n,int m,int &success,int &failure,int &sum_success_time,int &sum_failure_time,double &sum_success_clock,double &sum_failure_clock)
{
    success=0;failure=0;//�ҵ���û�ҵ�����
    sum_success_time=0;sum_failure_time=0;//�Աȴ���
    sum_success_clock=0;sum_failure_clock=0;//ʱ��
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
    success=0;failure=0;//�ҵ���û�ҵ�����
    sum_success_time=0;sum_failure_time=0;//�Աȴ���
    sum_success_clock=0;sum_failure_clock=0;//ʱ��
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
    cout<<"�ڳ�Ϊ"<<n<<"�ı���"<<m<<"�β����У�"<<endl;
    cout<<"     ����"<<success<<"�γɹ���ѯ"<<endl;
    cout<<"     ƽ��ÿ�γɹ�������Ҫ"<<(sum_success_time*1.0)/(success*1.0)<<"�αȽ�"<<endl;
    // printf("%.20f\n",sum_success_clock);
    printf("     ƽ��ÿ�β��Һ�ʱ%.20f��\n",sum_success_clock/(success*1.0));
    printf("     �ɹ������ܺ�ʱ%.20f��\n\n",sum_success_clock);
    cout<<"     ����"<<failure<<"��ʧ�ܲ�ѯ"<<endl;
    cout<<"     ƽ��ÿ��ʧ�ܲ�����Ҫ"<<(sum_failure_time*1.0)/(failure*1.0)<<"�αȽ�"<<endl;
    // printf("%.20f\n",sum_failure_clock);
    printf("     ƽ��ÿ�β��Һ�ʱ%.20f��\n",sum_failure_clock/(failure*1.0));
    printf("     ʧ�ܲ����ܺ�ʱ%.20f��\n",sum_failure_clock);
    printf("          �㷨�ܺ�ʱ%.20f��\n\n",sum_success_clock+sum_failure_clock);
}


int main()
{
    a.push_back(0);
    int n,m;
    cout<<"������n��";cin>>n;
    cout<<"������m��";cin>>m;
    /*����������������*/
    for(int i=1;i<=n;i++)
    {
        int r=rand()%n;
        a.push_back(r);
        // b[r]=1;
    }    
    sort(a.begin()+1,a.end());

    int success,failure;//�ҵ���û�ҵ�����
    int sum_success_time,sum_failure_time;//�Աȴ���
    double sum_success_clock,sum_failure_clock;//ʱ��
    search_ShunXu(a,n,m,success,failure,sum_success_time,sum_failure_time,sum_success_clock,sum_failure_clock);
    cout<<"��˳������У�"<<endl;
    print(n,m,success,failure,sum_success_time,sum_failure_time,sum_success_clock,sum_failure_clock);
    search_ErFen (a,n,m,success,failure,sum_success_time,sum_failure_time,sum_success_clock,sum_failure_clock);
    cout<<"�ڶ��ֲ����У�"<<endl;
    print(n,m,success,failure,sum_success_time,sum_failure_time,sum_success_clock,sum_failure_clock);
    
}
    