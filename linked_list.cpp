/**
  * @brief  双向链表实现的线性表
  */
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <iomanip>

using namespace std;

template<class T>

class LinkedList
{
private:
    struct Node
    {
        T data;
        Node* prev;
        Node* next;

        Node(T d, Node* p = NULL, Node* n = NULL):
            data(d), prev(p), next(n) {}
    }* head_, *tail_; //头结点，尾结点

    int nodeCnt_;//结点个数


    //寻找指定结点
    Node* find(T data)
    {
        Node* p = head_->next;
        while (p != tail_)
        {
            if (p->data == data) return p;
            p = p->next;
        }
        return NULL;
    }

    void insertBetween(T data, Node* prev, Node* next)
    {
        Node* p = new Node(data, prev, next);
        prev->next = p;
        next->prev = p;
    }

public:
    LinkedList(): nodeCnt_(0)
    {
        head_ = new Node(0);
        tail_ = new Node(0, head_);
        head_->next = tail_;
    }

    ~LinkedList()
    {
        Node* p = head_;
        while (p)
        {
            head_ = head_->next;
            delete p;
            p = head_;
        }
    }

    //表头插入
    void insertFirst(T data)
    {
        insertBetween(data, head_, head_->next);
        nodeCnt_++;
    }

    //表尾插入
    void insertLast(T data)
    {
        insertBetween(data, tail_->prev, tail_);
        nodeCnt_++;
    }

    //指定结点前插入
    void insertBefore(T target, T data)
    {
        Node* p = find(target);
        if (p == NULL)
        {
            cout << "Specified element is not found" << endl;
            return;
        }
        insertBetween(data, p->prev, p);
        nodeCnt_++;
    }

    //指定结点后插入
    void insertAfter(T target, T data)
    {
        Node* p = find(target);
        if (p == NULL)
        {
            cout << "Specified element is not found" << endl;
            return;
        }
        insertBetween(data, p, p->next);
        nodeCnt_++;
    }

    //删除
    void del(T data)
    {
        Node* p = find(data);
        if (p == NULL)
        {
            cout << "Specified element is not found" << endl;
            return;
        }
        p->prev->next = p->next;
        p->next->prev = p->prev;
        delete p;
        p = NULL;
        nodeCnt_--;
    }

    int getLength()
    {
        return nodeCnt_;
    }

    //遍历
    void traversal()
    {
        Node* p = head_->next;
        while (p != tail_)
        {
            cout << p->data << ' ';
            p = p->next;
        }
    }

};

int main()
{
    clock_t start = clock();
    srand(time(NULL));

    float a[5];
    cout << "origin: ";
    for (int i = 0; i < 5; i++)
    {
        a[i] = 100.0 * rand() / (RAND_MAX + 1.0);
        cout << a[i] << "  ";
    }
    cout << endl;

    LinkedList<float> list;
    list.insertFirst(a[0]);
    list.insertAfter(a[0], a[1]);
    list.insertBefore(a[0], a[2]);
    list.insertLast(a[3]);
    list.del(a[0]);
    list.insertFirst(a[4]);
    cout << "Traversal: ";
    list.traversal();
    cout << endl;
    cout << "Total number of elements: " << list.getLength() << endl;

    clock_t end = clock();
    cout << "Running time: " << end - start << "/" << CLOCKS_PER_SEC << " s" << endl;
    cin.get();
    return 0;
}
