//
//  BinaryTree.hpp
//  DataStructureRevision
//
//  Created by Evian张 on 2018/12/30.
//  Copyright © 2018 Evian张. All rights reserved.
//

#ifndef BinaryTree_hpp
#define BinaryTree_hpp

#include <iostream>

#include "../Stack/Stack.hpp"

template <typename T>
class BinaryTree
{
    class BTreeNode
    {
    public:
        T value;
        BTreeNode* lchild;
        BTreeNode* rchild;
    };
    
    BTreeNode* root;
    int count;
    
    enum NodePosition
    {
        LTree,
        RTree
    };
    
    void displayFromNode(BTreeNode* node, NodePosition nodePos, int indent);
    
    void preOrderCreateTreeFromNode(BTreeNode *preNode, NodePosition nodePos, bool (*createNode)(T&));
    
public:
    /** 初始化 */
    BinaryTree();
    
    /** 析构函数 */
    ~BinaryTree();
    
    /**
     @brief 打印二叉树
     @discussion 打印二叉树。需要对类T重载<<算符
     */
    void display();
    
    /**
     @brief 建立二叉树
     @discussion 前序遍历建立二叉树，若createNode返回false则停止继续往下延伸
     */
    void preOrderCreateTree(bool (*createNode)(T&));
    
    /**
     @brief 前序遍历二叉树
     @discussion 利用递归前序遍历二叉树
     */
    void preOrderTraverse(void (*visit)(T));
    
    /**
     @brief 中序遍历二叉树
     @discussion 利用递归中序遍历二叉树
     */
    void inOrderTraverse(void (*visit)(T));
    
    /**
     @brief 后序遍历二叉树
     @discussion 利用递归后序遍历二叉树
     */
    void postOrderTraverse(void (*visit)(T));

};

template <typename T>
BinaryTree<T>::BinaryTree()
{
    this->root = NULL;
    this->count = 0;
}

template <typename T>
BinaryTree<T>::~BinaryTree()
{
    this->postOrderTraverse([](T node){delete node;});
}

template <typename T>
void BinaryTree<T>::displayFromNode(BTreeNode *node, NodePosition nodePos, int indent)
{
    for (int i = 0; i < indent; i++)
        std::cout << "          ";
    std::cout << "+---------";
    switch (nodePos)
    {
        case LTree:
            std::cout << "LT: ";
            break;
        case RTree:
            std::cout << "RT: ";
            break;
            
        default:
            break;
    }
    std::cout << node->value << std::endl;
    if (node->rchild != NULL)
        this->displayFromNode(node->rchild, RTree, indent + 1);
    if (node->lchild != NULL)
        this->displayFromNode(node->lchild, LTree, indent + 1);
}

template <typename T>
void BinaryTree<T>::display()
{
    if (this->root == NULL)
        std::cout << "NULL";
    else
    {
        std::cout << "R: " << this->root->value << std::endl;
        if (this->root->rchild != NULL)
            this->displayFromNode(this->root->rchild, RTree, 0);
        if (this->root->lchild != NULL)
            this->displayFromNode(this->root->lchild, LTree, 0);
    }
}

template <typename T>
void BinaryTree<T>::preOrderCreateTreeFromNode(BTreeNode* preNode, NodePosition nodepos, bool (*createNode)(T&))
{
    T value;
    if (createNode(value))
    {
        BTreeNode *node = new BTreeNode();
        node->value = value;
        node->lchild = NULL;
        node->rchild = NULL;
        switch (nodepos)
        {
            case LTree:
                preNode->lchild = node;
                break;
            case RTree:
                preNode->rchild = node;
                break;
                
            default:
                break;
        }
        preOrderCreateTreeFromNode(node, LTree, createNode);
        preOrderCreateTreeFromNode(node, RTree, createNode);
    }
}

template <typename T>
void BinaryTree<T>::preOrderCreateTree(bool (*createNode)(T &))
{
    T value;
    if (createNode(value))
    {
        this->root = new BTreeNode();
        this->root->value = value;
        this->root->lchild = NULL;
        this->root->rchild = NULL;
        preOrderCreateTreeFromNode(this->root, LTree, createNode);
        preOrderCreateTreeFromNode(this->root, RTree, createNode);
    }
}

#endif /* BinaryTree_hpp */
