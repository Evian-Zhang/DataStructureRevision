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
using namespace std;

int main()
{
    BinaryTree<Student>* btree = new BinaryTree<Student>;
    btree->preOrderCreateTree(Student::createStudent);
    btree->display();
    cout << "\n\n\n\npreOrderTraverse: "<< endl;
    btree->preOrderTraverse(Student::display);
    cout << "\n\n\n\npreOrderTraverseWithStack: "<< endl;
    btree->preOrderTraverseWithStack(Student::display);
    cout << "\n\n\n\ninOrderTraverse: "<< endl;
    btree->inOrderTraverse(Student::display);
    cout << "\n\n\n\ninOrderTraverseWithStack: "<< endl;
    btree->inOrderTraverseWithStack(Student::display);
    cout << "\n\n\n\npostOrderTraverse: "<< endl;
    btree->postOrderTraverse(Student::display);
    cout << "\n\n\n\npostOrderTraverseWithStack: "<< endl;
    btree->postOrderTraverseWithStack(Student::display);
    return 0;
}
