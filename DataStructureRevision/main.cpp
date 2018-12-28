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
using namespace std;

int main()
{
    SequenceListByArray<Student> *studentListMgr = new SequenceListByArray<Student>();
    Student *stu1 = new Student("zhangshu", "571", 123);
    studentListMgr->insert(*stu1, 0);
    Student *stu2 = new Student();
    studentListMgr->get(0, *stu2);
    studentListMgr->remove(0);
    cout << studentListMgr->getCount();
    
    return 0;
}
