//
//  main.cpp
//  DataStructureRevision
//
//  Created by Evian张 on 2018/12/28.
//  Copyright © 2018 Evian张. All rights reserved.
//

#include <iostream>
#include <stdlib.h>
#include <cstring>

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
#include "Graph/GraphByAdjMat.hpp"
#include "GraphByAdjList.hpp"
#include "Algorithm/Search.hpp"
#include "Algorithm/Sort.hpp"
using namespace std;

int main()
{
    const int M = 128;
    Student array[M];
    for (int i = 0; i < M; i++)
    {
        sprintf(array[i].name, "array[%d]", i);
        array[i].score = rand() % M;
        
        cout << array[i] << "\t";
    }
    cout << "\n\n\n";
    
    Sort<Student>::twoWayInsertSort(array, M);
    
    for (int i = 0; i < M; i++)
        cout << array[i] << "\t";
    
    return 0;
}
