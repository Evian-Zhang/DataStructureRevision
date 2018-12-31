//
//  CircularQueue.hpp
//  DataStructureRevision
//
//  Created by Evian张 on 2018/12/29.
//  Copyright © 2018 Evian张. All rights reserved.
//

#ifndef CircularQueue_hpp
#define CircularQueue_hpp

#include <iostream>

template <typename T>
class CircularQueue
{
    static const int MAX_QUEUE_LENGTH = 128;
    T list[MAX_QUEUE_LENGTH];
    int count;
    int frontIndex;
    int rearIndex;
    
public:
    /** 初始化 */
    CircularQueue();
    
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
    
    /** 判断队列内是否有元素 */
    bool isEmpty();
};

template <typename T>
CircularQueue<T>::CircularQueue()
{
    this->count = 0;
    this->frontIndex = this->rearIndex = 0;
}

template <typename T>
void CircularQueue<T>::display()
{
    if (this->count == 0)
    {
        std::cout << "Front: NULL" << std::endl;
        std::cout << "Rear: NULL" << std::endl;
        std::cout << "NULL" << std::endl;
    }
    else
    {
        std::cout << "Front: " << this->list[this->frontIndex] << std::endl;
        std::cout << "Rear: " << this->list[this->rearIndex] << std::endl;
        for (int i = this->frontIndex; i < this->rearIndex; i = (i + 1) % this->MAX_QUEUE_LENGTH)
        {
            std::cout << this->list[i] << ", ";
        }
        std::cout << this->list[this->rearIndex] << std::endl;
    }
}

template <typename T>
bool CircularQueue<T>::enQueue(T value)
{
    if (this->count == this->MAX_QUEUE_LENGTH)
        return false;
    if (this->count == 0)
    {
        this->list[this->rearIndex] = value;
    }
    else
    {
        this->rearIndex = (this->rearIndex + 1) % this->MAX_QUEUE_LENGTH;
        this->list[this->rearIndex] = value;
    }
    this->count++;
    return true;
}

template <typename T>
bool CircularQueue<T>::deQueue(T &value)
{
    if (this->count == 0)
        return false;
    value = this->list[this->frontIndex];
    if (this->frontIndex != this->rearIndex)
        this->frontIndex = (this->frontIndex + 1) % this->MAX_QUEUE_LENGTH;
    this->count--;
    return true;
}

template <typename T>
bool CircularQueue<T>::getFront(T &value)
{
    if (this->count == 0)
        return false;
    value = this->list[this->frontIndex];
    return true;
}

template <typename T>
bool CircularQueue<T>::isEmpty()
{
    return this->count == 0;
}

#endif /* Queue_hpp */
