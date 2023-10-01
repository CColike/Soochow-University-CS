#include<string>
#include<cstring>
#include<iostream>
using namespace std;

struct BNode
{
    int  data;
    BNode *left;
    BNode *right;

};


class BTree
{
public:
    BTree(int n=0){create(n);}
    ~BTree(){release(root);}
    void preorder(){pre_order(root);}
    void inorder(){in_order(root);}
    void postorder(){post_order(root);}
    void levelorder(){level_order(root);}//每次调用我都更新
    int getdepth(){get_depth(root,0);return depth;}
    int getwidth(){get_width(root,0);return width;}
    void getdegree(int &d0,int &d1,int &d2){get_degree(root,0);d0=degree_arr[0];d1=degree_arr[1];d2=degree_arr[2];}
    void insert(int new_data){root=Insert(root,new_data);}
    bool search(int target){if(Search(root,target)!=nullptr)return true;else return false;}
    bool remove(int target){return Remove(root,root,'#',target);}

private:
    BNode *root;
    int width_arr[10000],degree_arr[4];///100->N
    int depth=0,width=0;

    void *create(int n);
    void release(BNode *root);
    void pre_order(BNode *root);// preorder前序
    void in_order(BNode *root);// inorder中序
    void post_order(BNode *root);// postorder后序
    void level_order(BNode *root);// levelorder层序
    void get_depth(BNode *root,int cnt);
    void get_width(BNode *root,int cnt);
    void get_degree(BNode *root,int flag);
    BNode *Insert(BNode *root,int new_data);
    BNode *Search(BNode *root,int target);
    bool Remove(BNode *root,BNode *parent,char child,int target);
   };

void BTree::pre_order(BNode *root) 
{
    if(root == nullptr)return;
    else
    {
        cout<<root->data<<' ';
        pre_order(root->left);
        pre_order(root->right);
    }
}

void BTree::post_order(BNode *root) 
{
    if(root == nullptr)return;
    else
    {
        post_order(root->left);
        post_order(root->right);
        cout<<root->data<<' ';
    }
}

void BTree::in_order(BNode *root) 
{
    if(root == nullptr)return;
    else
    {
        in_order(root->left);
        cout<<root->data<<' ';
        in_order(root->right);
    }
}

void BTree::level_order(BNode *root)
{
    BNode *Q[10000],*q=nullptr;
    int front=-1,rear=-1;
    if(root==nullptr)return;
    Q[++rear]=root;
    while(front!=rear)
    {
        q=Q[++front];
        cout<<q->data<<' ';
        if(q->left !=nullptr)Q[++rear]=q->left;
        if(q->right!=nullptr)Q[++rear]=q->right;
    }
}

void *BTree::create(int n=0)
{
    int new_data;
    root=nullptr;
    // cout<<n<<endl;
    while(n--)
    {
        cin>>new_data;
        root=Insert(root,new_data);
    }
}

void BTree::release(BNode *root)
{
    if(root==nullptr)return;
    else
    {
        release(root->left);
        release(root->right);
        delete root;
    }
}


void BTree::get_depth(BNode *root,int cnt=0)
{
    if(!cnt)depth=0;
    if(root==nullptr)return;
    cnt++;
    depth=max(depth,cnt);
    get_depth(root->left,cnt);
    get_depth(root->right,cnt);
}

void BTree::get_width(BNode *root,int cnt=0)
{
    if(!cnt)
    {
        memset(width_arr,0,sizeof(width_arr));
        width=0;
    }
    if(root==nullptr)return;
    cnt++;
    width_arr[cnt]++;
    width=max(width,width_arr[cnt]);
    get_width(root->left,cnt);
    get_width(root->right,cnt);
}

void BTree::get_degree(BNode *root,int flag=0)
{
    if(!flag) memset(degree_arr,0,sizeof(degree_arr));
    int son=0;
    if(root->left!=nullptr)
    {
        get_degree(root->left,1);
        son++;
    }
    if(root->right!=nullptr)
    {
        get_degree(root->right,1);
        son++;
    }
    degree_arr[son]++;
    // cout<<"c:"<<root->c<<"son:"<<son<<endl;
}

BNode *BTree::Insert(BNode *root,int new_data)
{

    // cout<<"newdata:"<<new_data<<endl;
    if(root==nullptr) 
    {
        // cout<<"YES!!"<<endl;
        root=new BNode;
        root->data=new_data;
        root->left=nullptr;
        root->right=nullptr;
        // if(root==nullptr)cout<<"NO!"<<endl;
        return root;
    }
    if(new_data<=root->data)
    {
        // cout<<'n'<<endl;
        root->left=Insert(root->left,new_data);
        return root;
    }
    else
    {
        // cout<<'n'<<endl;
        root->right=Insert(root->right,new_data);
        return root;
    }
}

BNode *BTree::Search(BNode *root,int target)
{
    if(root==nullptr)return root;
    if(target==root->data)return root;
    if(target<root->data)return Search(root->left,target);
    if(target>root->data)return Search(root->right,target); 
}

bool BTree::Remove(BNode *root,BNode *parent,char child,int target)
{
    if(root->data==target)
    {
        if(root->left==nullptr&&root->right==nullptr)
        {
            if(child=='#')
            {
                delete root;
                root=nullptr;
            }
            else if (child=='l')
            {
                delete root;
                parent->left=nullptr;
            }
            else
            {
                delete root;
                parent->right=nullptr;
            }
            return true;
        }
        if(root->left!=nullptr&&root->right==nullptr)
        {
            if(child=='#')
            {
                root=root->left;
                delete parent;
                this->root=root;
            }
            if(child=='l')
            {
                parent->left=root->left;
                delete root;
            }
            if(child=='r')
            {
                parent->right=root->left;
                delete root;
            }
            return true;
        }
        if(root->left==nullptr&&root->right!=nullptr)
        {
            if(child=='#')
            {
                root=root->right;
                delete parent;
                this->root=root;
            }
            if(child=='l')
            {
                parent->left=root->right;
                delete root;
            }
            if(child=='r')
            {
                parent->right=root->right;
                delete root;
            }
            return true;
        }
        if(root->left!=nullptr&&root->right!=nullptr)
        {
            BNode *temp_node=root->right;
            if(temp_node->left==nullptr)
            {
                if(child=='#')
                {
                    temp_node->left=root->left;
                    delete root;
                    this->root=temp_node;
                    return true;
                }
                if(child=='l')
                {
                    temp_node->left=root->left;
                    parent->left=temp_node;
                    delete root;
                    return true;
                }
                if(child=='r')
                {
                    temp_node->left=root->left;
                    parent->right=temp_node;
                    delete root;
                    return true;
                }
            }
            while(temp_node->left->left!=nullptr)temp_node=temp_node->left;
            root->data=temp_node->left->data;
            delete temp_node->left;
            temp_node->left=nullptr;
            return true;
        }
    }
    else
    {
        bool f1=false,f2=false;
        if(root->left!=nullptr)
        {
            f1=Remove(root->left,root,'l',target);
        }
        if(root->right!=nullptr)
        {
            f2=Remove(root->right,root,'r',target);
        }
        if(f1==false&&f2==false)return false;
        else return true;
    }
}