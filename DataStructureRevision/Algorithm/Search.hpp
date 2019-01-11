//
//  Search.hpp
//  DataStructureRevision
//
//  Created by Evian张 on 2019/1/6.
//  Copyright © 2019 Evian张. All rights reserved.
//

#ifndef Search_hpp
#define Search_hpp

#include "../Tree/BinarySearchTree.hpp"
#include "../Tree/AVLTree.hpp"

template <typename T>
class Search
{
    
    
public:
    /**
     @brief 顺序查找
     @discussion 顺序查找，时间复杂度为O(n)

     @param length array的长度
     @param key 关键字。需要对类T重载==
     @return key第一次出现时所在位置的下标；若不存在则返回-1
     */
    static int seqSearch(T *array, int length, T key);
    
    /**
     @brief 二分查找
     @discussion 二分查找，时间复杂度为O(logn)

     @param array 待查找数组。需要按关键字升序。
     @param length array的长度
     @param key 关键字。需要对类T重载==
     @return key第一次出现时所在位置的下标；若不存在则返回-1
     */
    static int binarySearch(T *array, int length, T key);
    
    /**
     @brief 二叉搜索树查找
     @discussion 二叉搜索树查找，时间复杂度为O(logn)

     @param length array的长度
     @param key 关键字。需要对类T重载==及<
     @return key第一次出现时所在位置的下标；若不存在则返回-1
     */
    static int BSTreeSearch(T *array, int length, T key);
    
    /**
     @brief 平衡二叉搜索树查找
     @discussion 平衡二叉搜索树查找，时间复杂度为O(logn)
     
     @param length array的长度
     @param key 关键字。需要对类T重载==及<
     @return key第一次出现时所在位置的下标；若不存在则返回-1
     */
    static int AVLTreeSearch(T *array, int length, T key);
};

template <typename T>
int Search<T>::seqSearch(T *array, int length, T key)
{
    for (int index = 0; index < length; index++)
        if (array[index] == key)
            return index;
    return -1;
}

template <typename T>
int Search<T>::binarySearch(T *array, int length, T key)
{
    int low = 0, high = length - 1;
    while (low <= high)
    {
        int mid = (low + high) / 2;
        if (array[mid] == key)
            return mid;
        else if (array[mid] < key)
            high = mid - 1;
        else
            low = mid + 1;
    }
    return -1;
}

template <typename T>
int Search<T>::BSTreeSearch(T *array, int length, T key)
{
    class NodeWithIndex
    {
    public:
        T value;
        int index;
        
        bool operator==(NodeWithIndex node)
        {
            return this->value == node.value;
        }
        
        bool operator<(NodeWithIndex node)
        {
            return this->value < node.value;
        }
    };
    
    BinarySearchTree<NodeWithIndex> *tree = new BinarySearchTree<NodeWithIndex>();
    
    for (int i = 0; i < length; i++)
    {
        NodeWithIndex *node = new NodeWithIndex();
        node->value = array[i];
        node->index = i;
        tree->addNode(*node);
    }
    
    NodeWithIndex *keyNode = new NodeWithIndex();
    keyNode->value = key;
    
    NodeWithIndex *foundNode = tree->search(*keyNode);
    
    int index = -1;
    
    if (foundNode != NULL)
        index = foundNode->index;
    delete keyNode;
    delete tree;
    return index;
}

template <typename T>
int Search<T>::AVLTreeSearch(T *array, int length, T key)
{
    class NodeWithIndex
    {
    public:
        T value;
        int index;
        
        bool operator==(NodeWithIndex node)
        {
            return this->value == node.value;
        }
        
        bool operator<(NodeWithIndex node)
        {
            return this->value < node.value;
        }
    };
    
    AVLTree<NodeWithIndex> *tree = new AVLTree<NodeWithIndex>();
    
    for (int i = 0; i < length; i++)
    {
        NodeWithIndex *node = new NodeWithIndex();
        node->value = array[i];
        node->index = i;
        tree->addNode(*node);
    }
    
    NodeWithIndex *keyNode = new NodeWithIndex();
    keyNode->value = key;
    
    NodeWithIndex *foundNode = tree->search(*keyNode);
    
    int index = -1;
    
    if (foundNode != NULL)
        index = foundNode->index;
    delete keyNode;
    delete tree;
    return index;
}

#endif /* Search_hpp */
