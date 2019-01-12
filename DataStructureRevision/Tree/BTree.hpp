//
//  BTree.hpp
//  DataStructureRevision
//
//  Created by Evian张 on 2019/1/11.
//  Copyright © 2019 Evian张. All rights reserved.
//

#ifndef BTree_hpp
#define BTree_hpp

#include <iostream>

template <typename T>
class BTree
{
    static const int M = 5;
    
    int ceilHalf(int x)
    {
        return (x % 2) ? ((x + 1) / 2) : (x / 2);
    }
    
    const int KEY_MIN = this->ceilHalf(M) - 1;
    const int KEY_MAX = M - 1;
    class BTreeNode
    {
    public:
        BTreeNode()
        {
            this->keyCount = 0;
            this->parent = NULL;
            for (int i = 0; i < M + 1; i ++)
            {
                this->children[i] = NULL;
            }
        }
        int keyCount;
        BTreeNode *parent;
        T key[M + 1];//key[0]未用, key[M + 1]用于分裂时的临时空间
        BTreeNode* children[M + 1];
    };
    
    int count;
    
    BTreeNode *root;
    
    void postOrderTraverseDeleteNode(BTreeNode *node);
    
    void displayFromNode(BTreeNode* node, int indent);
    
    void addKeyAtNode(T value, BTreeNode*& node, BTreeNode *splitedChild);
    
public:
    /** 初始化 */
    BTree();
    
    /** 析构函数 */
    ~BTree();
    
    /**
     @brief 打印B树
     @discussion 打印B树。需要对类T重载<<算符
     */
    void display();
    
    /**
     @brief 搜索
     @discussion 利用B树搜索，时间复杂度为O(logn)
     */
    T* search(T key);
    
    /**
     @brief 增加节点
     @discussion 增加节点，需要对类T重载=, ==与<
     */
    void addKey(T value);
};

template <typename T>
BTree<T>::BTree()
{
    this->count = 0;
    this->root = NULL;
}

template <typename T>
void BTree<T>::postOrderTraverseDeleteNode(BTreeNode *node)
{
    for (int i = 0; i <= node->keyCount; i++)
    {
        if (node->children[i] != NULL)
            this->postOrderTraverseDeleteNode(node->children[i]);
    }
    delete node;
}

template <typename T>
BTree<T>::~BTree()
{
    if (this->root != NULL)
        this->postOrderTraverseDeleteNode(this->root);
}

template <typename T>
void BTree<T>::displayFromNode(BTreeNode *node, int indent)
{
    for (int i = 0; i < node->keyCount + 1; i++)
    {
        for (int j = 0; j < indent; j++)
            std::cout << "          ";
        std::cout << "+---------";
        std::cout << "key[" << i << "]: " << node->key[i] << std::endl;
        if (node->children[i] != NULL)
            this->displayFromNode(node->children[i], indent + 1);
    }
}

template <typename T>
void BTree<T>::display()
{
    if (this->root == NULL)
        std::cout << "NULL" << std::endl;
    else
        this->displayFromNode(this->root, 0);
}

template <typename T>
T* BTree<T>::search(T key)
{
    BTreeNode *node = this->root;
    while (node != NULL)
    {
        for (int i = 0; i < node->keyCount; i++)
        {
            if (key == node->key[i + 1])
                return &(node->key[i + 1]);
            else if (key < node->key[i + 1])
                node = node->children[i];
            else if (key > node->key[node->keyCount + 1])
                node = node->children[node->keyCount + 1];
        }
    }
    return NULL;
}

template <typename T>
void BTree<T>::addKeyAtNode(T value, BTreeNode *&node, BTreeNode *splitedChild)
{
    if (node != NULL)
    {
        int insertedIndex;
        for (insertedIndex = 1; insertedIndex <= node->keyCount; insertedIndex++)
            if (value < node->key[insertedIndex])
                break;
        for (int i = node->keyCount + 1; i > insertedIndex; i--)
        {
            node->key[i] = node->key[i - 1];
            node->children[i] = node->children[i - 1];
        }
        node->key[insertedIndex] = value;
        node->children[insertedIndex] = splitedChild;
    }
    else
    {
        node = new BTreeNode();
        node->key[1] = value;
        node->children[0] = this->root;
        node->children[1] = splitedChild;
        this->root = node;
    }
    
    if (node->keyCount < this->KEY_MAX)
    {
        node->keyCount++;
    }
    else
    {
        int splitIndex = this->ceilHalf(M) + 1;
        BTreeNode *splitedNode = new BTreeNode();
        splitedNode->parent = node->parent;
        for (int i = 0; i < M - splitIndex; i++)
        {
            splitedNode->key[i + 1] = node->key[i + splitIndex + 1];
            splitedNode->children[i + 1] = node->children[i + splitIndex + 1];
            node->children[i + splitIndex + 1] = NULL;
            splitedNode->keyCount++;
            node->keyCount--;
        }
        splitedNode->children[0] = node->children[splitIndex];
        node->children[splitIndex] = NULL;
        node->keyCount--;//减去中间的那个关键字
        this->addKeyAtNode(node->key[splitIndex], node->parent, splitedNode);
    }
}

template <typename T>
void BTree<T>::addKey(T value)
{
    if (this->root == NULL)
    {
        BTreeNode *node = new BTreeNode();
        node->key[1] = value;
        node->keyCount++;
        this->root = node;
        return;
    }
    BTreeNode *node = this->root;
    
    bool findNode = false;
    
    while (!findNode)
    {
        for (int i = 0; i < node->keyCount; i++)
        {
            if (value == node->key[i + 1])
                return;
            else if (value < node->key[i + 1])
            {
                if (node->children[i] != NULL)
                    node = node->children[i];
                else
                    findNode = true;
                break;
            }
            else if (value > node->key[node->keyCount])
            {
                if (node->children[i] != NULL)
                    node = node->children[node->keyCount];
                else
                    findNode = true;
                break;
            }
        }
    }
    this->count++;
    this->addKeyAtNode(value, node, NULL);
}

#endif /* BTree_hpp */
