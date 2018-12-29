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
using namespace std;

int main()
{
    Queue<Student>* queue = new Queue<Student>;
    queue->display();
    Student *stu1 = new Student("zhangshu", "571", 123);
    queue->enQueue(*stu1);
    queue->display();
    Student *stu2 = new Student("zs", "570", 212);
    queue->enQueue(*stu2);
    queue->display();
    Student *stu3 = new Student();
    queue->deQueue(*stu3);
    cout << *stu3 << endl;
    queue->display();
    return 0;
}
