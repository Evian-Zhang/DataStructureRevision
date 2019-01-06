//
//  BinarySearchTree.hpp
//  DataStructureRevision
//
//  Created by Evian张 on 2019/1/6.
//  Copyright © 2019 Evian张. All rights reserved.
//

#ifndef BinarySearchTree_hpp
#define BinarySearchTree_hpp

#include "BinaryTree.hpp"

template <typename T>
class BinarySearchTree : public BinaryTree<T>
{
public:
    void addNode(T value);
    
    /**
     查找

     @return 指向该元素的指针。若失败则返回NULL
     */
    T* search(T value);
};

template <typename T>
void BinarySearchTree<T>::addNode(T value)
{
    typename BinaryTree<T>::BTreeNode **pNode = &(this->root);
    while (*pNode != NULL)
    {
        if (value == (*pNode)->value)
            return;
        else if (value < (*pNode)->value)
            pNode = &((*pNode)->lchild);
        else
            pNode = &((*pNode)->rchild);
    }
    *pNode = new typename BinaryTree<T>::BTreeNode();
    (*pNode)->value = value;
    (*pNode)->lchild = NULL;
    (*pNode)->rchild = NULL;
    this->count++;
}

template <typename T>
T* BinarySearchTree<T>::search(T value)
{
    typename BinaryTree<T>::BTreeNode *node = this->root;
    while (node != NULL)
    {
        if (value == node->value)
            return &(node->value);
        else if (value < node->value)
            node = node->lchild;
        else
            node = node->rchild;
    }
    return NULL;
}

#endif /* BinarySearchTree_hpp */
