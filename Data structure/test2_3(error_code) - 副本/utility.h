#include <cassert>
#include <cctype>
#include <cerrno>
#include <cfloat>
#include <ciso646>
#include <climits>
#include <clocale>
#include <cmath>
#include <csetjmp>
#include <csignal>
#include <cstdarg>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <ccomplex>
#include <cfenv>
#include <cinttypes>
#include <cstdalign>
#include <cstdbool>
#include <cstdint>
#include <ctgmath>
#include <cwchar>
#include <cwctype>
#include <algorithm>
#include <bitset>
#include <complex>
#include <deque>
#include <exception>
#include <fstream>
#include <functional>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <iostream>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <memory>
#include <new>
#include <numeric>
#include <ostream>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <typeinfo>
#include <utility>
#include <valarray>
#include <vector>
#include <array>
#include <atomic>
#include <chrono>
#include <condition_variable>
#include <forward_list>
#include <future>
#include <initializer_list>
#include <mutex>
#include <random>
#include <ratio>
#include <regex>
#include <scoped_allocator>
#include <system_error>
#include <thread>
#include <tuple>
#include <typeindex>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>

//不用 using namespace std

double get_num_in_str(std::string str,int xx,int yy)
{
    double num1=0,num2=0;
    int x=xx,y=yy;
    while(str[x]!='.'&&x<=yy)
    {
        num1=num1*10+str[x++]-'0';
    }
    if(x==yy+1)return num1;
    while(str[y]!='.')
        num2=(num2+str[y--]-'0')*0.1;

    return num1+num2;
}

void strengthen(std::string &s)//删除字符串中的杂志
{
    int s_len=s.size(),r_len=18,ss_len=0;
    char right_char[r_len]={'0','1','2','3','4','5','6','7','8','9'
                        ,'+','-','*','/','(',')','.','#'};
    std::string ss="";
    for(int i=0;i<s_len;i++)
    {
        bool flag=false;
        for(int j=0;j<r_len;j++)
        {
            if(s[i]==right_char[j])
            {
                flag=true;
                break;
            }
        }
        if(flag)
        {
            if(ss_len)if(ss[ss_len-1]=='('&&s[i]=='-')
            {
                ss+='0';
                ss_len++;
            }
            ss_len++;
            ss+=s[i];
        }
    }
    if(ss[0]=='-')ss='0'+ss;
    s=ss;
}

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
        std::cout<<"unknow error"<<std::endl;
        exit(0);
    }
}

void string_error(int i)
{
    std::cout<<"error!the string is incorrect"<<std::endl;
    switch(i)
    {
        case 0:
            std::cout<<"the string may lack marks,please check it"<<std::endl;
            break;
        case 1:
            std::cout<<"the string may lack '(' ,please check it"<<std::endl;
            break;
        case 2:
            std::cout<<"there may be no number before '#',please check it"<<std::endl;
            break;
        case 3:
            std::cout<<"error!the string is too long(the numbers are too many)"<<std::endl;
            break;
        case 4:
            std::cout<<"the string may lack numbers,please check it"<<std::endl;
            break;
        
    }
    exit(0);
}

