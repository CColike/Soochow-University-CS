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


void work(char ch)
{
    //num.show();
    //mark.show();

    char ch1;
    if(mark.top(ch1)==underflow)
        string_error(0);

    char c=a[get_mark(ch1)][get_mark(ch)];

    cout<<ch1<<' '<<c<<' '<<ch<<endl;

    switch(c)//高效
    {
        case '=':
            switch(ch)
            {
                case ')':
                        if(mark.pop()==underflow)
                            string_error(1);
                        else
                            cout<<"mark   stack:pop '('"<<endl;
                        break;
                case '#':
                         double ans;
                         if(num.top(ans)==success)
                         {
                            cout<<"answer is:"<<ans<<endl;
                            exit(0);
                         }
                         else 
                            string_error(2);
                         break;
            }
            break;

        case '<':
            if(mark.push(ch)==overflow)
                string_error(3);
            else   
                cout<<"mark   stack:push '"<<ch<<"'"<<endl;
            break;

        case '>':
            double x,y;
            if(mark.pop()!=success)string_error(0);
            cout<<"mark   stack:pop '"<<ch1<<"'"<<endl;
            if(num.top(y)!=success)string_error(4);
            if(num.pop() !=success)string_error(4);
            cout<<"number stack:pop "<<y<<endl;
            if(num.top(x)!=success)string_error(4);
            if(num.pop() !=success)string_error(4);
            cout<<"number stack:pop "<<x<<endl;
            if(num.push(res(x,y,ch1))!=success)string_error(3);
            cout<<x<<' '<<ch1<<' '<<y<<" ="<<' '<<res(x,y,ch1)<<endl;
            cout<<"number stack:push "<<res(x,y,ch1)<<endl;
            work(ch);
        
        case ' ':
            string_error(5);
    }
}


void solve_middle(const string &s)//引用提升效率
{
    int s_len=s.size(),left=0;
    double x,y;
    char ch1,ch;
    mark.push('#');
    cout<<"mark   stack:push '#'"<<endl;

    for(int i=0;i<s_len;i++)
    {
        if(get_mark(s[i]))
        {
            if(!get_mark(s[left]))  
            {
                //cout<<get_num_in_str(s,left,i-1)<<endl;
                if(num.push(get_num_in_str(s,left,i-1))==overflow)
                    string_error(3);
                else
                    cout<<"number stack:push "<<get_num_in_str(s,left,i-1)<<endl;
            }                                         
                
            left=i+1;
            work(s[i]);
        }
    }
}



int main()
{
    instruction();
    string s;getline(cin,s);
    strengthen(s);//考虑到健壮性，整行读入后删去其余字符（包括空格等）
                  //考虑到负数在首位情况,进行添0使它符合规范
    cout<<"after formatting:"<<s<<endl;
    solve_middle(s);
}


 