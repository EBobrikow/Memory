#pragma once
#include <iostream>
using namespace std;


class Counter
{
public:
   
    Counter()
        : counter(0) 
    {};

    Counter(const Counter&) = delete;
    Counter& operator=(const Counter&) = delete;

  
    ~Counter() {}

    void reset()
    {
        counter = 0;
    }

    unsigned int get()
    {
        return counter;
    }

    void operator++()
    {
        counter++;
    }

    void operator++(int)
    {
        counter++;
    }

    void operator--()
    {
        counter--;
    }
    void operator--(int)
    {
        counter--;
    }

private:
    unsigned int counter{};
};


template <typename T>
class CustomSharedPtr
{
public:
   
    CustomSharedPtr(T* _ptr = nullptr)
    {
        ptr = _ptr;
        counter = new Counter();
        (*counter)++;
    }

    CustomSharedPtr(const CustomSharedPtr<T>& other)
    {
        ptr = other.ptr;
        counter = other.counter;
        if (ptr != nullptr)
        {
            cout << "Counter increased" << endl;
            (*counter)++;
        }
    }

    CustomSharedPtr<T>& operator=(const CustomSharedPtr<T>& other)
    {
        ptr = other.ptr;
        counter = other.counter;
        if (ptr != nullptr)
        {
            cout << "Counter increased" << endl;
            (*counter)++;
        }
        return *this;
    }


    unsigned int GetCount()
    {
        return counter->get();
    }

    T* Get()
    {
        return ptr;
    }

    T& operator*()
    {
        return *ptr;
    }

    T* operator->()
    {
        return ptr;
    }

    virtual ~CustomSharedPtr()
    {
        (*counter)--;
        cout << "Counter decreased" << endl;
        if (counter->get() == 0)
        {
            cout << "Pointer destroyed" << endl;
            delete counter;
            delete ptr;
        }
    }


private:
   
    Counter* counter;
    T* ptr;
};

