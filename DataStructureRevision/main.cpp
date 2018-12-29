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
using namespace std;

int main()
{
    Student *stu1 = new Student("zhangshu", "571", 123);
    BiLinkedList<Student> *studentListMgr = new BiLinkedList<Student>();
    studentListMgr->display();
    studentListMgr->insertInHead(*stu1);
    studentListMgr->display();
    Student *stu2 = new Student("zs", "5132", 123);
    studentListMgr->insertInHead(*stu2);
    studentListMgr->display();
    studentListMgr->removeByKey(*stu2, Student::compare);
    studentListMgr->display();
    return 0;
}
