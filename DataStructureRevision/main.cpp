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
    SequenceListByArray<Student> *studentListMgr = new SequenceListByArray<Student>();
    Student *stu1 = new Student("zhangshu", "571", 123);
    studentListMgr->insert(*stu1, 0);
    int index;
    studentListMgr->locate(*stu1, Student::compare, index);
    cout << index << endl;
    return 0;
}
