#include<bits/stdc++.h>
using namespace std;

class big_int
{
private:
    list<int>a;
    char c;
public:
    big_int();
    void build(string &s);
    void show();
    friend big_int operator+(const big_int &a,const big_int &b);
    friend big_int operator-(const big_int &a,const big_int &b);
    friend big_int operator*(const big_int &a,const big_int &b);
};


big_int::big_int()
{
    a.clear();
}

void big_int::build(string &s)
{
    int ls=s.size(),endd=0;
    if(s[0]=='-')
    {
        c='-';
        endd=1;
    }
    else if(s[0]=='+')
    {
        c='+';
        endd=1;
    } 
    else
    {
        c='+';
        endd=0;
    }
    for(int i=ls-1;i>=endd;i--)
    {
        //cout<<s[i]-'0'<<endl;
        a.push_back(s[i]-'0');
    }
}

void big_int::show()
{
    int la=a.size();
    // cout<<c<<endl;
    if(c=='-')cout<<'-';
    for(int i=la-1;i>=0;i--)
    {
        list<int>::iterator iter=a.begin();
        advance(iter,i);
        cout<<*iter;
    }
    cout<<endl;
}




big_int operator+(const big_int &xx,const big_int &yy)
{
    big_int x=xx,y=yy,z;//x+y=z
    // cout<<'x'<<x.c<<'y'<<y.c<<"xx"<<xx.c<<"yy"<<yy.c<<endl;
    if(x.c!=y.c)
    {
        if(x.c=='+')
        {
            y.c='+';
            return x-y;
        }
        else
        {
            x.c='+';
            return y-x;
        }
    }
    z.c=x.c;
    // cout<<'z'<<z.c<<endl;
    int lx=x.a.size(),ly=y.a.size();
    int jw=0;
    list<int>::iterator iter_x=x.a.begin();
    list<int>::iterator iter_y=y.a.begin();
    for(int i=lx;i<ly;i++)x.a.push_back(0);
    for(int i=ly;i<lx;i++)y.a.push_back(0);
    for(int i=0;i<max(lx,ly);i++)
    {
        int zz=*iter_x+*iter_y+jw;
        jw=zz/10;
        zz%=10;
        z.a.push_back(zz);
        advance(iter_x,1);
        advance(iter_y,1);
    }
    if(jw!=0)
        z.a.push_back(jw);
    return z;
}

big_int operator-(const big_int &xx,const big_int &yy)
{
    big_int x=xx,y=yy,z;//x+y=z
    if(x.c!=y.c)
    {
        if(y.c=='-')
            y.c='+';
        else
            y.c='-';
        return x+y;
    }
    int lx=x.a.size(),ly=y.a.size(),waiting=0;
    int jw=0;
    list<int>::iterator iter_x=x.a.begin();
    list<int>::iterator iter_y=y.a.begin();
    for(int i=lx;i<ly;i++)x.a.push_back(0);
    for(int i=ly;i<lx;i++)y.a.push_back(0);
    lx=max(lx,ly);ly=max(lx,ly);
    for(int i=lx-1;i>=0;i--)
    {
        list<int>::iterator iter_x=x.a.begin();
        list<int>::iterator iter_y=y.a.begin();
        advance(iter_x,i);
        advance(iter_y,i);
        if(*iter_x>*iter_y)
        {
            z.c=x.c;
            break;
        }
        if(*iter_x<*iter_y)
        {
            big_int temp;
            temp=x;
            x=y;
            y=temp;
            if(x.c=='+')z.c='-';
            else z.c='+';
            break;
        }
    }
    for(int i=0;i<max(lx,ly);i++)
    {
        int zz=*iter_x-*iter_y-jw;
        //cout<<zz<<endl;
        if(zz<0)
        {
            zz+=10;
            jw=1;
        }
        else
            jw=0;
        if(zz==0)
        {
            waiting++;
        }
        else
        {
            for(int j=1;j<=waiting;j++)
                z.a.push_back(0);
            waiting=0;
            z.a.push_back(zz);
        }
        
        
        advance(iter_x,1);
        advance(iter_y,1);
    }
    return z;
}


big_int operator*(const big_int &xx,const big_int &yy)
{
    big_int x=xx,y=yy,temp,ans;
    ans.a.clear();
    ans.a.push_back(0);
    // cout<<xx.c<<' '<<yy.c<<' '<<x.c<<' '<<y.c<<endl;
    // cout<<ans.c<<endl;
    int lx=x.a.size(),ly=y.a.size(),jw=0;
    list<int>::iterator iter_x=x.a.begin();
    for(int i=0;i<lx;i++)
    {
        jw=0;
        temp.a.clear();
        temp.c='+';
        list<int>::iterator iter_y=y.a.begin();
        for(int j=0;j<ly;j++)
        {
            int t=(*iter_y)*(*iter_x)+jw;
            // cout<<*iter_x<<' '<<*iter_y<<endl;
            jw=t/10;
            t%=10;
            temp.a.push_back(t);
            // cout<<t<<endl;
            advance(iter_y,1);
        }
        if(jw)
        {
            temp.a.push_back(jw);
        }
        //  cout<<"temp:";temp.show();cout<<endl;
        // cout<<"ans:";ans.show();cout<<endl;
        ans=ans+temp;
        // cout<<"ans:";ans.show();cout<<endl;
        advance(iter_x,1);
        y.a.push_front(0);
        ly++;
    }
    if(x.c==y.c)
        ans.c='+';
    else
        ans.c='-';
    //  cout<<ans.c<<endl;
    return ans;
}
 
int main()
{
    string s,ss;
    cout<<"x=";getline(cin,s);
    cout<<"y=";getline(cin,ss);
    big_int x,y,z;
    x.build(s);
    y.build(ss);
    z=x+y;
    cout<<"x+y=";
    z.show();
    z=x-y;
    cout<<"x-y=";
    z.show();
    z=x*y;
    cout<<"x*y=";
    z.show();
}