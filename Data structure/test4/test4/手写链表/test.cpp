#include"DanLianBiao.h"
using namespace std;

int main()
{
    int i = 0,x=1;
    List<int> L;
    L.insert(0,x);
    L.showData();
    x=2;
    L.insert(1,x);
    x=3;
    L.insert(1,x);
    List<int> LL=L;
    cout<<L.length()<<endl;
    L.showData();
    LL.showData();
    LL.setData(1,x);
    L.showData();
    LL.showData();
    L.remove(1,x);
    cout<<x<<endl;
    L.showData();
    return 0;
}