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
using namespace std;

int main()
{
    SparseMatrix<Student>* mat = new SparseMatrix<Student>(10, 10);
    Student* stu1 = new Student("张曙", "571", 122);
    Student* stu2 = new Student("zs", "572", 121);
    Student* stu3 = new Student("zhangshu", "123", 213);
    
    mat->addElement(*stu1, 2, 2);
    mat->addElement(*stu2, 2, 5);
    mat->addElement(*stu3, 3, 4);
    
    mat->display();
    cout << endl;
    SparseMatrix<Student>* mat2 = mat->transpose();
    mat2->display();
    cout << endl;
    mat2 = mat->fastTranspose();
    mat2->display();
    cout << endl;
    return 0;
}
