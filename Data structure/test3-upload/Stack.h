//不要用using namespce ,做工程的时候套太多容易出错
#include"Error_code.h"
const int max_stack=2000;

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
    void show()const;
};

template <typename T>
Stack<T>::Stack()
{   
    len=0;//没必要mst
}

template <typename T>
Error_code Stack<T>::top(T &item) const//在函数名前加作用域
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

template <typename T>
void Stack<T>::show()const
{
    if(this->empty())std::cout<<"None"<<std::endl;
    else 
    {
        for (int i=0;i<len-1;i++)
        {
            std::cout<<a[i]<<'-';
        }
        std::cout<<a[len-1]<<std::endl;  
    } 
}

//using namespace std 用了后，后面要用template <typename T>   Stack::sss<>
//Error_code  Error_code