#include<bits/stdc++.h>
using namespace std;

class under_flow{};
class up_flow{};
const int max_stack=1000;

template <typename T>
class Stack
{
private:
    int len=0;//最小的空的空间下标
    T a[max_stack];
    
public:
    Stack();
    T top();
    void push(T temp);
    void pop();
    bool empty();
    /*
    void show()
    {
        for (int i=0;i<len;i++)
        {
            cout<<a[i]<<'_';
        }
        cout<<endl;
    }
    */
};


template <typename T>
Stack<T>::Stack()
{
    memset(a,0,sizeof(a));//实际上没有必要
    len=0;
}

template <typename T>
T Stack<T>::top()//在函数名前加作用域
{
    if(len)
        return a[len-1];
    else 
        throw under_flow();
}

template <typename T>
void Stack<T>::push(T temp)
{
    if(len<=max_stack-1)
        a[len++]=temp;
    else
        throw up_flow();
}

template <typename T>
void Stack<T>::pop()
{
    if(len>0)
        len--;
    else
        throw under_flow();
}

template <typename T>
bool Stack<T>::empty()
{
    if(len)
        return true;
    else 
        return false;
}