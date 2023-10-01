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

using namespace std;

void instructions()
{
    cout<<"this is a program sloving the Life Game\n";
    cout<<"the row and col can be modified in Life.h\n";
}

bool user_says_yes()
{
    string temp;
    cin>>temp;
    if(temp=="yes"||temp=="1"||temp=="Y") return 1;
    else return 0;
}

double get_num_in_str(string str,int xx,int yy)
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

void str_delete(string &s)//删除字符串中的杂志
{
    int s_len=s.size(),r_len=18;
    char right_char[r_len]={'0','1','2','3','4','5','6','7','8','9'
                        ,'+','-','*','/','(',')','.','#'};
    string ss="";
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
        if(flag)ss+=s[i];
    }
    s=ss;
}