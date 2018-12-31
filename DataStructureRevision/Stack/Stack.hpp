//
//  Stack.hpp
//  DataStructureRevision
//
//  Created by Evian张 on 2018/12/29.
//  Copyright © 2018 Evian张. All rights reserved.
//

#ifndef Stack_hpp
#define Stack_hpp

#include <iostream>

#include "../SequenceList/SequenceListByArray.hpp"

template <typename T>
class Stack
{
    SequenceListByArray<T> list;
    int count;
public:
    /** 初始化 */
    Stack();
    
    /**
     @brief 打印栈
     @discussion 打印栈顶，并从栈顶开始打印栈。需要对类T重载<<算符
     */
    void display();
    
    /**
     弹栈

     @param value 传出栈顶的值
     */
    bool pop(T& value);
    
    /**
     压栈

     @param value 传入栈顶的值
     */
    bool push(T value);
    
    /**
     获得栈顶元素

     @param value 传出栈顶的值
     */
    bool getTop(T& value);
    
    /** 判断栈内是否有元素 */
    bool isEmpty();
};

template <typename T>
Stack<T>::Stack()
{
    this->count = 0;
}

template <typename T>
void Stack<T>::display()
{
    if (this->count == 0)
    {
        std::cout << "Top: NULL" << std::endl;
        std::cout << "NULL" << std::endl;
    }
    else
    {
        T *element = new T;
        this->getTop(*element);
        std::cout << "Top: " << *element << std::endl;
        for (int i = this->count - 1; i >= 0; i--)
        {
            this->list.get(i, *element);
            std::cout << *element << std::endl;
        }
    }
}

template <typename T>
bool Stack<T>::pop(T &value)
{
    this->list.get(this->count - 1, value);
    bool isSuccess = this->list.remove(this->count - 1);
    if (isSuccess)
    {
        this->count--;
        return true;
    }
    return false;
}

template <typename T>
bool Stack<T>::push(T value)
{
    bool isSuccess = this->list.insert(value, this->count);
    if (isSuccess)
    {
        this->count++;
        return true;
    }
    return false;
}

template <typename T>
bool Stack<T>::getTop(T &value)
{
    return this->list.get(this->count - 1, value);
}

template <typename T>
bool Stack<T>::isEmpty()
{
    return this->count == 0;
}

#endif /* Stack_hpp */
