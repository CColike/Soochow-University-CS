#include<bits/stdc++.h>
#include<windows.h>
using namespace std;

int n,cnt_cmp,cnt_mov,cnt_out=0;//compare, swap, cout which order of the three test
vector<int> a_positive,a_reverse,a_random;
    LARGE_INTEGER t1,t2,tc;

void format(string &s)
{
    if(s[s.size()-1]!='/'&&s[s.size()-1]!='\\')s=s+"/";
}


void get_data(string path,int n)
{
    format(path);
    int temp;
    ifstream in1(path+to_string(n)+"_positive.txt");
    if(!in1)
    {
        cout<<"please run create_arr.cpp first"<<endl;
        cout<<"or check whether the folder is right"<<endl;
        exit(0);
    }
    for(int i=1;i<=n;i++)
    {
        in1>>temp;
        a_positive.push_back(temp);
    }
    ifstream in2(path+to_string(n)+"_reverse.txt");
    for(int i=1;i<=n;i++)
    {
        in2>>temp;
        a_reverse.push_back(temp);
    }
    ifstream in3(path+to_string(n)+"_random.txt");
    for(int i=1;i<=n;i++)
    {
        in3>>temp;
        a_random.push_back(temp);
    }

}

void insert_sort(vector<int> a)
{
    cnt_cmp=cnt_mov=0;
    QueryPerformanceFrequency(&tc);
    QueryPerformanceCounter(&t1);
    for(int i=0;i<n;i++)
    {
        for(int j=i;j>=1;j--)
        {
            if(a[j]<a[j-1])//< or <= are both right
            {
                swap(a[j],a[j-1]);
                cnt_mov++;
            }
            cnt_cmp++;
        }
    }
    QueryPerformanceCounter(&t2);
    // for(int i=0;i<n;i++)cout<<a[i]<<endl;
}

void select_sort(vector<int>a)
{
    cnt_cmp=cnt_mov=0;
    QueryPerformanceFrequency(&tc);
    QueryPerformanceCounter(&t1);
    for(int i=0;i<n-1;i++)
    {
        for(int j=i+1;j<n;j++)
        {
            if(a[j]<a[i])//< or <= are both right
            {
                swap(a[i],a[j]);
                cnt_mov++;
            }
            cnt_cmp++;
        }
    }
    QueryPerformanceCounter(&t2);
    // for(int i=0;i<n;i++)cout<<a[i]<<endl;
}



void shell_sort(vector<int>a) 
{
    int d=1;
    while(d<n/3) d=3*d+1;
    cnt_cmp=cnt_mov=0;
    QueryPerformanceFrequency(&tc);
    QueryPerformanceCounter(&t1);
    while(d>=1) 
    {
        for(int i=d;i<n;i++) 
        {
            cnt_cmp+=i/d;
            for (int j=i;j>=d&&a[j]<a[j-d];j-=d) 
            {
                swap(a[j], a[j-d]);
                cnt_mov++;
            }
        }
        d=d/3;
    }
    QueryPerformanceCounter(&t2);
    // for(int i=0;i<n;i++)cout<<a[i]<<endl;
}



void Merge_sort(vector<int>&a,int ans[],int l,int r) 
{
    if(l>= r)return;
    int len=r-l,mid=(l+r)/2;
    int l1=l,r1=mid,l2=mid+1,r2=r;

    Merge_sort(a,ans,l1,r1);
    Merge_sort(a,ans,l2,r2);

    int k=l;
    while(l1<=r1&&l2<=r2)
    {
        cnt_cmp++;cnt_mov++;
        if(a[l1]<a[l2])ans[k++]=a[l1++];
        else ans[k++]=a[l2++];
    }
    while(l1<=r1)
    {
        ans[k++]=a[l1++];
        cnt_mov++;
    }
    while(l2<=r2)
    {
        ans[k++]=a[l2++];
        cnt_mov++;  
    }
    for(k=l;k<=r;k++)
        a[k]=ans[k];
}

void merge_sort(vector<int> a) 
{
    int ans[n+1];
    cnt_cmp=cnt_mov=0;
    QueryPerformanceFrequency(&tc);
    QueryPerformanceCounter(&t1);
    Merge_sort(a,ans,0,n-1);
    QueryPerformanceCounter(&t2);
    // for(int i=0;i<n;i++)cout<<ans[i]<<endl;
}



void quickSort(vector<int>&a,int l,int r)
{
	if (l<r)
	{      
		int i=l,j=r,x=a[l];
		while(i<j)
		{
			while(i<j&&a[j]>=x)
            {
				j--; 
                cnt_cmp++;
            }
			if(i<j)
            {
				a[i++]=a[j];
                cnt_mov++;
            }
			while(i<j&&a[i]<x) 
            {
				i++; 
                cnt_cmp++;
            }
			if(i<j)
            {
				a[j--]=a[i];
                cnt_mov++;
            }
		}
		a[i]=x;
		quickSort(a,l,i-1);
		quickSort(a,i+1,r);
    }
}

void quick_sort(vector<int> a)
{
    cnt_cmp=cnt_mov=0;
    QueryPerformanceFrequency(&tc);
    QueryPerformanceCounter(&t1);
    quickSort(a,0,n-1);
    QueryPerformanceCounter(&t2);
    // for(int i=0;i<n;i++)cout<<a[i]<<endl;
}


void heap_adjust(vector<int>&a, int k0, int max_index) {
    int k1=k0*2+1;
    while (k1<=max_index) 
    {
        cnt_cmp+=2; 
        if (k1+1<=max_index&&a[k1]<a[k1+1]) 
            k1++;//k0:present node waiting to be adjusted,k1:bigger son
        if (a[k0]>=a[k1])return;
        swap(a[k1],a[k0]);
        cnt_mov++;
        k0=k1;
        k1=k0*2+1;
    }
}

void heap_sort(vector<int> a) 
{ 
    cnt_cmp=cnt_mov=0;
    QueryPerformanceFrequency(&tc);
    QueryPerformanceCounter(&t1);
    for (int i=n/2-1;i>=0;i--)
        heap_adjust(a,i,n-1);
    for (int i=n-1;i>0;i--) 
    {
        cnt_mov++;
        swap(a[0],a[i]);
        heap_adjust(a,0,i-1);
    }
    QueryPerformanceCounter(&t2);
}

void show_cnt()
{
    if(cnt_out%3==0)cout<<"positive order:\n";
    if(cnt_out%3==1)cout<<"reverse order:\n";
    if(cnt_out%3==2)cout<<"random order:\n";
    cnt_out++;
    cout<<"compare count:"<<cnt_cmp<<" move count:"<<cnt_mov<<endl;
    printf("time:%.7fs\n",(double)(t2.QuadPart-t1.QuadPart)/(double)tc.QuadPart);
}


// QueryPerformanceFrequency(&tc);
// QueryPerformanceCounter(&t1);
// //do
// QueryPerformanceCounter(&t2);
// (double)(t2.QuadPart-t1.QuadPart)/(double)tc.QuadPart;


int main()
{
    string path;
    cout<<"please input the folder in create_arr.cpp:";cin>>path;
    cout<<"please input the length of the arrays:";cin>>n;
    get_data(path,n);

    cout<<"\ninsert_sort:\n";
    insert_sort(a_positive);
    show_cnt();
    insert_sort(a_reverse);
    show_cnt();
    insert_sort(a_random);
    show_cnt();

    cout<<"\nselect_sort:\n";
    select_sort(a_positive);
    show_cnt();
    select_sort(a_reverse);
    show_cnt();
    select_sort(a_random);
    show_cnt();

    cout<<"\nshell_sort:\n";
    shell_sort(a_positive);
    show_cnt();
    shell_sort(a_reverse);
    show_cnt();
    shell_sort(a_random);
    show_cnt();

    cout<<"\nmerge_sort:\n";
    merge_sort(a_positive);
    show_cnt();
    merge_sort(a_reverse);
    show_cnt();
    merge_sort(a_random);
    show_cnt();

    cout<<"\nquick_sort:\n";
    quick_sort(a_positive);
    show_cnt();
    quick_sort(a_reverse);
    show_cnt();
    quick_sort(a_random);
    show_cnt();

    cout<<"\nheap_sort:\n";
    heap_sort(a_positive);
    show_cnt();
    heap_sort(a_reverse);
    show_cnt();
    heap_sort(a_random);
    show_cnt();

}