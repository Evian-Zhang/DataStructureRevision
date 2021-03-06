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
     @brief 删除
     @discussion 删除节点。若该节点既有左子树也有右子树，则将其左子树中最大的节点替代此节点

     @param value 需对类T重载==及<
     @return 若无该节点，则返回false。否则返回true
     */
    bool removeNode(T value);
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
bool BinarySearchTree<T>::removeNode(T value)
{
    typename BinaryTree<T>::BTreeNode *nodeToBeDeleted = this->root;
    typename BinaryTree<T>::BTreeNode *preNodeToBeDeleted = nodeToBeDeleted;
    while (nodeToBeDeleted != NULL)
    {
        if (value == nodeToBeDeleted->value)
            break;
        else if (value < nodeToBeDeleted->value)
        {
            preNodeToBeDeleted = nodeToBeDeleted;
            nodeToBeDeleted = nodeToBeDeleted->lchild;
        }
        else
        {
            preNodeToBeDeleted = nodeToBeDeleted;
            nodeToBeDeleted = nodeToBeDeleted->rchild;
        }
    }
    if (nodeToBeDeleted == NULL)
        return false;
    
    typename BinaryTree<T>::BTreeNode *nodeToReplace = nodeToBeDeleted;
    if (nodeToBeDeleted->lchild != NULL && nodeToBeDeleted->rchild != NULL)
    {
        nodeToReplace = nodeToBeDeleted->lchild;
        
        typename BinaryTree<T>::BTreeNode *preNodeToReplace = NULL;
        //找到nodeToBeDeleted左子树中最大的那个
        while (nodeToReplace->rchild != NULL)
        {
            preNodeToReplace = nodeToReplace;
            nodeToReplace = nodeToReplace->rchild;
        }
        
        nodeToBeDeleted->value = nodeToReplace->value;
        
        if (preNodeToReplace == NULL)
        {
            nodeToBeDeleted->lchild = nodeToReplace->lchild;
        }
        else if (nodeToReplace->lchild != NULL)
        {
            preNodeToReplace->rchild = nodeToReplace->lchild;
        }
        else
        {
            //maybe need to delete nodeToReplace, but I don't know how
            preNodeToReplace->rchild = NULL;
        }
    }
    else if (nodeToBeDeleted->lchild != NULL)
    {
        if (nodeToBeDeleted == preNodeToBeDeleted)
            this->root = nodeToBeDeleted->lchild;
        else if (nodeToBeDeleted == preNodeToBeDeleted->lchild)
            preNodeToBeDeleted->lchild = nodeToBeDeleted->lchild;
        else
            preNodeToBeDeleted->rchild = nodeToBeDeleted->lchild;
        delete nodeToBeDeleted;
    }
    else if (nodeToBeDeleted->rchild != NULL)
    {
        if (nodeToBeDeleted == preNodeToBeDeleted)
            this->root = nodeToBeDeleted->rchild;
        else if (nodeToBeDeleted == preNodeToBeDeleted->lchild)
            preNodeToBeDeleted->lchild = nodeToBeDeleted->rchild;
        else
            preNodeToBeDeleted->rchild = nodeToBeDeleted->rchild;
        delete nodeToBeDeleted;
    }
    else
    {
        if (nodeToBeDeleted == preNodeToBeDeleted)
            this->root = NULL;
        else if (nodeToBeDeleted == preNodeToBeDeleted->lchild)
            preNodeToBeDeleted->lchild = NULL;
        else
            preNodeToBeDeleted->rchild = NULL;
        delete nodeToBeDeleted;
    }
    this->count--;
    return true;
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
