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
#include "../Queue/Queue.hpp"

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
    
    /** display的辅助函数 */
    void displayFromNode(BTreeNode* node, NodePosition nodePos, int indent);
    
    /** preOrderCreateTree的辅助函数 */
    void preOrderCreateTreeFromNode(BTreeNode *&node, bool (*createNode)(T&));
    
    /** preOrderTraverse的辅助函数 */
    void preOrderTraverseFromNode(BTreeNode *node, void (*visit)(T));
    
    /** inOrderTraverse的辅助函数 */
    void inOrderTraverseFromNode(BTreeNode *node, void (*visit)(T));
    
    /** postOrderTraverse的辅助函数 */
    void postOrderTraverseFromNode(BTreeNode *node, void (*visit)(T));
    
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
     @brief 前序遍历二叉树
     @discussion 利用栈前序遍历二叉树
     */
    void preOrderTraverseWithStack(void (*visit)(T));
    
    /**
     @brief 中序遍历二叉树
     @discussion 利用递归中序遍历二叉树
     */
    void inOrderTraverse(void (*visit)(T));
    
    /**
     @brief 中序遍历二叉树
     @discussion 利用栈中序遍历二叉树
     */
    void inOrderTraverseWithStack(void (*visit)(T));
    
    /**
     @brief 后序遍历二叉树
     @discussion 利用递归后序遍历二叉树
     */
    void postOrderTraverse(void (*visit)(T));
    
    /**
     @brief 后序遍历二叉树
     @discussion 利用栈后序遍历二叉树
     */
    void postOrderTraverseWithStack(void (*visit)(T));

    /**
     @brief 广度优先遍历二叉树
     @discussion 利用栈广度优先遍历二叉树
     */
    void BFSTraverse(void (*visit)(T));
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
    if (node->lchild != NULL)
        this->displayFromNode(node->lchild, LTree, indent + 1);
    if (node->rchild != NULL)
        this->displayFromNode(node->rchild, RTree, indent + 1);
}

template <typename T>
void BinaryTree<T>::display()
{
    if (this->root == NULL)
        std::cout << "NULL";
    else
    {
        std::cout << "R: " << this->root->value << std::endl;
        if (this->root->lchild != NULL)
            this->displayFromNode(this->root->lchild, LTree, 0);
        if (this->root->rchild != NULL)
            this->displayFromNode(this->root->rchild, RTree, 0);
    }
}

template <typename T>
void BinaryTree<T>::preOrderCreateTreeFromNode(BTreeNode*& node, bool (*createNode)(T&))
{
    T value;
    if (createNode(value))
    {
        node = new BTreeNode();
        node->value = value;
        node->lchild = NULL;
        node->rchild = NULL;
        preOrderCreateTreeFromNode(node->lchild, createNode);
        preOrderCreateTreeFromNode(node->rchild, createNode);
    }
}

template <typename T>
void BinaryTree<T>::preOrderCreateTree(bool (*createNode)(T &))
{
    preOrderCreateTreeFromNode(this->root, createNode);
}

template <typename T>
void BinaryTree<T>::preOrderTraverseFromNode(BTreeNode *node, void (*visit)(T))
{
    visit(node->value);
    if (node->lchild != NULL)
        this->preOrderTraverseFromNode(node->lchild, visit);
    if (node->rchild != NULL)
        this->preOrderTraverseFromNode(node->rchild, visit);
}

template <typename T>
void BinaryTree<T>::preOrderTraverse(void (*visit)(T))
{
    if (this->root != NULL)
        preOrderTraverseFromNode(this->root, visit);
}

template <typename T>
void BinaryTree<T>::preOrderTraverseWithStack(void (*visit)(T))
{
    if (this->root == NULL)
        return;
    Stack<BTreeNode*> *stack = new Stack<BTreeNode*>();
    BTreeNode *node = this->root;
    stack->push(node);
    while (!stack->isEmpty())
    {
        stack->pop(node);
        visit(node->value);
        if (node->rchild != NULL)
            stack->push(node->rchild);
        if (node->lchild != NULL)
            stack->push(node->lchild);
    }
    delete stack;
}

template <typename T>
void BinaryTree<T>::inOrderTraverseFromNode(BTreeNode *node, void (*visit)(T))
{
    if (node->lchild != NULL)
        this->inOrderTraverseFromNode(node->lchild, visit);
    visit(node->value);
    if (node->rchild != NULL)
        this->inOrderTraverseFromNode(node->rchild, visit);
}

template <typename T>
void BinaryTree<T>::inOrderTraverse(void (*visit)(T))
{
    if (this->root != NULL)
        inOrderTraverseFromNode(this->root, visit);
}

template <typename T>
void BinaryTree<T>::inOrderTraverseWithStack(void (*visit)(T))
{
    if (this->root == NULL)
        return;
    Stack<BTreeNode*> *stack = new Stack<BTreeNode*>();
    BTreeNode *node = this->root;
    stack->push(node);
    while (!stack->isEmpty())
    {
        stack->getTop(node);
        while (node->lchild != NULL)
        {
            node = node->lchild;
            stack->push(node);
        }
        while (stack->pop(node))
        {
            visit(node->value);
            if (node->rchild != NULL)
            {
                node = node->rchild;
                stack->push(node);
                break;
            }
        }
    }
    delete stack;
}

template <typename T>
void BinaryTree<T>::postOrderTraverseFromNode(BTreeNode *node, void (*visit)(T))
{
    if (node->lchild != NULL)
        this->postOrderTraverseFromNode(node->lchild, visit);
    if (node->rchild != NULL)
        this->postOrderTraverseFromNode(node->rchild, visit);
    visit(node->value);
}

template <typename T>
void BinaryTree<T>::postOrderTraverse(void (*visit)(T))
{
    if (this->root != NULL)
        postOrderTraverseFromNode(this->root, visit);
}

template <typename T>
void BinaryTree<T>::postOrderTraverseWithStack(void (*visit)(T))
{
    if (this->root == NULL)
        return;
    Stack<BTreeNode*> *stack = new Stack<BTreeNode*>();
    BTreeNode *node = this->root;
    BTreeNode *lastNode = NULL;
    stack->push(node);
    while (!stack->isEmpty())
    {
        stack->getTop(node);
        while (node->lchild != NULL && lastNode != node->lchild && lastNode != node->rchild)
        {
            node = node->lchild;
            stack->push(node);
        }
        while (stack->getTop(node))
        {
            if (lastNode == node->rchild || node->rchild == NULL)
            {
                stack->pop(node);
                visit(node->value);
                lastNode = node;
            }
            else if (node->rchild != NULL)
            {
                stack->push(node->rchild);
                break;
            }
        }
    }
    delete stack;
}

template <typename T>
void BinaryTree<T>::BFSTraverse(void (*visit)(T))
{
    if (this->root == NULL)
        return;
    Queue<BTreeNode*> *queue = new Queue<BTreeNode*>();
    BTreeNode *node = this->root;
    queue->enQueue(node);
    while (!queue->isEmpty())
    {
        queue->deQueue(node);
        visit(node->value);
        if (node->lchild != NULL)
            queue->enQueue(node->lchild);
        if (node->rchild != NULL)
            queue->enQueue(node->rchild);
    }
    delete queue;
}

#endif /* BinaryTree_hpp */
