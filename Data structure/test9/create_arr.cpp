#include<bits/stdc++.h>
using namespace std;


vector<int>a;


void format(string &s)
{
    if(s[s.size()-1]!='/'&&s[s.size()-1]!='\\')s=s+"/";
}

void create(string path,vector<int>&a)
{
    ofstream out(path);
    if(!out)
    {
        cout<<"error!please check whether the folder already exist";
        exit(0);
    }
    int len=a.size();
    for(int i=0;i<len;i++)
    {
        out<<a[i]<<endl;
        // cout<<a[i]<<endl;
    }
}

int main()
{
    int n;string path;
    cout<<"please input the length of the list you want:";
    cin>>n;
    cout<<"please input the path of a folder(Must already exist)\nsuch as: d:/data/"<<endl;
    cin>>path;
    path="d:/data/";//if there is a '/'?
    ofstream out(path);
    for(int i=1;i<=n;i++)
        a.push_back(rand()%n);
    format(path);
    create(path+to_string(n)+"_random.txt",a);
    sort(a.begin(),a.end());
    create(path+to_string(n)+"_positive.txt",a);
    reverse(a.begin(),a.end());
    create(path+to_string(n)+"_reverse.txt",a);
}