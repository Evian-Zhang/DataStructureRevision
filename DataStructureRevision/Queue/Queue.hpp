//
//  Queue.hpp
//  DataStructureRevision
//
//  Created by Evian张 on 2018/12/29.
//  Copyright © 2018 Evian张. All rights reserved.
//

#ifndef Queue_hpp
#define Queue_hpp

#include <iostream>

#include "../LinkedList/BiLinkedList.hpp"

template <typename T>
class Queue
{
    BiLinkedList<T> list;
    int count;
    
public:
    /** 初始化 */
    Queue();
    
    /**
     @brief 打印队列
     @discussion 打印队列的队首、队尾及队列元素。需要对类T重载<<算符
     */
    void display();
    
    /** 进队列 */
    bool enQueue(T value);
    
    /**
     出队列
     
     @param value 传出的队首值
     */
    bool deQueue(T& value);
    
    /**
     获得队首值
     
     @param value 传出的队首值
     */
    bool getFront(T& value);
};

template <typename T>
Queue<T>::Queue()
{
    this->count = 0;
}

template <typename T>
void Queue<T>::display()
{
    if (this->count == 0)
    {
        std::cout << "Front: NULL" << std::endl;
        std::cout << "Rear: NULL" << std::endl;
        std::cout << "NULL" << std::endl;
    }
    else
    {
        T* element = new T;
        this->list.get(0, *element);
        std::cout << "Front: " << *element << std::endl;
        this->list.get(this->count - 1, *element);
        std::cout << "Rear: " << *element << std::endl;
        for (int i = 0; i < this->count - 1; i++)
        {
            this->list.get(i, *element);
            std::cout << *element << ", ";
        }
        this->list.get(this->count - 1, *element);
        std::cout << *element << std::endl;
    }
}

template <typename T>
bool Queue<T>::enQueue(T value)
{
    bool isSuccess = this->list.insertInTail(value);
    if (isSuccess)
    {
        this->count++;
        return true;
    }
    return false;
}

template <typename T>
bool Queue<T>::deQueue(T &value)
{
    bool isSuccess = this->list.get(0, value);
    if (isSuccess)
    {
        this->count--;
        return true;
    }
    return false;
}

template <typename T>
bool Queue<T>::getFront(T &value)
{
    return this->list.get(0, value);
}

#endif /* Queue_hpp */
