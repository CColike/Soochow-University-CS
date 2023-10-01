#include<bits/stdc++.h>
#include"BTree.h"
#include"Tree.h"
using namespace std;



int main()
{
    int ask1=-1,ask2=-1,ask3=-1;
    while(ask1!=0)
    {
        cout<<"请问您想演示哪种树：1.二叉树 2.二叉查找树 0.退出程序"<<endl;
        cin>>ask1;
        if(ask1==1)
        {
            cout<<"请手动输入一棵树的先序遍历（空结点用#代替,例如：AB#D##CE#F###）"<<endl;
            Tree t1;//建树过程
            ask2=-1;
            
            while(ask2!=0)
            {
                cout<<endl;
                cout<<"1.输出先序遍历顺序"<<endl;
                cout<<"2.输出中序遍历顺序"<<endl;
                cout<<"3.输出后序遍历顺序"<<endl;
                cout<<"4.输出层序遍历顺序"<<endl;
                cout<<"5.输出树的深度"<<endl;
                cout<<"6.输出树的宽度"<<endl;
                cout<<"7.统计度为0，1，2的结点数"<<endl;
                cout<<"0.返回"<<endl;
                cin>>ask2;
                if(ask2==1)
                {
                    cout<<"先序遍历："<<endl;
                    t1.preorder();cout<<endl;
                }
                if(ask2==2)
                {
                    cout<<"中序遍历："<<endl;
                    t1.inorder();cout<<endl;
                }
                if(ask2==3)
                {
                    cout<<"后序遍历："<<endl;
                    t1.postorder();cout<<endl;
                }
                if(ask2==4)
                {
                    cout<<"层序遍历："<<endl;
                    t1.levelorder();cout<<endl;
                }
                if(ask2==5)
                {
                    cout<<"树的深度："<<endl;
                    cout<<t1.getdepth()<<endl;
                }
                if(ask2==6)
                {
                    cout<<"树的宽度："<<endl;
                    cout<<t1.getwidth()<<endl;
                }
                if(ask2==7)
                {
                    int cnt0,cnt1,cnt2;
                    t1.getdegree(cnt0,cnt1,cnt2);
                    cout<<"度为0的结点共有:"<<cnt0<<"条"<<endl;
                    cout<<"度为1的结点共有:"<<cnt1<<"条"<<endl;
                    cout<<"度为2的结点共有:"<<cnt2<<"条"<<endl;
                }
                if(ask2==0)
                {
                    cout<<"返回"<<endl;
                    break;
                }
            }
        }
        if(ask1==2)
        {
            int n;
            cout<<"请输入二叉查找树的结点个数与每个结点的值："<<endl;
            cout<<"请输入结点个数：";cin>>n;
            cout<<"请输入各个结点的值（中间以空格间隔）";BTree t2(n);
            ask2=-1;
            
            while(ask2!=0)
            {
                cout<<endl;
                cout<<"1.输出先序遍历顺序"<<endl;
                cout<<"2.输出中序遍历顺序"<<endl;
                cout<<"3.输出后序遍历顺序"<<endl;
                cout<<"4.输出层序遍历顺序"<<endl;
                cout<<"5.输出树的深度"<<endl;
                cout<<"6.输出树的宽度"<<endl;
                cout<<"7.统计度为0，1，2的结点数"<<endl;
                cout<<"8.插入结点"<<endl;
                cout<<"9.删除特定值的结点"<<endl;
                cout<<"10.查找目标值在树中是否存在"<<endl;
                cout<<"0.返回"<<endl;
                cin>>ask2;
                if(ask2==1)
                {
                    cout<<"先序遍历："<<endl;
                    t2.preorder();cout<<endl;
                }
                if(ask2==2)
                {
                    cout<<"中序遍历："<<endl;
                    t2.inorder();cout<<endl;
                }
                if(ask2==3)
                {
                    cout<<"后序遍历："<<endl;
                    t2.postorder();cout<<endl;
                }
                if(ask2==4)
                {
                    cout<<"层序遍历："<<endl;
                    t2.levelorder();cout<<endl;
                }
                if(ask2==5)
                {
                    cout<<"树的深度："<<endl;
                    cout<<t2.getdepth()<<endl;
                }
                if(ask2==6)
                {
                    cout<<"树的宽度："<<endl;
                    cout<<t2.getwidth()<<endl;
                }
                if(ask2==7)
                {
                    int cnt0,cnt1,cnt2;
                    t2.getdegree(cnt0,cnt1,cnt2);
                    cout<<"度为0的结点共有:"<<cnt0<<"条"<<endl;
                    cout<<"度为1的结点共有:"<<cnt1<<"条"<<endl;
                    cout<<"度为2的结点共有:"<<cnt2<<"条"<<endl;
                }
                if(ask2==8)
                {
                    cout<<"请输入需要插入的结点的值："<<endl;
                    int temp;cin>>temp;
                    t2.insert(temp);
                    cout<<"插入成功"<<endl;
                }
                if(ask2==9)
                {
                    cout<<"请输入需要删除的结点的值"<<endl;
                    int temp;cin>>temp;
                    if(t2.remove(temp))cout<<"删除成功"<<endl;
                    else cout<<"删除失败，树中没有输入的值的结点"<<endl;
                }
                if(ask2==10)
                {
                    cout<<"请输入需要查找结点的值"<<endl;
                    int temp;cin>>temp;
                    if(t2.search(temp))cout<<"查找成功，树中有您需要查找的值"<<endl;
                    else cout<<"未查找到，树中没有您查找的值"<<endl;
                }
                if(ask2==0)
                {
                    cout<<"返回"<<endl;
                    break;
                }
            }
        }
        if(!ask1)exit(0);

    }
}