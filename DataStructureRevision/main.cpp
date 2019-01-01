//
//  main.cpp
//  DataStructureRevision
//
//  Created by Evian张 on 2018/12/28.
//  Copyright © 2018 Evian张. All rights reserved.
//

#include <iostream>

#include "Test/Student.hpp"
#include "SequenceList/SequenceListByArray.hpp"
#include "SequenceList/SequenceListByPtr.hpp"
#include "LinkedList/UniLinkedList.hpp"
#include "LinkedList/BiLinkedList.hpp"
#include "Stack/Stack.hpp"
#include "Queue/Queue.hpp"
#include "Queue/CircularQueue.hpp"
#include "String/String.hpp"
#include "SparseMatrix/SparseMatrix.hpp"
#include "Tree/BinaryTree.hpp"
#include "Tree/ThreadedBinaryTree.hpp"
using namespace std;

int main()
{
    ThreadedBinaryTree<Student> *tree = new ThreadedBinaryTree<Student>();
    tree->preOrderCreateTree(Student::createStudent);
    
    tree->display();
    tree->preOrderTraverse(Student::display);
    tree->display();
    tree->inOrderTraverse(Student::display);
    tree->display();
    tree->postOrderTraverse(Student::display);
    tree->display();
    delete tree;
    return 0;
}
