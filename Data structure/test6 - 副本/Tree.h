#include<string>
#include<cstring>
#include<iostream>
using namespace std;

struct Node
{
    char c;
    Node *left;
    Node *right;

    // Node();
    // Node(char inpt);
};

// Node::Node()////////////////
// {
//     c='#';
//     left=nullptr;
//     right=nullptr;
// }

// Node::Node(char inpt)
// {
//     c=inpt;
//     left=nullptr;
//     right=nullptr;
// }

class Tree
{
public:
    Tree(){root=create();}//�����������ʹ�����
    ~Tree(){release(root);}
    void preorder(){pre_order(root);}
    void inorder(){in_order(root);}
    void postorder(){post_order(root);}
    void levelorder(){level_order(root);}//ÿ�ε����Ҷ�����
    int getdepth(){get_depth(root,0);return depth;}
    int getwidth(){get_width(root,0);return width;}
    void getdegree(int &d0,int &d1,int &d2){get_degree(root,0);d0=degree_arr[0];d1=degree_arr[1];d2=degree_arr[2];}


private:
    Node *root;
    int width_arr[10000],degree_arr[4];///100->N
    int depth=0,width=0;

    Node *create();
    void release(Node *root);
    // void create(const string &s);
    void pre_order(Node *root);// preorderǰ��
    void in_order(Node *root);// inorder����
    void post_order(Node *root);// postorder����
    void level_order(Node *root);// levelorder����
    void get_depth(Node *root,int cnt);
    void get_width(Node *root,int cnt);
    void get_degree(Node *root,int flag);
   };

void Tree::pre_order(Node *root) 
{
    if(root == nullptr)return;
    else
    {
        cout<<root->c<<' ';
        pre_order(root->left);
        pre_order(root->right);
    }
}

void Tree::post_order(Node *root) 
{
    if(root == nullptr)return;
    else
    {
        post_order(root->left);
        post_order(root->right);
        cout<<root->c<<' ';
    }
}

void Tree::in_order(Node *root) 
{
    if(root == nullptr)return;
    else
    {
        in_order(root->left);
        cout<<root->c<<' ';
        in_order(root->right);
    }
}

void Tree::level_order(Node *root)
{
    Node *Q[100],*q=nullptr;
    int front=-1,rear=-1;
    if(root==nullptr)return;
    Q[++rear]=root;
    while(front!=rear)
    {
        q=Q[++front];
        cout<<q->c<<' ';
        if(q->left !=nullptr)Q[++rear]=q->left;
        if(q->right!=nullptr)Q[++rear]=q->right;
    }
}

Node *Tree::create()
{
    Node *root;
    char ch;
    cin>>ch;
    if(ch=='#')root=nullptr;
    else
    {
        root=new Node;
        root->c=ch;
        root->left=create();
        root->right=create();
        cout<<"���"<<ch<<endl;
        if(root->left!=nullptr)cout<<"    ������"<<root->left->c<<endl;
        else cout<<"    û������"<<endl;
        if(root->right!=nullptr)cout<<"    ���Һ���"<<root->right->c<<endl;
        else cout<<"    û���Һ���"<<endl;
    }
    return root;
}

void Tree::release(Node *root)
{
    if(root==nullptr)return;
    else
    {
        release(root->left);
        release(root->right);
        delete root;
    }
}

///////////////////////////////////////////////////////////

void Tree::get_depth(Node *root,int cnt=0)
{
    if(!cnt)depth=0;
    if(root==nullptr)return;
    cnt++;
    depth=max(depth,cnt);
    get_depth(root->left,cnt);
    get_depth(root->right,cnt);
}

void Tree::get_width(Node *root,int cnt=0)
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

void Tree::get_degree(Node *root,int flag=0)
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

