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
#include "Tree/BinarySearchTree.hpp"
#include "Tree/AVLTree.hpp"
#include "Tree/BTree.hpp"
#include "Tree/B+Tree.hpp"
#include "Graph/GraphByAdjMat.hpp"
#include "GraphByAdjList.hpp"
#include "Algorithm/Search.hpp"
using namespace std;

int main()
{
    Student *stu1 = new Student("zs", "57117213", 100);
    Student *stu2 = new Student("hth", "1234", 90);
    Student *stu3 = new Student("hyy", "4321", 95);
    Student *stu4 = new Student("wlw", "3214", 60);
    Student *stu5 = new Student("lyx", "12343", 99);
    BTree<Student> *tree = new BTree<Student>();
    tree->display();
    tree->addKey(*stu1);
    tree->display();
    tree->addKey(*stu2);
    tree->display();
    tree->addKey(*stu3);
    tree->display();
    tree->addKey(*stu4);
    tree->display();
    tree->addKey(*stu5);
    tree->display();
    return 0;
}
