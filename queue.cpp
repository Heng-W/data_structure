/**
  * @brief  链表实现的队列
  */
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <iomanip>

using namespace std;

template<class T>

class Queue
{
private:
    struct Node
    {
        T data;
        Node* next;

        Node(T d, Node* n = NULL): data(d), next(n) {}
    }* head_, *tail_;

    int len_;//长度

public:
    Queue(): head_(NULL), tail_(NULL), len_(0) {}

    ~Queue()
    {
        Node* p = head_;
        while (p)
        {
            head_ = head_->next;
            delete p;
            p = head_;
        }
    }

    //加入队列
    void enQueue(T data)
    {
        Node* p = new Node(data);
        if (isEmpty())
        {
            head_ = p;
            tail_ = p;
        }
        else
        {
            tail_->next = p;
            tail_ = p;
        }
        len_++;
    }

    bool isEmpty()
    {
        return len_ == 0;
    }

    //弹出队列
    T deQueue()
    {
        Node* p = head_;
        T data = p->data;
        head_ = head_->next;
        delete p;
        len_--;
        if (len_ == 0)
        {
            head_ = tail_ = NULL;
        }
        return data;
    }

    int getLength()
    {
        return len_;
    }

};


int main()
{
    srand(time(NULL));
    Queue<int> q;
    cout << "en queue" << endl;
    for (int i = 0; i < 5; i++)
    {
        int data = rand() * 100 / RAND_MAX;
        q.enQueue(data);
        cout << data << "  enQueue" << endl;
    }
    cout << endl;
    cout << "de queue" << endl;
    while (!q.isEmpty())
    {
        cout << q.deQueue() << "  deQueue" << endl;
    }
    cin.get();
    return 0;
}
