//
//  AVLTree.hpp
//  DataStructureRevision
//
//  Created by Evian张 on 2019/1/11.
//  Copyright © 2019 Evian张. All rights reserved.
//

#ifndef AVLTree_hpp
#define AVLTree_hpp

#include <iostream>

template <typename T>
class AVLTree
{
    class AVLTreeNode
    {
    public:
        T value;
        int height;
        AVLTreeNode *lchild;
        AVLTreeNode *rchild;
    };
    
    AVLTreeNode *root;
    int count;
    
    enum NodePosition
    {
        LTREE,
        RTREE
    };
    
    /** display的辅助函数 */
    void displayFromNode(AVLTreeNode* node, NodePosition nodePos, int indent);
    
    int max(int a, int b)
    {
        return (a > b) ? a : b;
    }
    
    int height(AVLTreeNode *node)
    {
        return (node == NULL) ? 0 : node->height;
    }
    
    AVLTreeNode* LL_Rotate(AVLTreeNode *node);
    
    AVLTreeNode* RR_Rotate(AVLTreeNode *node);
    
    AVLTreeNode* LR_Rotate(AVLTreeNode *node);
    
    AVLTreeNode* RL_Rotate(AVLTreeNode* node);
    
    AVLTreeNode* addNodeFromNode(T value, AVLTreeNode* node);
    
    AVLTreeNode* deleteNodeFromNode(T value, AVLTreeNode* node);
    
public:
    /** 初始化 */
    AVLTree();
    
    /**
     @brief 打印平衡二叉搜索树
     @discussion 打印平衡二叉搜索树。需要对类T重载<<算符
     */
    void display();
    
    /** 增加节点 */
    void addNode(T value);
    
    /** 删除节点 */
    void deleteNode(T value);
};

template <typename T>
AVLTree<T>::AVLTree()
{
    this->root = NULL;
    this->count = 0;
}

template <typename T>
void AVLTree<T>::displayFromNode(AVLTreeNode *node, NodePosition nodePos, int indent)
{
    for (int i = 0; i < indent; i++)
        std::cout << "          ";
    std::cout << "+---------";
    switch (nodePos)
    {
        case LTREE:
            std::cout << "LT: ";
            break;
        case RTREE:
            std::cout << "RT: ";
            break;
            
        default:
            break;
    }
    std::cout << node->value << std::endl;
    if (node->lchild != NULL)
        this->displayFromNode(node->lchild, LTREE, indent + 1);
    if (node->rchild != NULL)
        this->displayFromNode(node->rchild, RTREE, indent + 1);
}

template <typename T>
void AVLTree<T>::display()
{
    if (this->root == NULL)
        std::cout << "NULL";
    else
    {
        std::cout << "R: " << this->root->value << std::endl;
        if (this->root->lchild != NULL)
            this->displayFromNode(this->root->lchild, LTREE, 0);
        if (this->root->rchild != NULL)
            this->displayFromNode(this->root->rchild, RTREE, 0);
    }
}


template <typename T>
typename AVLTree<T>::AVLTreeNode* AVLTree<T>::LL_Rotate(AVLTreeNode *node)
{
    //完成旋转
    AVLTreeNode *newNode = node->lchild;
    node->lchild = newNode->rchild;
    newNode->rchild = node;
    
    //更新height
    node->height = this->max(this->height(node->lchild), this->height(node->rchild)) + 1;
    newNode->height = this->max(this->height(newNode->lchild), this->height(node)) + 1;
    return newNode;
}

template <typename T>
typename AVLTree<T>::AVLTreeNode* AVLTree<T>::RR_Rotate(AVLTreeNode *node)
{
    //完成旋转
    AVLTreeNode *newNode = node->rchild;
    node->rchild = newNode->lchild;
    newNode->lchild = node;
    
    //更新height
    node->height = this->max(this->height(node->lchild), this->height(node->rchild)) + 1;
    newNode->height = this->max(this->height(newNode->rchild), this->height(node)) + 1;
    return newNode;
}

template <typename T>
typename AVLTree<T>::AVLTreeNode* AVLTree<T>::LR_Rotate(AVLTreeNode *node)
{
    node->lchild = this->RR_Rotate(node->lchild);
    return this->LL_Rotate(node);
}

template <typename T>
typename AVLTree<T>::AVLTreeNode* AVLTree<T>::RL_Rotate(AVLTreeNode *node)
{
    node->rchild = this->LL_Rotate(node->rchild);
    return this->RR_Rotate(node);
}

template <typename T>
typename AVLTree<T>::AVLTreeNode* AVLTree<T>::addNodeFromNode(T value, AVLTreeNode *node)
{
    if (node == NULL)
    {
        AVLTree<T>::AVLTreeNode *addedNode = new AVLTree<T>::AVLTreeNode();
        addedNode->value = value;
        addedNode->lchild = NULL;
        addedNode->rchild = NULL;
        addedNode->height = 0;
        this->count++;
    }
    else if (value < node->value)
    {
        node->lchild = this->addNodeFromNode(value, node->lchild);
        if (this->height(node->lchild) - this->height(node->rchild) == 2)
        {
            if (value < node->lchild->value)
                node = this->LL_Rotate(node);
            else
                node = this->LR_Rotate(node);
        }
    }
    else if (value > node->value)
    {
        node->rchild = this->addNodeFromNode(value, node->rchild);
        if (this->height(node->rchild) - this->height(node->lchild) == 2)
        {
            if (value > node->rchild->value)
                node = this->RR_Rotate(node);
            else
                node = this->RL_Rotate(node);
        }
    }
    node->height = this->max(this->height(node->lchild), this->height(node->rchild)) + 1;
    return node;
}

template <typename T>
void AVLTree<T>::addNode(T value)
{
    this->addNodeFromNode(value, this->root);
}

template <typename T>
typename AVLTree<T>::AVLTreeNode* AVLTree<T>::deleteNodeFromNode(T value, AVLTreeNode *node)
{
    if (node == NULL)
        return NULL;
    if (value < node->value)
    {
        node->lchild = this->deleteNodeFromNode(value, node->lchild);
        if (this->height(node->rchild) - this->height(node->lchild) == 2)
        {
            AVLTreeNode *tmpNode = node->rchild;
            if (this->height(tmpNode->lchild) > this->height(tmpNode->rchild))
                node = this->RL_Rotate(node);
            else
                node = this->RR_Rotate(node);
        }
    }
    else if (value > node->value)
    {
        node->rchild = this->deleteNodeFromNode(value, node->rchild);
        if (this->height(node->lchild) - this->height(node->rchild) == 2)
        {
            AVLTreeNode *tmpNode = node->lchild;
            if (this->height(tmpNode->rchild) > this->height(tmpNode->lchild))
                node = this->LR_Rotate(node);
            else
                node = this->LL_Rotate(node);
        }
    }
    else
    {
        if (node->lchild != NULL && node->rchild != NULL)
        {
            if (this->height(node->lchild) > this->height(node->rchild))
            {
                AVLTreeNode *nodeToReplace = node->lchild;
                while (nodeToReplace->rchild != NULL)
                    nodeToReplace = nodeToReplace->rchild;
                node->value = nodeToReplace->value;
                node->rchild = this->deleteNodeFromNode(nodeToReplace->value, node->lchild);
            }
            else
            {
                AVLTreeNode *nodeToReplace = node->rchild;
                while (nodeToReplace->lchild != NULL)
                    nodeToReplace = nodeToReplace->lchild;
                node->value = nodeToReplace->value;
                node->lchild = this->deleteNodeFromNode(nodeToReplace->value, node->rchild);
            }
        }
        else
        {
            AVLTreeNode *tmpNode = node;
            if (node->lchild != NULL)
                node = node->lchild;
            else
                node = node->rchild;
            delete tmpNode;
        }
    }
    return node;
}

template <typename T>
void AVLTree<T>::deleteNode(T value)
{
    this->deleteNodeFromNode(value, this->root);
}

#endif /* AVLTree_hpp */
