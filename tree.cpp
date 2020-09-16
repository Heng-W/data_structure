/**
  * @brief  二叉树与二叉排序树的实现
  */
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <iomanip>
#include <cstring>

using namespace std;

#define MAX(a,b) ((a)>(b)?(a):(b))

template<class T>

class Tree
{
private:
    struct Node
    {
        T data;
        Node* parent;
        Node* lchild, *rchild;

        Node(T d, Node* p = NULL, Node* l = NULL, Node* r = NULL):
            data(d), parent(p), lchild(l), rchild(r) {}

    }* root_;

    //递归删除结点
    void delAll(Node* p)
    {
        if (p)
        {
            delAll(p->lchild);
            delAll(p->rchild);
            delete p;
            p = NULL;
        }
    }

public:
    Tree(): root_(NULL)
    {

    }

    ~Tree()
    {
        delAll(root_);
        root_ = NULL;
    }

    //添加根结点
    void addroot(T data)
    {
        if (root_)
        {
            cout << "Root already exists" << endl;
        }
        else
        {
            root_ = new Node(data);
        }
    }

    //添加左孩子结点
    void addlchild(T cmpData, T addData)
    {
        Node* p = find(root_, cmpData);
        if (p == NULL)
        {
            cout << "Specified element is not found" << endl;
        }
        else if (p->lchild)
        {
            cout << "Left child already exists" << endl;
        }
        else
        {
            p->lchild = new Node(addData, p);
        }
    }

    //添加右孩子结点
    void addrchild(T cmpData, T addData)
    {
        Node* p = find(root_, cmpData);
        if (p == NULL)
        {
            cout << "Specified element is not found" << endl;
        }
        else if (p->rchild)
        {
            cout << "Right child already exists" << endl;
        }
        else
        {
            p->rchild = new Node(addData, p);
        }
    }

    //删除指定结点
    void del(T data)
    {
        Node* p = find(root_, data);
        if (p == NULL)
        {
            cout << "Specified element is not found " << endl;
        }
        else if (p == root_)
        {
            delAll(root_);
            root_ = NULL;
        }
        else
        {
            Node* node = p->parent;
            if (node->lchild == p)
                node->lchild = NULL;
            else
                node->rchild = NULL;
            delAll(p);
        }
    }

    //二叉排序树中插入结点
    void insert(T data)
    {
        Node* p = root_;
        while (1)
        {
            if (data < p->data)
            {
                if (p->lchild)
                {
                    p = p->lchild;
                    continue;
                }
                else
                {
                    p->lchild = new Node(data, p);
                    break;
                }
            }
            else
            {
                if (p->rchild)
                {
                    p = p->rchild;
                    continue;
                }
                else
                {
                    p->rchild = new Node(data, p);
                    break;
                }
            }
        }
    }

    //二叉排序树实现
    void arrangeTree(T a[], int len)
    {
        addroot(a[0]);
        for (int i = 1; i < len && a[i] != '\0'; i++)
        {
            insert(a[i]);
        }
        cout << "Binary sort tree: " << endl;
    }

    Node* find(Node* p, T data)
    {
        if (p == NULL)
        {
            return NULL;
        }
        else if (p->data == data)
        {
            return p;
        }
        else
        {
            Node* result = find(p->lchild, data);
            if (result)
                return result;
            else
                return find(p->rchild, data);
        }
    }

    int depth(Node* p)
    {
        if (p == NULL)
            return 0;
        else
            return MAX(depth(p->lchild), depth(p->rchild)) + 1;
    }

    //前序遍历
    void pre(Node* p)
    {
        if (p)
        {
            cout << setw(4) << p->data;
            pre(p->lchild);
            pre(p->rchild);
        }
    }

    //中序遍历
    void inorder(Node* p)
    {
        if (p)
        {
            inorder(p->lchild);
            cout << setw(4) << p->data;
            inorder(p->rchild);
        }
    }

    //后序遍历
    void post(Node* p)
    {
        if (p)
        {
            post(p->lchild);
            post(p->rchild);
            cout << setw(4) << p->data;
        }
    }

    void disp()
    {
        cout << "depth: " << depth(root_) << endl;
        cout << "preorder traversal: ";
        pre(root_);
        cout << endl;
        cout << "inorder traversal: ";
        inorder(root_);
        cout << endl;
        cout << "postorder traversal: ";
        post(root_);
        cout << endl << endl;
    }

};


int main()
{
    clock_t start = clock();
    srand(time(NULL));

    Tree<int> tree1;
    tree1.addroot(4);
    tree1.addroot(6);
    tree1.addlchild(4, 7);
    tree1.addrchild(7, 2);
    tree1.addrchild(4, 1);
    tree1.addrchild(2, 11);
    tree1.addlchild(7, 13);
    tree1.del(2);
    tree1.disp();

    Tree<char> tree2;
    char p[] = {"hzj$#maGcK&iP"};
    tree2.arrangeTree(p, strlen(p));
    tree2.disp();

    Tree<int> tree3;
    int num[20];
    int len = sizeof(num) / sizeof(*num);
    for (int i = 0; i < len; i++)
    {
        num[i] = rand() % 100;
    }
    tree3.arrangeTree(num, len);
    tree3.disp();

    clock_t end = clock();
    cout << "Running time: " << end - start << "/" << CLOCKS_PER_SEC << " s" << endl;
    cin.get();
    return 0;
}
