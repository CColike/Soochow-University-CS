#include<stdlib.h>
#include<iostream>

using namespace std;

template<class T>
struct Node 
{
    T data;
    Node<T>* next;
    Node<T>* pres;

    Node(Node<T> *p1=NULL,Node<T> *p2=NULL)
    {
        pres=p1;
        next=p2;
    }
    Node(T& item,Node<T>*p1=NULL,Node<T>*p2=NULL)
    {
        data=item;
        pres=p1;
        next=p2;
    }
};


template<class T>
class List
{
private:
    Node<T> * head;   
    int idx;
    Node<T> * idx_p;
    int count;
public:
    List(){ head=new Node<T>;idx=0;idx_p=head;head->next=head;head->pres=head;count=0;}                       
    List(const T& x){ head=new Node<T>(x);idx=0;idx_p=head;head->next=head;head->pres=head;count=1;}        
    List(List<T>& L);                                   
    List<T>& operator=(List<T>& L);                     
    ~List(){ clear(); }                                   

    Node<T> *setPosition(int i);                       
     
    void clear();                           
    int length()const;                              
    Node<T> *gethead()const{ return head; }         
    Node<T> *search(T x);                            
    bool getData(int i,T& x)const;                  
    void setData(int i,T& x);                         
    bool insert(int i,T& x);                         
    bool remove(int i,T& x);                         
    bool empty()const ;                            
    void showData();                               
};




template<class T>
Node<T> * List<T>::setPosition(int i)
{
    // cout<<"iiii "<<i<<endl;
    if (i < 0)
        return NULL;
    // cout<<"1111 "<<abs(count-i)<<endl;
    // cout<<"2222 "<<abs(i-idx)<<endl;
    // cout<<"3333 "<<abs(i)<<endl;
    if((abs(count-i)<abs(i-idx))&&(abs(count-i)<abs(i)))
    {
        idx=count;
        idx_p=head->pres;
    }
    else if((abs(i)<abs(count-i))&&(abs(i)<abs(i-idx)))
    {
        idx=0;
        idx_p=head;
    }
    while(idx>i)
    {
        idx_p=idx_p->pres;
        idx--;
        //  cout<<1<<endl;
    }
    while(idx<i)
    {
        idx_p=idx_p->next;
        idx++;
        //  cout<<2<<endl;
    }
    return idx_p;
}


template<class T>
List<T>::List(List& L)
{
    T copy_data;
    Node<T> *old_head=L.gethead();
    Node<T> *new_head=head=new Node<T>;

    idx=0;idx_p=new_head;
    while (old_head->next!=L.gethead())
    {
        copy_data=old_head->next->data;
        new_head->next=new Node<T>(copy_data,new_head);
        new_head=new_head->next;
        old_head=old_head->next;
    }
    new_head->next = head;
    head->pres=new_head;
    count=L.count;
};



template<class T>
List<T>& List<T>::operator=(List<T>& L)
{
    T copy_data;
    Node<T> * old_head = L.gethead();
    Node<T> * new_head = new Node<T>;

    idx=0;idx_p=new_head;
    while (old_head->next != L.gethead())
    {
        copy_data = old_head->next->data;
        new_head->next=new Node<T>(copy_data,new_head);
        old_head = old_head->next;
        new_head = new_head->next;
    }
    new_head->next = head;
    head->pres=new_head;
    count=L.count;
    return *this;
}


template<class T>
void List<T>::clear()
{
    Node<T> * del;
    head->pres->next=NULL;
    while (head->next != NULL)
    {
        del = head->next;
        head->next = del->next;
        delete del;
    }
    count=0;
};



template<class T>
int List<T>::length()const
{
    return count;
};


template<class T>
Node<T> * List<T>::search(T x)
{
    Node<T> * current = head->next;
    while (current != head)
    {
        if (current->data == x)
            break;
        else
            current = current->next;
    }
    return current;
};


template<class T>
bool List<T>::getData(int i, T& x)const
{
    if (i <= 0)
        return false;
    Node<T> * current = setPosition(i);
    if (current == NULL)
        return false;
    else
    {
        x = current->data;
        return true;
    }
}


template<class T>
void List<T>::setData(int i, T& x)
{
    if (i < 0)
        return;
    Node<T> * current = setPosition(i);
    if (current == NULL)
        return;
    else
    {
        current->data = x;
    }
}

template<class T>
bool List<T>::insert(int i, T& x)
{
    if (i < 0)
        return false;
    Node<T> * current = setPosition(i);
    // cout<<idx<<endl;
    if (NULL == current)
        return false;
    Node<T> * new_node = new Node<T>(x);
    if (new_node == NULL)
    {
        cout << "memory error!" << endl;
        exit(1);
    }
    new_node->next = current->next;
    current->next = new_node;
    new_node->pres=current;
    new_node->next->pres=new_node;
    count++;
    return true;
}

template<class T>
bool List<T>::remove(int i, T& x)
{
    // cout<<"count"<<count<<endl;
    if (i <= 0)
        return false;
    Node<T> * current = setPosition(i - 1);
    if (current == NULL || current->next == NULL)
        return false;
    Node<T> * del = current->next;
    // cout<<current->data<<'d'<<endl;
    if (del == NULL)
        return false;
    current->next = del->next;
    current->next->pres=current;
    x = del->data;
    delete del;
    count--;
    return true;
}


template<class T>
void List<T>::showData()
{
    Node<T> * current = head->next;
    while (current != head)
    {
        cout << current->data << "-";
        current = current->next;
    }
    cout<<endl;
}



template<class T>
bool List<T>::empty()const   
{
    return !count;
}