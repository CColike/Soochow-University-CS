#include"Stack.h"
#include"utility.h"
using namespace std;



void solve(const string &s)
{
    int lft=0;
    Stack<double>a;
    for(int i=0,len=s.size();i<len;i++)
    {
        if(s[i]==' '||i==len-1)
        {
            if(!get_mark(s[lft]))
            {
                if(a.push(get_num_in_str(s,lft,i-1))!=success)
                    str_error();
                cout<<"push "<<get_num_in_str(s,lft,i-1)<<endl;
                lft=i+1;
            }
            else
            {
                double x,y;
                bool flag=true;
                if(a.top(x)!=success)flag=false;
                if(a.pop()!=success) flag=false;
                if(a.top(y)!=success)flag=false;
                if(a.pop()!=success) flag=false;
                // cout<<s[lft+1]<<endl;
                // cout<<lft<<endl;
                if(a.push(res(y,x,s[lft]))!=success)flag=false;
                if(!flag)
                    str_error();
                cout<<"pop " <<x<<endl;
                cout<<"pop " <<y<<endl;
                cout<<y<<' '<<s[lft]<<' '<<x<<" = "<<res(y,x,s[lft])<<endl;
                cout<<"push "<<res(y,x,s[lft])<<endl;
                if(i==len-1)
                    cout<<"the answer is "<<res(y,x,s[lft])<<endl;
                else
                    lft=i+1; 
            }
        }
    }
}



int main()
{
    instruction();
    string s;getline(cin,s);
    solve(s);
}