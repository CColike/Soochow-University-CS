#include<cstring>
#include<string>
#include<bits/stdc++.h>
using namespace std;

struct Node  
{
    string name="";
    int spc=0;
    Node *left=nullptr;
    Node *right=nullptr;
    Node(string n="",int s=0,Node *l=nullptr,Node *r=nullptr)
    {
        name=n;
        spc=s;
        left=l;
        right=r;
    }
    
};

class NTree
{
public:
    NTree(const vector<string> &name_data,int n);
    ~NTree(){clear(root);}
    // void check();

    bool search_child(string x,string y);
    bool search_sibling(string x,string y);
    bool search_descendant(string x,string y);
private:    
    Node *root,*new_node; 
    int read_cnt,cnt;
    Node *get_data(string name);
    void create(Node *db,const vector<string> &name_data);
    Node *search(Node *root,string s);
    void clear(Node *root);
};

NTree::NTree(const vector<string> &name_data,int n)
{
    root=new Node("!@#$",-1);
    // cout<<db<<' '<<root<<" dizhidizhi"<<endl;
    new_node=get_data(name_data[0]);
    // cout<<new_node->name<<"789"<<endl;
    read_cnt=1;
    cnt=n;
    create(root,name_data);
    // cout<<db<<' '<<root<<" dizhidizhi"<<endl;
    // if(db->left==nullptr)cout<<"!!!!!!!!!!!!!!"<<endl;
}

// void NTree::check()
// {
//     cout<<"check:"<<this->root->name<<endl;
//     if(search(root,"a"))cout<<"yes!"<<endl;
//     else cout<<"no!"<<endl;
//        cout<<root->left->right->left->name<<endl;
//     cout<<"!!!"<<endl;
//     cout<<root->left->name<<endl;
//     cout<<root->left->right->name<<endl;
//     cout<<root->left->left->name<<endl;
//     cout<<root->left->left->right->name<<endl;
//     cout<<root->name<<endl;
//     cout<<root->name<<endl;  
// }


void NTree::clear(Node *root)
{
    if(root->left!=nullptr)clear(root->left);
    if(root->right!=nullptr)clear(root->right);
    delete root;
}


Node *NTree::get_data(string name)
{
    int spc=0;
    while(name[spc]==' ')spc++;
    name=name.substr(spc);
    return new Node(name,spc,nullptr,nullptr);
}



void NTree::create(Node *db,const vector<string> &name_data)
{
    // cout<<"db::"<<db->name<<endl;
    if(db->name=="")
    {
        
        //  if(new_node->name=="a")cout<<db;
        db->name=new_node->name;
        // cout<<db->name<<endl;
        db->spc=new_node->spc;
        // db->left=nullptr;
        // db->right=nullptr;
        // cout<<"name:"<<db->name<<endl;
        // cout<<new_node->name<<endl;
        // if(root==nullptr)cout<<"!"<<endl;
        // if(db==nullptr)cout<<"!!"<<endl;
        if(read_cnt<=cnt-1)
        {
            // cout<<"readcnt:"<<read_cnt<<endl;
            delete new_node;
            // cout<<read_cnt<<endl;
            new_node=get_data(name_data[read_cnt]);
            // cout<<new_node->name<<' '<<new_node->spc<<endl;
        }
    
        if(read_cnt>=cnt)return;
        read_cnt++;
    }
    // cout<<"db->spc:"<<db->spc<<endl;
    // cout<<"db->name:"<<db->name<<endl;
    // cout<<new_node->spc<<endl;
    // cout<<new_node->name<<new_node->spc<<endl;
    // cout<<db->name<<db->spc<<endl;
    if(db->spc<new_node->spc)
    {
        if(db->left==nullptr){db->left=new Node();}

        // cout<<new_node->name<<"456"<<endl;
        create(db->left,name_data);
        // cout<<"db::"<<db->name<<endl;
        //  if(read_cnt>=cnt)return;
    } 
    if(db->spc==new_node->spc)
    {
        if(db->right==nullptr)db->right=new Node();
        create(db->right,name_data);
        // cout<<"db::"<<db->name<<endl;
        // if(read_cnt>=cnt)return;
    }
    if(db->spc>new_node->spc)return;
}

Node *NTree::search(Node *root,string s)
{
    //  cout<<root->name<<endl;
    //  cout<<this->root->name<<endl;
    Node *ans=nullptr;//注意不能直接返回search递归结果，因为不会保留当前进程
    //  cout<<"name:"<<root->name<<endl;
    if(root->name==s)return root;
    if(root->left!=nullptr) 
    {
        ans=search(root->left,s);
        if(ans!=nullptr)return ans;
    }
    //  cout<<"name:"<<root->name<<endl;
    if(root->right!=nullptr)
    {
        ans=search(root->right,s);
        if(ans!=nullptr)return ans;
    }
    return nullptr;
}


bool NTree::search_child(string x,string y)
{
    // cout<<this->root->name<<endl;
    // cout<<1<<endl;
    // cout<<x<<x.size()<<endl;
    // cout<<root<<' '<<root->name<<endl;
    Node *temp=search(this->root,x);
    // cout<<temp->name<<endl;
    // cout<<"11111111110"<<endl;
    if(temp->left==nullptr)return false;
    // cout<<1<<endl;
    // cout<<"22222222222222"<<endl;
    temp=temp->left;
    // cout<<temp->name<<endl;
    while(temp->name!=y&&temp->right!=nullptr)
    {
         cout<<temp->name<<endl;
        temp=temp->right;
        // cout<<temp->name<<endl;
    }
    //  cout<<"root:"<<this->root->name<<endl;
    if(temp->name!=y)return false;
    return true;
}


bool NTree::search_sibling(string x,string y)
{
    Node *temp1=search(root,x),*temp2=search(root,y);
    Node *t1=temp1,*t2=temp2;
    if(temp1==temp2)return false;
    while(t1!=nullptr)
    {
        t1=t1->right;
        if(t1==temp2)return true;
    }
    while(t2!=nullptr)
    {
        t2=t2->right;
        if(t2==temp1)return true;
    }
    return false;
}


bool NTree::search_descendant(string x,string y)
{
    Node *temp=search(root,x);
    if(temp->left==nullptr)return false;
    return search(root->left,y)!=nullptr;
    // bool tag1= Search_Descendant(temp->left,y),tag2;
    // if(search(root->left,y)!=nullptr)tag2=true;
    // else tag2=false;
    // if(tag1!=tag2)cout<<"!!!!!!!!!!!!!!!"<<endl;   
}

// bool NTree::Search_Descendant(Node *temp,string s)
// {
//     if(temp->name==s)return true;
//     bool b1=false,b2=false;
//     if(temp->left!=nullptr) b1=Search_Descendant(temp->left,s);
//     if(temp->right!=nullptr)b2=Search_Descendant(temp->right,s);
//     if(b1||b2)return true;
//     else return false;
// }