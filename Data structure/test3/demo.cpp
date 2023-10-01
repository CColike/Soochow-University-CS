#include"Queue.h"
using namespace std;

int main()
{
    Queue<int> q;
    int a;
    q.append(1);
    q.append(2);
    q.append(3);
    q.reverse_append(4);
    q.retrieve(a);
    cout<<a;
    q.serve();
    q.retrieve(a);
    cout<<a;
    q.serve();
    q.retrieve(a);
    cout<<a;
    q.serve();
    q.retrieve(a);
    cout<<a;
    q.serve();
    q.retrieve(a);
    cout<<a;
    q.serve();
    
}