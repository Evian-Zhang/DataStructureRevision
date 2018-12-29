//
//  SequenceListByPtr.hpp
//  DataStructureRevision
//
//  Created by Evian张 on 2018/12/29.
//  Copyright © 2018 Evian张. All rights reserved.
//

#ifndef SequenceListByPtr_hpp
#define SequenceListByPtr_hpp

#include <stdlib.h>

template <typename T>
class SequenceListByPtr
{
    static const int MAX_LIST_LENGTH = 128;
    T* sequenceList;
    int count;
public:
    /** 初始化 */
    SequenceListByPtr();
    
    /** 析构函数 */
    ~SequenceListByPtr();
    
    /**
     插入
     
     @param value 插入的元素
     @param index 从0开始
     */
    bool insert(T value, int index);
    
    /**
     删除
     
     @param index 从0开始
     */
    bool remove(int index);
    
    /**
     指定位置获取
     
     @param index 从0开始
     @param value 传出获取的值
     */
    bool get(int index, T& value);
    
    /**
     定位
     
     @param key 要定位的值
     @param compare 比较函数，如果两参数相等则返回true
     @param index 传出定位的下标，从0开始
     */
    bool locate(T key, bool (*compare)(T, T), int& index);
    
    int getCount();
};

template <typename T>
SequenceListByPtr<T>::SequenceListByPtr()
{
    this->sequenceList = new T[MAX_LIST_LENGTH];
    this->count = 0;
}

template <typename T>
SequenceListByPtr<T>::~SequenceListByPtr()
{
    delete this->sequenceList;
    this->count = 0;
}

template <typename T>
bool SequenceListByPtr<T>::insert(T value, int index)
{
    if (this->count == this->MAX_LIST_LENGTH || index > this->count)
        return false;
    for (int i = this->count - 1; i >= index; i--)
    {
        *(this->sequenceList + i + 1) = *(this->sequenceList + i);
    }
    *(this->sequenceList + index) = value;
    this->count++;
    return true;
}

template <typename T>
bool SequenceListByPtr<T>::remove(int index)
{
    if (this->count == 0 || index > this->count - 1)
        return false;
    for (int i = index; i < this->count; i++)
    {
        *(this->sequenceList + i) = *(this->sequenceList + i + 1);
    }
    this->count--;
    return true;
}

template <typename T>
bool SequenceListByPtr<T>::get(int index, T &value)
{
    if (this->count == 0 || index >= this->count)
        return false;
    value = *(this->sequenceList + index);
    return true;
}

template <typename T>
bool SequenceListByPtr<T>::locate(T key, bool compare(T, T), int &index)
{
    for (int i = 0; i < this->count; i++)
    {
        if (compare(key, *(this->sequenceList + i)))
        {
            index = i;
            return true;
        }
    }
    return false;
}

template <typename T>
int SequenceListByPtr<T>::getCount()
{
    return this->count;
}

#endif /* SequenceListByPtr_hpp */
