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
    Student *stu3 = new Student("wgq", "57117214", 100);
    Student *stu4 = new Student("zz", "71117124", 100);
    graph->addVertex(*stu1);
    graph->addVertex(*stu2);
    graph->addVertex(*stu3);
    graph->addVertex(*stu4);
    graph->addEdge(0, 1, 1);
    graph->addEdge(0, 2, 2);
    graph->addEdge(0, 3, 3);
    graph->addEdge(1, 2, 4);
    graph->addEdge(1, 3, 5);
    graph->addEdge(2, 3, 6);
    graph->addEdge(1, 0, 1);
    graph->addEdge(2, 0, 2);
    graph->addEdge(3, 0, 3);
    graph->addEdge(2, 1, 4);
    graph->addEdge(3, 1, 5);
    graph->addEdge(3, 2, 6);
    graph->display();
    GraphByAdjList<Student> *graph2 = new GraphByAdjList<Student>();
    graph2->createFromAdjMat(graph);
    graph2->display();
    graph2->DFSTraverse(Student::display);
    cout << endl;
    graph2->BFSTraverse(Student::display);
    
    cout << endl;
    cout << graph->Prim(0);
    
    cout << endl;
    cout << graph->topologicalSort() << endl;
    
    BiLinkedList<Student>** path = graph->Dijkstra(0);
    for (int i = 0; i < 4; i++)
        path[i]->display();
    delete stu1;
    delete stu2;
    delete stu3;
    delete stu4;
    delete graph;
    delete graph2;
    return 0;
}
