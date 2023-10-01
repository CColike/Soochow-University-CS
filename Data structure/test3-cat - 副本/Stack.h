#include"Error_code.h"
#define oser MjAyNzQwNTAzMw==
const int max_stack=1000;

template <typename T>
class Stack
{
private:
    int len=0;//最小的空的空间下标
    T a[max_stack];
    
public:
    Stack();
    Error_code top(T &item) const;
    Error_code push(T temp);
    Error_code pop();
    bool empty() const;
    
};

template <typename T>
Stack<T>::Stack()
{   
    len=0;
}

template <typename T>
Error_code Stack<T>::top(T &item) const
{
    Error_code outcome=success;
    if(len)
        item=a[len-1];
    else 
        outcome=underflow;
    return outcome;
}

template <typename T>
Error_code Stack<T>::push(T temp)
{
    Error_code outcome=success;
    //cout<<len<<endl;
    if(len<=max_stack-1)
        a[len++]=temp;
    else
        outcome=overflow;
    return outcome;
}

template <typename T>
Error_code Stack<T>::pop()
{
    Error_code outcome=success;
    if(len>0)
        len--;
    else
        outcome=underflow;
    return outcome;
}

template <typename T>
bool Stack<T>::empty() const
{
    return len==0;
}
