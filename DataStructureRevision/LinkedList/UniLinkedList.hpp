//
//  UniLinkedList.hpp
//  DataStructureRevision
//
//  Created by Evian张 on 2018/12/29.
//  Copyright © 2018 Evian张. All rights reserved.
//

#ifndef UniLinkedList_hpp
#define UniLinkedList_hpp

template <typename T>
class UniLinkedList
{
    class UniLinkedListNode
    {
    public:
        T value;
        T* nextNode;
        
        UniLinkedListNode()
        {
            this->value = NULL;
            this->nextNode = NULL;
        }
    };
    
    UniLinkedListNode *head;
    int count;
public:
    /** 初始化 */
    UniLinkedList();
    
    /** 析构函数 */
    ~UniLinkedList();
    
    /**
     插入

     @param value 插入的值，从头插入
     */
    bool insert(T value);
    
    /**
     指定位置获取

     @param index 从0开始
     @param value 传出获取的值
     */
    bool get(int index, T& value);
    
    /**
     定位

     @param key 定位的值
     @param compare 比较函数，如果相等则返回true
     @param value 传出找到的值
     */
    bool locate(T key, bool (*compare)(T, T), T& value);
    
    /**
     指定位置删除

     @param index 从0开始
     */
    bool removeByIndex(int index);
    
    /**
     指定key删除

     @param key 指定删除的值
     @param compare 比较函数，若相等则返回true
     */
    bool removeByKey(T key, bool (*compare)(T, T));
};

template <typename T>
UniLinkedList<T>::UniLinkedList()
{
    this->head = NULL;
    this->count = 0;
}

template <typename T>
UniLinkedList<T>::~UniLinkedList()
{
    UniLinkedListNode* tmpNode = this->head;
    while (tmpNode!= NULL)
    {
        UniLinkedListNode* tmpPreNode = tmpNode;
        tmpNode = tmpPreNode->nextNode;
        delete tmpPreNode;
        this->count--;
    }
}

template <typename T>
bool UniLinkedList<T>::insert(T value)
{
    UniLinkedListNode* insertedNode = new UniLinkedListNode();
    insertedNode->value = value;
    insertedNode->nextNode = this->head;
    this->head = insertedNode;
    this->count++;
    return true;
}

template <typename T>
bool UniLinkedList<T>::get(int index, T &value)
{
    if (this->count == 0 || index >= this->count)
        return false;
    UniLinkedListNode* tmpNode = this->head;
    for (int i = 0; i < index; i++)
    {
        tmpNode = tmpNode->next;
    }
    value = tmpNode->value;
    return true;
}

template <typename T>
bool UniLinkedList<T>::locate(T key, bool (*compare)(T, T), T &value)
{
    UniLinkedListNode* tmpNode = this->head;
    while (tmpNode != NULL)
    {
        if (compare(tmpNode->value, key))
        {
            value = tmpNode->value;
            return true;
        }
        tmpNode = tmpNode->next;
    }
    return false;
}

template <typename T>
bool UniLinkedList<T>::removeByIndex(int index)
{
    if (this->count == 0 || index >= this->count)
        return false;
    UniLinkedListNode* tmpNode = this->head;
    UniLinkedListNode* tmpPreNode = tmpNode;
    for (int i = 0; i < index; i++)
    {
        tmpNode = tmpNode->next;
        tmpPreNode = tmpNode;
    }
    if (tmpPreNode == tmpNode)
        this->head = tmpNode->nextNode;
    else
        tmpPreNode->nextNode = tmpNode->nextNode;
    delete tmpNode;
    this->count--;
    return true;
}

template <typename T>
bool UniLinkedList<T>::removeByKey(T key, bool (*compare)(T, T))
{
    UniLinkedListNode* tmpNode = this->head;
    UniLinkedListNode* tmpPreNode = tmpNode;
    while (tmpNode != NULL)
    {
        if (compare(tmpNode->value, key))
            break;
        tmpPreNode = tmpNode;
    }
    if (tmpNode == NULL)
        return false;
    if (tmpPreNode == tmpNode)
        this->head = tmpNode->nextNode;
    else
        tmpPreNode->nextNode = tmpNode->nextNode;
    delete tmpNode;
    this->count--;
    return true;
}

#endif /* UniLinkedList_hpp */
