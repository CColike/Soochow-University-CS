#include"Stack.h"
#include"utility.h"
#define ERROR_CODE_MARK -29
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
            return ERROR_CODE_MARK;
    }
}


void work(char ch)
{
    //num.show();
    //mark.show();
    char ch1=mark.top();
    //cout<<ch1<<'-'<<endl;
    char c=a[get_mark(ch1)][get_mark(ch)];
    //cout<<ch1<<c<<ch<<endl;
    switch(c)//高效
    {
        case '=':
            switch(ch)
            {
                case ')':mark.pop();
                         break;
                case '#':cout<<num.top();
                         return;
            }
            break;
        case '<':
            mark.push(ch);
            break;
        case '>':
            mark.pop();
            double y=num.top();num.pop();
            double x=num.top();num.pop();
            num.push(res(x,y,ch1));
            work(ch);
    }
}


void slove_middle()
{
    string s; cin>>s;
    s='#'+s;
    int s_len=s.size(),left=1;
    double x,y;
    char ch1,ch;
    mark.push('#');

    for(int i=1;i<s_len;i++)
    {
        if(get_mark(s[i]))
        {
            if(!get_mark(s[left]))   //3*(4+5)/2-3-(5+2)#
            {
                num.push(get_num_in_str(s,left,i-1));
                //cout<<get_num_in_str(s,left,i-1)<<endl;
            }                                         //
                
            left=i+1;
            work(s[i]);
        }
    }
}



int main()
{
    slove_middle();
}