//
//  BiLinkedList.hpp
//  DataStructureRevision
//
//  Created by Evian张 on 2018/12/29.
//  Copyright © 2018 Evian张. All rights reserved.
//

#ifndef BiLinkedList_hpp
#define BiLinkedList_hpp

#include <iostream>

template <typename T>
class BiLinkedList
{
    class BiLinkedListNode
    {
    public:
        T value;
        BiLinkedListNode* preNode;
        BiLinkedListNode* nextNode;
        
        BiLinkedListNode()
        {
            this->preNode = NULL;
            this->nextNode = NULL;
        }
    };
    
    BiLinkedListNode* head;
    BiLinkedListNode* tail;
    int count;
public:
    /** 初始化 */
    BiLinkedList();
    
    /** 析构函数 */
    ~BiLinkedList();
    
    /**
     @brief 打印链表
     @discussion 打印链表头、尾及连接关系。需要对类T重载<<算符
     */
    void display();
    
    /**
     从头插入

     @param value 插入的值，从头插入
     */
    bool insertInHead(T value);
    
    /**
     从尾插入

     @param value 插入的值，从尾插入
     */
    bool insertInTail(T value);
    
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
BiLinkedList<T>::BiLinkedList()
{
    this->head = NULL;
    this->tail = NULL;
    this->count = 0;
}

template <typename T>
BiLinkedList<T>::~BiLinkedList()
{
    BiLinkedListNode* tmpNode = this->head;
    while (tmpNode!= NULL)
    {
        BiLinkedListNode* tmpPreNode = tmpNode;
        tmpNode = tmpPreNode->nextNode;
        delete tmpPreNode;
        this->count--;
    }
}

template <typename T>
void BiLinkedList<T>::display()
{
    if (this->head != NULL)
        std::cout << "head: " << this->head->value << std::endl;
    else
        std::cout << "head: NULL" << std::endl;
    if (this->tail != NULL)
        std::cout << "tail: " << this->tail->value << std::endl;
    else
        std::cout << "tail: NULL" << std::endl;
    BiLinkedListNode* tmpNode = this->head;
    while (tmpNode != NULL)
    {
        std::cout << tmpNode->value << " ";
        tmpNode = tmpNode->nextNode;
        if (tmpNode != NULL)
            std::cout << "-> ";
    }
    std::cout << std::endl;
}

template <typename T>
bool BiLinkedList<T>::insertInHead(T value)
{
    BiLinkedListNode* insertedNode = new BiLinkedListNode();
    insertedNode->value = value;
    insertedNode->nextNode = this->head;
    if (this->head != NULL)
        this->head->preNode = insertedNode;
    this->head = insertedNode;
    if (this->tail == NULL)
        this->tail = insertedNode;
    this->count++;
    return true;
}

template <typename T>
bool BiLinkedList<T>::insertInTail(T value)
{
    BiLinkedListNode* insertedNode = new BiLinkedListNode();
    insertedNode->value = value;
    insertedNode->preNode = this->tail;
    if (this->tail != NULL)
        this->tail->nextNode = insertedNode;
    this->tail = insertedNode;
    if (this->head == NULL)
        this->head = insertedNode;
    this->count++;
    return true;
}

template <typename T>
bool BiLinkedList<T>::get(int index, T &value)
{
    if (this->count == 0 || index >= this->count)
        return false;
    BiLinkedListNode* tmpNode = this->head;
    for (int i = 0; i < index; i++)
    {
        tmpNode = tmpNode->nextNode;
    }
    value = tmpNode->value;
    return true;
}

template <typename T>
bool BiLinkedList<T>::locate(T key, bool (*compare)(T, T), T &value)
{
    BiLinkedListNode* tmpNode = this->head;
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
bool BiLinkedList<T>::removeByIndex(int index)
{
    if (this->count == 0 || index >= this->count)
        return false;
    BiLinkedListNode* tmpNode = this->head;
    for (int i = 0; i < index; i++)
    {
        tmpNode = tmpNode->nextNode;
    }
    if (tmpNode->preNode != NULL && tmpNode->nextNode != NULL)
    {
        tmpNode->preNode->nextNode = tmpNode->nextNode;
        tmpNode->nextNode->preNode = tmpNode->preNode;
    }
    else if (tmpNode->preNode == NULL && tmpNode->nextNode != NULL)
    {
        this->head = tmpNode->nextNode;
        this->head->preNode = NULL;
    }
    else if (tmpNode->preNode != NULL && tmpNode->nextNode == NULL)
    {
        this->tail = tmpNode->preNode;
        this->tail->nextNode = NULL;
    }
    else
    {
        this->head = NULL;
        this->tail = NULL;
    }
    delete tmpNode;
    this->count--;
    return true;
}

template <typename T>
bool BiLinkedList<T>::removeByKey(T key, bool (*compare)(T, T))
{
    BiLinkedListNode* tmpNode = this->head;
    while (tmpNode != NULL)
    {
        if (compare(tmpNode->value, key))
            break;
        tmpNode = tmpNode->nextNode;
    }
    if (tmpNode == NULL)
        return false;
    if (this->head != tmpNode && this->tail != tmpNode)
    {
        tmpNode->preNode->nextNode = tmpNode->nextNode;
        tmpNode->nextNode->preNode = tmpNode->preNode;
    }
    if (this->head == tmpNode)
    {
        this->head = tmpNode->nextNode;
        this->head->preNode = NULL;
    }
    if (this->tail == tmpNode)
    {
        this->tail = tmpNode->preNode;
        this->tail->nextNode = NULL;
    }
    delete tmpNode;
    this->count--;
    return true;
}

#endif /* BiLinkedList_hpp */
