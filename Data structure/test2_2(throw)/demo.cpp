#include"Stack.h"
#include"utility.h"
using namespace std;

char a[8][8]={{},{' ','>','>','<','<','<','>','>'},
                 {' ','>','>','<','<','<','>','>'},
                 {' ','>','>','>','>','<','>','>'},
                 {' ','>','>','>','>','<','>','>'},
                 {' ','<','<','<','<','<','=',' '},
                 {' ','>','>','>','>',' ','>','>'},
                 {' ','<','<','<','<','<','<','='}};

Stack<double>num;
Stack<char> mark;


int get_mark(char c)
{
    switch(c)
    {
        case '+':return 1;
        case '-':return 2;
        case '*':return 3;
        case '/':return 4;
        case '(':return 5;
        case ')':return 6;
        case '#':return 7;
    default:
        return 0;
    }
}

double res(double x,double y,char c)
{
    switch (c)
    {
        case '+':return x+y;
        case '-':return x-y;
        case '*':return x*y;
        case '/':return x/y;
    default:
        cout<<"unknow error"<<endl;
        exit(0);
    }
}


void work(char ch)
{
    //num.show();
    //mark.show();
    char ch1;
    try
    {
        ch1=mark.top();//
    }
    catch(under_flow)
    {
        cout<<"the string is incorrect"<<endl;
        exit(0);
    }
    
    //cout<<ch1<<'-'<<endl;
    char c=a[get_mark(ch1)][get_mark(ch)];
    // cout<<ch1<<endl;
    // cout<<c<<endl;
    // cout<<ch<<endl;
    // cout<<c<<"----------"<<endl;
    switch(c)//高效
    {
        case '=':
            switch(ch)
            {
                case ')':
                        try
                        {
                            mark.pop();
                            
                        }
                        catch(under_flow)
                        {
                            cout<<"the string is incorrect"<<endl;
                            exit(0);
                        }
                        break;
                case '#':cout<<num.top();
                         return;
            }
            break;
        case '<':
            try
            {
                mark.push(ch);
            }
            catch(up_flow)
            {
                cout<<"the string is incorrect"<<endl;
                exit(0);
            }
            break;
        case '>':
            try
            {
                mark.pop();
                double y=num.top();num.pop();
                double x=num.top();num.pop();
                num.push(res(x,y,ch1));
            }
            catch(under_flow)
            {
                cout<<"the string is incorrect"<<endl;
                exit(0);
            }
            work(ch);
    }
}


void slove_middle(string s)
{
    s='#'+s;
    int s_len=s.size(),left=1;
    double x,y;
    char ch1,ch;
    mark.push('#');

    for(int i=1;i<s_len;i++)
    {
        if(get_mark(s[i]))
        {
            if(!get_mark(s[left]))  
            {
                try
                {
                    num.push(get_num_in_str(s,left,i-1));
                }
                catch(up_flow)
                {
                    cout<<"the numbers are too many"<<endl;
                    exit(0);
                }
                
                //cout<<get_num_in_str(s,left,i-1)<<endl;
            }//                                         
                
            left=i+1;
            work(s[i]);
        }
    }
}



int main()
{
    string s;getline(cin,s);
    str_delete(s);//考虑到健壮性，整行读入后删去空格
    // cout<<s<<endl;
    slove_middle(s);
}

 //3*(4+5)/2-3-(5+2)#