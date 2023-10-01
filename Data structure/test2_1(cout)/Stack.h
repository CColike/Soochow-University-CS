#include<bits/stdc++.h>
#define ERROR_CODE_OUT_OF_RANGE '3'
using namespace std;

template <typename T>
class Stack
{
private:
    int len=0;//空的最小的下标
    T a[10001];
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
    memset(a,0,sizeof(T)*10001);//实际上没有必要
    len=0;
}

template <typename T>
T Stack<T>::top()//在函数名前加作用域
{
    if(len)
        return a[len-1];
    else 
    {
        cout<<"out of range"<<endl;
        return ERROR_CODE_OUT_OF_RANGE;//all numbers in stack are postive,so error_code is negative
    }
        
}

template <typename T>
void Stack<T>::push(T temp)
{
    if(len<=10000)
        a[len++]=temp;
    else
        cout<<"out of range"<<endl;
}

template <typename T>
void Stack<T>::pop()
{
    if(len>0)
        len--;
    else
        cout<<"out of range"<<endl;
}

template <typename T>
bool Stack<T>::empty()
{
    if(len)
        return true;
    else 
        return false;
}