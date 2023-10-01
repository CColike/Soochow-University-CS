#include<stdlib.h>
#include<iostream>

using namespace std;

template<class T>
struct Node 
{
    T data;
    Node<T>* next;

    Node(Node<T> *p=NULL)
    {
        next = p;
    }
    Node(T& item,Node<T>*p=NULL)
    {
        data=item;
        next=p;
    }
};


template<class T>
class List
{
private:
    Node<T> * head;                                   
    
public:
    List(){ head=new Node<T>; }   //带头结点 head就是一个node                   
    List(const T& x){ head=new Node<T>(x); }        
    List(List<T>& L);                                   
    List<T>& operator=(List<T>& L);                     
    ~List(){ clear(); }                                   

    Node<T> *setPosition(int i);                       
     
    void clear();                           
    int length()const;                              
    Node<T> *getHead()const{ return head; }         
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
    if (i < 0)
        return NULL;
    Node<T> * current = head;
    int k = 0;
    while (current!=NULL&&k<i){
        current = current->next;
        k++;
    }
    return current;
}


template<class T>
List<T>::List(List& L)
{
    T copy_data;
    Node<T> *old_head=L.getHead();
    Node<T> *new_head=head=new Node<T>;

    while (old_head->next!=NULL)
    {
        copy_data=old_head->next->data;
        new_head->next=new Node<T>(copy_data);
        new_head=new_head->next;
        old_head=old_head->next;
    }
    new_head->next = NULL;
};



template<class T>
void List<T>::clear()
{
    Node<T> * del;
    while (head->next != NULL)
    {
        del = head->next;
        head->next = del->next;
        delete del;
    }
};



template<class T>
int List<T>::length()const
{
    Node<T>* q = head->next;
    int count = 0;
    while (q != NULL)
    {
        q = q->next;
        count++;
    }
    return count;
};


template<class T>
Node<T> * List<T>::search(T x)
{
    Node<T> * current = head->next;
    while (current != NULL)
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
    return true;
}

template<class T>
bool List<T>::remove(int i, T& x)
{
    if (i <= 0)
        return false;
    Node<T> * current = setPosition(i - 1);
    if (current == NULL || current->next == NULL)
        return false;
    Node<T> * del = current->next;
    if (del == NULL)
        return false;
    current->next = del->next;
    x = del->data;
    delete del;
    return true;
}


template<class T>
void List<T>::showData()
{
    Node<T> * current = head->next;
    while (current != NULL)
    {
        cout << current->data << "-";
        current = current->next;
    }
    cout<<endl;
}


template<class T>
List<T>& List<T>::operator=(List<T>& L)
{
    T copy_data;
    Node<T> * old_head = L.getHead();
    Node<T> * new_head = new Node<T>;
    while (old_head->next != NULL)
    {
        copy_data = old_head->next->data;
        new_head->next = new Node<T>(copy_data);
        old_head = old_head->next;
        new_head = new_head->next;
    }
    new_head->next = NULL;
    return *this;
}

template<class T>
bool List<T>::empty()const   
{
    return head->next==NULL;
}