#include<bits/stdc++.h>
using namespace std;

const int maxqueue=100;

class upflow{};
class underflow{};

template <typename T>
class Queue
{
protected:
    int count;
    int front,rear;//队头，队尾
    T a[maxqueue];
public:
    Queue();
    bool empty() const;
    void serve();//删除队头元素
    void append(const T &temp);//队尾添加元素
    T retrieve(T &temp)const;//返回队头元素
    void reverse_serve();//删除队尾元素
    void reverse_append(const T &temp);//队头添加元素
};

template<typename T>
Queue<T>::Queue()
{
    count=0;
    front=0;rear=maxqueue-1;
    memset(a,0,sizeof(T)*maxqueue);
}

template<typename T>
bool Queue<T>::empty() const
{
    return count==0;
}

template<typename T>
void Queue<T>::serve()//删除队头元素
{
    if(count<=0)throw underflow();
    count--;
    front=(front+1)%maxqueue;
}

template<typename T>
void Queue<T>::append(const T &temp)
{
    if(count>=maxqueue)throw upflow();
    count++;
    rear=(rear+1)%maxqueue;
    a[rear]=temp;
}

template<typename T>
T Queue<T>::retrieve(T &temp)const//返回队头元素
{
    if(count<=0)throw underflow();
    temp=a[front];
}

template<typename T>
void Queue<T>::reverse_serve()//删除队尾元素
{
    if(count<=0)throw underflow();
    count--;
    rear=(rear-1+maxqueue)%maxqueue;
}

template<typename T>
void Queue<T>::reverse_append(const T &temp)//队头添加元素
{
    if(count>=maxqueue)throw upflow();
    count++;
    front=(front-1+maxqueue)%maxqueue;
    a[front]=temp;
}