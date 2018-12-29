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
using namespace std;

int main()
{
    Stack<Student> *stack = new Stack<Student>;
    stack->display();
    Student *stu1 = new Student("zhangshu", "571", 123);
    stack->push(*stu1);
    stack->display();
    Student *stu2 = new Student("zs", "570", 122);
    stack->push(*stu2);
    stack->display();
    Student *stu = new Student();
    stack->pop(*stu);
    cout << *stu << endl;
    stack->display();
    return 0;
}
