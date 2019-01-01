//
//  ThreadedBinaryTree.hpp
//  DataStructureRevision
//
//  Created by Evian张 on 2018/12/31.
//  Copyright © 2018 Evian张. All rights reserved.
//

#ifndef ThreadedBinaryTree_hpp
#define ThreadedBinaryTree_hpp

#include <iostream>

template <typename T>
class ThreadedBinaryTree
{
    enum PointerTag
    {
        LINK,
        THREAD
    };
    
    enum NodePosition
    {
        LTREE,
        RTREE
    };
    
    class ThreadedBTreeNode
    {
    public:
        T value;
        ThreadedBTreeNode *parent;
        PointerTag ltag;
        ThreadedBTreeNode *lchild;
        PointerTag rtag;
        ThreadedBTreeNode *rchild;
    };
    
    ThreadedBTreeNode *root;
    int count;
    
    /** display的辅助函数 */
    void displayFromNode(ThreadedBTreeNode* node, NodePosition nodePos, PointerTag nodeTag, int indent);
    
    /** preOrderCreateTree的辅助函数 */
    void preOrderCreateTreeFromNode(ThreadedBTreeNode *preNode, ThreadedBTreeNode *&node, bool (*createNode)(T&));
    
    /** preThreading的辅助函数 */
    void preThreadingFromNode(ThreadedBTreeNode *node);
    
    /** inThreading的辅助函数 */
    void inThreadingFromNode(ThreadedBTreeNode *node);
    
    /** postThreading的辅助函数 */
    void postThreadingFromNode(ThreadedBTreeNode *node);
    
    /** 析构函数的辅助函数 */
    void postOrderTraverseToDeleteNode(ThreadedBTreeNode *node);
    
    /** 将所有的线索清空的辅助函数 */
    void clearThreadFromNode(ThreadedBTreeNode *node);
    
public:
    /** 初始化 */
    ThreadedBinaryTree();
    
    /** 析构函数 */
    ~ThreadedBinaryTree();
    
    /**
     @brief 打印线索化二叉树
     @discussion 打印线索化二叉树。需要对类T重载<<算符
     */
    void display();
    
    /**
     @brief 建立二叉树
     @discussion 前序遍历建立二叉树，若createNode返回false则停止继续往下延伸
     */
    void preOrderCreateTree(bool (*createNode)(T&));
    
    /** 前序线索化二叉树 */
    void preThreading();
    
    /** 中序线索化二叉树 */
    void inThreading();
    
    /** 后序线索化二叉树 */
    void postThreading();
    
    /**
     @brief 前序遍历线索化二叉树
     @discussion 利用线索前序遍历线索化二叉树
     */
    void preOrderTraverse(void (*visit)(T));
    
    /**
     @brief 中序遍历线索化二叉树
     @discussion 利用线索中序遍历线索化二叉树
     */
    void inOrderTraverse(void (*visit)(T));

    /**
     @brief 后序遍历线索化二叉树
     @discussion 利用线索后序遍历线索化二叉树
     */
    void postOrderTraverse(void (*visit)(T));
};

template <typename T>
ThreadedBinaryTree<T>::ThreadedBinaryTree()
{
    this->root = NULL;
    this->count = 0;
}

template <typename T>
void ThreadedBinaryTree<T>::postOrderTraverseToDeleteNode(ThreadedBTreeNode *node)
{
    if (node->ltag == LINK)
        this->postOrderTraverseToDeleteNode(node->lchild);
    if (node->rtag == LINK)
        this->postOrderTraverseToDeleteNode(node->rchild);
    delete node;
}

template <typename T>
ThreadedBinaryTree<T>::~ThreadedBinaryTree()
{
    this->postOrderTraverseToDeleteNode(this->root);
}

template <typename T>
void ThreadedBinaryTree<T>::displayFromNode(ThreadedBTreeNode *node, NodePosition nodePos, PointerTag nodeTag, int indent)
{
    for (int i = 0; i < indent; i++)
        std::cout << "          ";
    std::cout << "+---------";
    switch (nodePos)
    {
        case LTREE:
            std::cout << "LT";
            break;
        case RTREE:
            std::cout << "RT";
            break;
            
        default:
            break;
    }
    switch (nodeTag)
    {
        case LINK:
            std::cout << "(LINK): ";
            break;
        case THREAD:
            std::cout << "(THREAD): ";
            
        default:
            break;
    }
    if (node != NULL)
        std::cout << node->value << std::endl;
    else
        std::cout << "NULL" << std::endl;
    if (nodeTag == LINK && node != NULL)
    {
        this->displayFromNode(node->lchild, LTREE, node->ltag, indent + 1);
        this->displayFromNode(node->rchild, RTREE, node->rtag, indent + 1);
    }
}

template <typename T>
void ThreadedBinaryTree<T>::display()
{
    if (this->root == NULL)
        std::cout << "NULL";
    else
    {
        std::cout << "R: " << this->root->value << std::endl;
        if (this->root->lchild != NULL)
            this->displayFromNode(this->root->lchild, LTREE, this->root->ltag, 0);
        if (this->root->rchild != NULL)
            this->displayFromNode(this->root->rchild, RTREE, this->root->rtag, 0);
    }
}

template <typename T>
void ThreadedBinaryTree<T>::preOrderCreateTreeFromNode(ThreadedBTreeNode *preNode, ThreadedBTreeNode*& node, bool (*createNode)(T&))
{
    T value;
    if (createNode(value))
    {
        node = new ThreadedBTreeNode();
        node->value = value;
        node->parent = preNode;
        node->ltag = LINK;
        node->lchild = NULL;
        node->rtag = LINK;
        node->rchild = NULL;
        this->count++;
        preOrderCreateTreeFromNode(node, node->lchild, createNode);
        preOrderCreateTreeFromNode(node, node->rchild, createNode);
    }
}

template <typename T>
void ThreadedBinaryTree<T>::preOrderCreateTree(bool (*createNode)(T &))
{
    preOrderCreateTreeFromNode(NULL, this->root, createNode);
}

template <typename T>
void ThreadedBinaryTree<T>::clearThreadFromNode(ThreadedBTreeNode *node)
{
    if (node != NULL)
    {
        if (node->ltag == LINK)
            this->clearThreadFromNode(node->lchild);
        else
        {
            node->lchild = NULL;
            node->ltag = LINK;
        }
        if (node->rtag == LINK)
            this->clearThreadFromNode(node->rchild);
        else
        {
            node->rchild = NULL;
            node->rtag = LINK;
        }
    }
}

template <typename T>
void ThreadedBinaryTree<T>::preThreadingFromNode(ThreadedBTreeNode *node)
{
    static ThreadedBTreeNode *preNode = NULL;
    if (node != NULL)
    {
        if (node->lchild == NULL)
        {
            node->lchild = preNode;
            node->ltag = THREAD;
        }
        if (preNode != NULL && preNode->rchild == NULL)
        {
            preNode->rchild = node;
            preNode->rtag = THREAD;
        }
        preNode = node;
        if (node->ltag == LINK)
            this->preThreadingFromNode(node->lchild);
        if (node->rtag == LINK)
            this->preThreadingFromNode(node->rchild);
    }
}

template <typename T>
void ThreadedBinaryTree<T>::preThreading()
{
    this->clearThreadFromNode(this->root);
    this->preThreadingFromNode(this->root);
}

template <typename T>
void ThreadedBinaryTree<T>::inThreadingFromNode(ThreadedBTreeNode *node)
{
    static ThreadedBTreeNode *preNode = NULL;
    if (node != NULL)
    {
        this->inThreadingFromNode(node->lchild);
        if (node->lchild == NULL)
        {
            node->lchild = preNode;
            node->ltag = THREAD;
        }
        if (preNode != NULL && preNode->rchild == NULL)
        {
            preNode->rchild = node;
            preNode->rtag = THREAD;
        }
        preNode = node;
        if (node->rtag == LINK)
            this->inThreadingFromNode(node->rchild);
    }
}

template <typename T>
void ThreadedBinaryTree<T>::inThreading()
{
    this->clearThreadFromNode(this->root);
    this->inThreadingFromNode(this->root);
}

template <typename T>
void ThreadedBinaryTree<T>::postThreadingFromNode(ThreadedBTreeNode *node)
{
    static ThreadedBTreeNode *preNode = NULL;
    if (node != NULL)
    {
        this->postThreadingFromNode(node->lchild);
        if (node->rtag == LINK)
            this->postThreadingFromNode(node->rchild);
        if (node->lchild == NULL)
        {
            node->lchild = preNode;
            node->ltag = THREAD;
        }
        if (preNode != NULL && preNode->rchild == NULL)
        {
            preNode->rchild = node;
            preNode->rtag = THREAD;
        }
        preNode = node;
    }
}

template <typename T>
void ThreadedBinaryTree<T>::postThreading()
{
    this->clearThreadFromNode(this->root);
    this->postThreadingFromNode(this->root);
}

template <typename T>
void ThreadedBinaryTree<T>::preOrderTraverse(void (*visit)(T))
{
    preThreading();
    if (this->root != NULL)
    {
        ThreadedBTreeNode *node = this->root;
        while (node != NULL)
        {
            visit(node->value);
            while (node->ltag == LINK)
            {
                node = node->lchild;
                visit(node->value);
            }
            node = node->rchild;
        }
    }
}

template <typename T>
void ThreadedBinaryTree<T>::inOrderTraverse(void (*visit)(T))
{
    inThreading();
    if (this->root != NULL)
    {
        ThreadedBTreeNode *node = this->root;
        while (node != NULL)
        {
            while (node->ltag == LINK)
                node = node->lchild;
            visit(node->value);
            while (node != NULL && node->rtag == THREAD)
            {
                node = node->rchild;
                visit(node->value);
            }
            node = node->rchild;
        }
    }
}

template <typename T>
void ThreadedBinaryTree<T>::postOrderTraverse(void (*visit)(T))
{
    postThreading();
    if (this->root != NULL)
    {
        ThreadedBTreeNode *node = this->root;
        ThreadedBTreeNode *preNode = NULL;
        while (preNode != this->root)
        {
            while (node->ltag == LINK)
                node = node->lchild;
            while (node != NULL && node->rtag == THREAD)
            {
                visit(node->value);
                preNode = node;
                node = node->rchild;
            }
            while (preNode != this->root && node->rchild == preNode)
            {
                visit(node->value);
                preNode = node;
                if (preNode != this->root)
                    node = node->parent;
            }
            if (node->rtag == LINK)
                node = node->rchild;
        }
    }
}

#endif /* ThreadedBinaryTree_hpp */
