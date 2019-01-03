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
#include "Graph/GraphByAdjMat.hpp"
#include "GraphByAdjList.hpp"
using namespace std;

int main()
{
    GraphByAdjMat<Student> *graph = new GraphByAdjMat<Student>();
    Student *stu1 = new Student("zhangshu", "57117213", 100);
    Student *stu2 = new Student("zjd", "71117123", 100);
    graph->addVertex(*stu1);
    graph->addVertex(*stu2);
    graph->addEdge(0, 1, 1);
    graph->display();
    GraphByAdjList<Student> *graph2 = new GraphByAdjList<Student>();
    graph2->createFromAdjMat(graph);
    graph2->display();
    delete stu1;
    delete stu2;
    delete graph;
    delete graph2;
    return 0;
}
