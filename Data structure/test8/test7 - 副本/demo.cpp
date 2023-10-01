#include<bits/stdc++.h>
#include"Ntree.h"
using namespace std;

vector<string> name_data,q;  

bool querry(string s,NTree &t)//引用
{
    int l=0,r=s.size()-1;
    while(s[l]!=' ')l++;
    while(s[r]!=' ')r--;
    string x=s.substr(0,l),y=s.substr(r+1,s.size()-r-2);
    char c=s[l+6];
    // cout<<c<<endl;
    // cout<<x<<"   "<<y<<endl;
    // char c='c';
    //c 孩子  e 父母  s 兄弟姐妹   d后代   _祖先
    if(c=='c')return t.search_child(y,x);
    if(c=='e')return t.search_child(x,y);
    if(c=='s')return t.search_sibling(x,y);
    if(c=='d')return t.search_descendant(y,x);
    if(c==' ')return t.search_descendant(x,y);
}


int main()
{
    ifstream fin("d:/family.txt");
    int n=-1,m;
    while(n!=0)
    {
        name_data.clear();q.clear();
        string name;
        getline(fin,name);
        // cout<<name.size()<<endl;
        stringstream sstring(name);
        sstring>>n>>m;
        // cout<<n<<m<<endl;
        for(int i=1;i<=n;i++)
        {
            getline(fin,name);
            // cout<<name.size()<<endl;
            // if(!i)continue;
            name_data.push_back(name);
            cout<<name<<endl;
        }
        string s;
        NTree t(name_data,n);
        // t.check();
        // cout<<1<<endl;
        for(int i=1;i<=m;i++)
        {
            getline(fin,s);
            cout<<s<<endl;
            if(querry(s,t))cout<<"yes"<<endl;
            else cout<<"no"<<endl;
            // t.check();
        }
        cout<<"==============="<<endl;
        
    }

}  