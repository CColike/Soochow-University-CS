#include<bits/stdc++.h>
#include"BTree.h"
#include"Tree.h"
using namespace std;



int main()
{
    int ask1=-1,ask2=-1,ask3=-1;
    while(ask1!=0)
    {
        cout<<"����������ʾ��������1.������ 2.��������� 0.�˳�����"<<endl;
        cin>>ask1;
        if(ask1==1)
        {
            cout<<"���ֶ�����һ����������������ս����#����,���磺AB#D##CE#F###��"<<endl;
            Tree t1;//��������
            ask2=-1;
            
            while(ask2!=0)
            {
                cout<<endl;
                cout<<"1.����������˳��"<<endl;
                cout<<"2.����������˳��"<<endl;
                cout<<"3.����������˳��"<<endl;
                cout<<"4.����������˳��"<<endl;
                cout<<"5.����������"<<endl;
                cout<<"6.������Ŀ��"<<endl;
                cout<<"7.ͳ�ƶ�Ϊ0��1��2�Ľ����"<<endl;
                cout<<"0.����"<<endl;
                cin>>ask2;
                if(ask2==1)
                {
                    cout<<"���������"<<endl;
                    t1.preorder();cout<<endl;
                }
                if(ask2==2)
                {
                    cout<<"���������"<<endl;
                    t1.inorder();cout<<endl;
                }
                if(ask2==3)
                {
                    cout<<"���������"<<endl;
                    t1.postorder();cout<<endl;
                }
                if(ask2==4)
                {
                    cout<<"���������"<<endl;
                    t1.levelorder();cout<<endl;
                }
                if(ask2==5)
                {
                    cout<<"������ȣ�"<<endl;
                    cout<<t1.getdepth()<<endl;
                }
                if(ask2==6)
                {
                    cout<<"���Ŀ�ȣ�"<<endl;
                    cout<<t1.getwidth()<<endl;
                }
                if(ask2==7)
                {
                    int cnt0,cnt1,cnt2;
                    t1.getdegree(cnt0,cnt1,cnt2);
                    cout<<"��Ϊ0�Ľ�㹲��:"<<cnt0<<"��"<<endl;
                    cout<<"��Ϊ1�Ľ�㹲��:"<<cnt1<<"��"<<endl;
                    cout<<"��Ϊ2�Ľ�㹲��:"<<cnt2<<"��"<<endl;
                }
                if(ask2==0)
                {
                    cout<<"����"<<endl;
                    break;
                }
            }
        }
        if(ask1==2)
        {
            int n;
            cout<<"���������������Ľ�������ÿ������ֵ��"<<endl;
            cout<<"�������������";cin>>n;
            cout<<"�������������ֵ���м��Կո�����";BTree t2(n);
            ask2=-1;
            
            while(ask2!=0)
            {
                cout<<endl;
                cout<<"1.����������˳��"<<endl;
                cout<<"2.����������˳��"<<endl;
                cout<<"3.����������˳��"<<endl;
                cout<<"4.����������˳��"<<endl;
                cout<<"5.����������"<<endl;
                cout<<"6.������Ŀ��"<<endl;
                cout<<"7.ͳ�ƶ�Ϊ0��1��2�Ľ����"<<endl;
                cout<<"8.������"<<endl;
                cout<<"9.ɾ���ض�ֵ�Ľ��"<<endl;
                cout<<"10.����Ŀ��ֵ�������Ƿ����"<<endl;
                cout<<"0.����"<<endl;
                cin>>ask2;
                if(ask2==1)
                {
                    cout<<"���������"<<endl;
                    t2.preorder();cout<<endl;
                }
                if(ask2==2)
                {
                    cout<<"���������"<<endl;
                    t2.inorder();cout<<endl;
                }
                if(ask2==3)
                {
                    cout<<"���������"<<endl;
                    t2.postorder();cout<<endl;
                }
                if(ask2==4)
                {
                    cout<<"���������"<<endl;
                    t2.levelorder();cout<<endl;
                }
                if(ask2==5)
                {
                    cout<<"������ȣ�"<<endl;
                    cout<<t2.getdepth()<<endl;
                }
                if(ask2==6)
                {
                    cout<<"���Ŀ�ȣ�"<<endl;
                    cout<<t2.getwidth()<<endl;
                }
                if(ask2==7)
                {
                    int cnt0,cnt1,cnt2;
                    t2.getdegree(cnt0,cnt1,cnt2);
                    cout<<"��Ϊ0�Ľ�㹲��:"<<cnt0<<"��"<<endl;
                    cout<<"��Ϊ1�Ľ�㹲��:"<<cnt1<<"��"<<endl;
                    cout<<"��Ϊ2�Ľ�㹲��:"<<cnt2<<"��"<<endl;
                }
                if(ask2==8)
                {
                    cout<<"��������Ҫ����Ľ���ֵ��"<<endl;
                    int temp;cin>>temp;
                    t2.insert(temp);
                    cout<<"����ɹ�"<<endl;
                }
                if(ask2==9)
                {
                    cout<<"��������Ҫɾ���Ľ���ֵ"<<endl;
                    int temp;cin>>temp;
                    if(t2.remove(temp))cout<<"ɾ���ɹ�"<<endl;
                    else cout<<"ɾ��ʧ�ܣ�����û�������ֵ�Ľ��"<<endl;
                }
                if(ask2==10)
                {
                    cout<<"��������Ҫ���ҽ���ֵ"<<endl;
                    int temp;cin>>temp;
                    if(t2.search(temp))cout<<"���ҳɹ�������������Ҫ���ҵ�ֵ"<<endl;
                    else cout<<"δ���ҵ�������û�������ҵ�ֵ"<<endl;
                }
                if(ask2==0)
                {
                    cout<<"����"<<endl;
                    break;
                }
            }
        }
        if(!ask1)exit(0);

    }
}