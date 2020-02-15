/**
  * @brief  数组实现的队列
  */
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <iomanip>

using namespace std;

template<class T>

class ArrayQueue
{
private:
    T* data_;
    int cap_;//数组容量
    int headIdx_, tailIdx_;//头索引和尾索引


    //数组扩容
    void resize()
    {
        T* oldData = data_;
        int newCap = cap_ * 2;
        data_ = new T[newCap];
        for (int i = 0; i < cap_; i++)
        {
            if (headIdx_ < tailIdx_)
            {
                data_[i] = oldData[i];
            }
            else
            {
                if (i < cap_ - headIdx_)
                {
                    data_[i] = oldData[i + headIdx_];
                }
                else
                {
                    data_[i] = oldData[i + headIdx_ - cap_];
                }
            }
        }
        headIdx_ = 0;
        tailIdx_ = cap_ - 1;
        cap_ = newCap;
        delete [] oldData;
    }

public:
    ArrayQueue(int cap = 4): cap_(cap), headIdx_(-1), tailIdx_(-1)
    {
        data_ = new T[cap];
    }

    ~ArrayQueue()
    {
        delete [] data_;
    }

    bool isFull()
    {
        return (tailIdx_ + 1) % cap_ == headIdx_;
    }

    bool isEmpty()
    {
        return headIdx_ == -1;
    }

    void enQueue(T e)
    {
        if (isFull())
        {
            resize();
        }
        if (isEmpty())
        {
            headIdx_ = 0;
        }
        tailIdx_ = (tailIdx_ + 1) % cap_;
        data_[tailIdx_] = e;
    }

    T deQueue()
    {
        T e = data_[headIdx_];
        if (headIdx_ == tailIdx_)
        {
            headIdx_ = tailIdx_ = -1;
        }
        else
        {
            headIdx_ = (headIdx_ + 1) % cap_;
        }
        return e;
    }

    //实际元素数量
    int getLength()
    {
        if (isEmpty())
            return 0;
        if (headIdx_ <= tailIdx_)
            return tailIdx_ - headIdx_ + 1;
        return cap_ - headIdx_ + tailIdx_ + 1;
    }

    int getCapacity()
    {
        return cap_;
    }
};

int main()
{
    srand(time(NULL));

    ArrayQueue<int>* q = new ArrayQueue<int>();
    for (int i = 0; i < 3; i++)
    {
        int e = rand() * 100 / RAND_MAX;
        q->enQueue(e);
        cout << e << "  enQueue" << endl;
    }
    cout << "Capacity:" << q->getCapacity() << endl;
    cout << "Length:" << q->getLength() << endl;
    cout << q->deQueue() << "  deQueue" << endl;
    cout << q->deQueue() << "  deQueue" << endl;
    for (int i = 0; i < 6; i++)
    {
        int e = rand() * 100 / RAND_MAX;
        q->enQueue(e);
        cout << e << "  enQueue" << endl;
    }
    cout << "Capacity:" << q->getCapacity() << endl;
    cout << "Length:" << q->getLength() << endl;
    while (!q->isEmpty())
    {
        cout << q->deQueue() << "  deQueue" << endl;
    }
    cout << "isEmpty()=" << q->isEmpty() << endl;
    delete q;

    cin.get();
    return 0;
}


