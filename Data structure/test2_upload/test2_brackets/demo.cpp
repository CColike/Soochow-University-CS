#include"Stack.h"
#include"utility.h"
using namespace std;


bool brackets(const string &s)
{
    Stack<char>a;
    char c;Error_code e;
    for(int i=0,len=s.size();i<len;i++)
    {
        switch(s[i])
        {
            case '(':
                if(a.push(s[i])!=success)str_error();
                break;
            case ')':
                if(a.top(c)==success)
                    if(c=='(')
                        e=a.pop();
                    else return false;
                else return false;
                break;

            case '[':
                if(a.push(s[i])!=success)str_error();
                break;
            case ']':
                if(a.top(c)==success)
                    if(c=='[')
                        e=a.pop();
                    else return false;
                else return false;
                break;

            case '{':
                if(a.push(s[i])!=success)str_error();
                break;
            case '}':
                if(a.top(c)==success)
                    if(c=='{')
                        e=a.pop();
                    else return false;
                else return false;
                break;

            default:continue;
        }
    }
    return a.empty();
}

int main()
{
    instruction();
    string s;
    getline(cin,s);
    if(brackets(s))cout<<"YES"<<endl;
    else cout<<"NO"<<endl;
}