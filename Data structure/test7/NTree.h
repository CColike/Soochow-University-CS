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
    new_node=get_data(name_data[0]);
    read_cnt=1;
    cnt=n;
    create(root,name_data);
}


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
    if(db->name=="")
    {
        db->name=new_node->name;
        db->spc=new_node->spc;
        if(read_cnt<=cnt-1)
        {
            delete new_node;
            new_node=get_data(name_data[read_cnt]);
        }
    
        if(read_cnt>=cnt)return;
        read_cnt++;
    }
    if(db->spc<new_node->spc)
    {
        if(db->left==nullptr){db->left=new Node();}

        create(db->left,name_data);
    } 
    if(db->spc==new_node->spc)
    {
        if(db->right==nullptr)db->right=new Node();
        create(db->right,name_data);
    }
    if(db->spc>new_node->spc)return;
}

Node *NTree::search(Node *root,string s)
{
    Node *ans=nullptr;
    if(root->name==s)return root;
    if(root->left!=nullptr) 
    {
        ans=search(root->left,s);
        if(ans!=nullptr)return ans;
    }
    if(root->right!=nullptr)
    {
        ans=search(root->right,s);
        if(ans!=nullptr)return ans;
    }
    return nullptr;
}


bool NTree::search_child(string x,string y)
{
    Node *temp=search(this->root,x);
    if(temp->left==nullptr)return false;
    temp=temp->left;
    while(temp->name!=y&&temp->right!=nullptr)
    {
        temp=temp->right;
    }
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
}
