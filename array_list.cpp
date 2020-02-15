/**
  * @brief  动态数组实现的线性表
  */
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <iomanip>

using namespace std;

template<class T>

class ArrayList
{
private:
    T* data_;
    int size_;//实际大小
    int cap_;//数组容量

    bool isFull()
    {
        return size_ == cap_;
    }


public:
    ArrayList(int cap = 4): size_(0), cap_(cap)
    {
        data_ = new T[cap_];
    }

    ~ArrayList()
    {
        delete [] data_;
    }

    bool isEmpty()
    {
        return size_ == 0;
    }

    int getCapacity()
    {
        return cap_;
    }

    int getSize()
    {
        return size_;
    }

    //数组扩容
    void resize()
    {
        T* old = data_;
        cap_ *= 2;
        data_ = new T[cap_];
        for (int i = 0; i < cap_; i++)
            data_[i] = old[i];
        delete [] old;
    }

    void append(T e)
    {
        if (isFull())
            resize();
        data_[size_] = e;
        size_++;
    }

    void insert(int idx, T e)
    {
        if (isFull())
            resize();
        if (idx < size_)
        {
            for (int i = size_ - 1; i >= idx; i--)
                data_[i + 1] = data_[i];
            data_[idx] = e;
        }
        else
        {
            data_[size_] = e;
        }
        size_++;
    }

    //弹出末尾元素
    T pop()
    {
        size_--;
        return data_[size_];
    }

    T getLast()
    {
        return data_[size_ - 1];
    }

    T getFirst()
    {
        return data_[0];
    }

    T getElement(int idx)
    {
        if (idx >= size_)
            idx = size_ - 1;
        return data_[idx];
    }

    int find(T e)
    {
        int i;
        for (i = 0; i < size_; i++)
            if (data_[i] == e)
                break;
        if (i >= size_)
            return -1;
        return i;
    }

    //按索引删除
    T delByIdx(int idx)
    {
        if (idx >= size_)
            idx = size_ - 1;
        T data = data_[idx];
        for (int i = idx; i < size_ - 1; i++)
            data_[i] = data_[i + 1];
        size_--;
        return data;
    }

    //删除元素
    void del(T e)
    {
        int idx = find(e);
        if (idx == -1)
        {
            cout << "Specified element is not found" << endl;
            return;
        }
        delByIdx(idx);
    }

    //反转
    void reverse()
    {
        T tmp;
        for (int i = 0; i < size_ / 2; i++)
        {
            tmp = data_[i];
            data_[i] = data_[size_ - 1 - i];
            data_[size_ - 1 - i] = tmp;
        }
    }

    //遍历
    void traversal()
    {
        for (int i = 0; i < size_; i++)
        {
            cout << data_[i] << ' ';
        }
    }

};

int main()
{
    clock_t start = clock();

    ArrayList<int>* list = new ArrayList<int>();
    list->insert(2, 99);
    cout << "first element is " << list->getFirst() << endl;
    cout << "append 88" << endl;
    list->append(88);
    cout << "insert 0, 55" << endl;
    list->insert(0, 55);
    cout << "append 77" << endl;
    list->append(77);
    cout << "pop last " << list->pop() << endl;
    cout << "traversal: ";
    list->traversal();
    cout << endl;
    list->reverse();
    cout << "reverse: ";
    list->traversal();
    cout << endl;
    delete list;

    clock_t end = clock();
    cout << "Running time: " << end - start << "/" << CLOCKS_PER_SEC << " s" << endl;
    cin.get();
    return 0;
}
