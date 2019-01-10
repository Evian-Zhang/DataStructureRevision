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
    Student* array[4];
    array[0] = stu1;
    array[1] = stu2;
    array[2] = stu3;
    array[3] = stu4;
    
    cout << Search<Student*>::BSTreeSearch(array, 4, stu3);
    return 0;
}
