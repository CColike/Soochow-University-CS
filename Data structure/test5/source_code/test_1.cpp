#include<bits/stdc++.h>
#include<windows.h>
using namespace std;

vector<int> unsorted,sorted;


void search(const vector<int> &a,const int &n,const int &m,int &success,int &failure,int &sum_success_time,int &sum_failure_time,double &sum_success_clock,double &sum_failure_clock)
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
            if(sorted[j]==target)
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
    unsorted.push_back(-1);sorted.push_back(-1);
    int n,m;
    cout<<"������n��";cin>>n;
    cout<<"������m��";cin>>m;
    /*����δ�����������������*/
    for(int i=1;i<=n;i++)
    {
        int r=rand()%n;
        unsorted.push_back(r);
        sorted.push_back(r);
    }    
    sort(sorted.begin()+1,sorted.end());

    
    int success,failure;//�ҵ���û�ҵ�����
    int sum_success_time,sum_failure_time;//�Աȴ���
    double sum_success_clock,sum_failure_clock;//ʱ��
    /*ģ����������в���ͳ��ʱ��*/
    search(unsorted,n,m,success,failure,sum_success_time,sum_failure_time,sum_success_clock,sum_failure_clock);
    /*������*/
    cout<<"�����"<<endl;
    print(n,m,success,failure,sum_success_time,sum_failure_time,sum_success_clock,sum_failure_clock);
    /*ģ����������в���ͳ��ʱ��*/
    search(sorted,n,m,success,failure,sum_success_time,sum_failure_time,sum_success_clock,sum_failure_clock);
    /*������*/
    cout<<"�����"<<endl;
    print(n,m,success,failure,sum_success_time,sum_failure_time,sum_success_clock,sum_failure_clock);
    
}