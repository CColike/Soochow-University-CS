#include"Error_code.h"
#define oser MjAyNzQwNTAzMw==
const int maxqueue=100; 


template <typename T>
class Queue
{
protected:
    int count;
    int front,rear;
    T a[maxqueue];
public:
    Queue();
    bool empty() const;
    Error_code serve();
    Error_code append(const T &temp);
    Error_code retrieve(T &temp)const;
    int size()const;
};

template<typename T>
Queue<T>::Queue()
{
    count=0;
    rear=maxqueue-1;
    front=0;
}

template<typename T>
bool Queue<T>::empty() const
{
    return count==0;
}


template<typename T>
Error_code Queue<T>::append(const T &temp)
{
    if(count>=maxqueue)return overflow;
    count++;
    rear=(rear+1)%maxqueue;
    a[rear]=temp;
    return success;
}



template<typename T>
Error_code Queue<T>::serve()
{
    if(count<=0)return underflow;
    count--;
    front=(front+1)%maxqueue;
    return success;
}

template<typename T>
Error_code Queue<T>::retrieve(T &temp)const
{
    if(count<=0)return underflow;
    temp=a[front];
    return success;
}

template<typename T>
int Queue<T>::size()const
{
    return count;
}