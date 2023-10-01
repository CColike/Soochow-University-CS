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

void instruction()
{
    std::cout<<"this is a program solving Postfix Expression"<<std::endl;
    std::cout<<"please input a Postfix Expression,Separated by spaces"<<std::endl;
    std::cout<<"such as:  '3 4 * 5 - 7 +'"<<std::endl;
    std::cout<<"     or:  '3.4 4.3 * 5.1 - 7.2 +'"<<std::endl;
}

int get_mark(char c)
{
    switch(c)
    {
        case '+':return 1;
        case '-':return 2;
        case '*':return 3;
        case '/':return 4;
    default:
        return 0;
    }
}

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

void str_error()
{
    std::cout<<"the string is incorrect,please check it"<<std::endl;
    exit(0);
}