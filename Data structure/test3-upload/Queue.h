#include"Error_code.h"
const int maxqueue=2000;


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
    Error_code serve();//删除队头元素
    Error_code append(const T &temp);//队尾添加元素
    Error_code retrieve(T &temp)const;//返回队头元素
    int size()const;
    void show()const;
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
Error_code Queue<T>::serve()//删除队头元素
{
    if(count<=0)return underflow;
    count--;
    front=(front+1)%maxqueue;
    return success;
}

template<typename T>
Error_code Queue<T>::retrieve(T &temp)const//返回队头元素
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

template<typename T>
void Queue<T>::show()const
{
    if(!count)std::cout<<"None"<<std::endl;
    else
    {
        for(int i=0;i<count;i++)
        {
            if(!i)std::cout<<a[(front+i)%maxqueue];
            else  std::cout<<'-'<<a[(front+i)%maxqueue];
        }
        std::cout<<std::endl;
    }
    
}