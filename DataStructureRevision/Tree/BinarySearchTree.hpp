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
    class A : BinaryTree<T>::BTreeNode
    {
        
    };
};

template <typename T>
void BinarySearchTree<T>::addNode(T value)
{
    BinaryTree<T>::BTreeNode *node;
}

#endif /* BinarySearchTree_hpp */
