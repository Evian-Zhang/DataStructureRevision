//
//  Student.hpp
//  DataStructureRevision
//
//  Created by Evian张 on 2018/12/29.
//  Copyright © 2018 Evian张. All rights reserved.
//

#ifndef Student_hpp
#define Student_hpp

#include <string.h>
#include <iostream>

class Student
{
    friend std::ostream& operator<<(std::ostream& output, const Student& student);
public:
    char name[16];
    char id[16];
    short score;
    
    Student(char* name = "0", char* id = "0", short score = 0);
    
    static bool createStudent(Student& student);
    
    /** 比较两个对象的成绩是否相等，相等则返回true */
    static bool compare(Student student1, Student student2);
    
    /** 重载赋值运算符 */
    Student& operator=(Student& student);
};

#endif /* Student_hpp */
