//
//  Student.cpp
//  DataStructureRevision
//
//  Created by Evian张 on 2018/12/29.
//  Copyright © 2018 Evian张. All rights reserved.
//

#include "Student.hpp"
Student::Student(char* name, char* id, short score)
{
    if (name != NULL)
        strcpy(this->name, name);
    else
        strcpy(this->name, "0");
    if (id != NULL)
        strcpy(this->id, id);
    else
        strcpy(this->id, "0");
    this->score = score;
}

std::ostream& operator<<(std::ostream& output, const Student& student)
{
    output << student.name;
    return output;
}

bool Student::compare(Student student1, Student student2)
{
    return !strcmp(student1.name, student2.name);
}

Student& Student::operator=(Student& student)
{
    strcpy(this->name, student.name);
    strcpy(this->id, student.id);
    this->score = student.score;
    return student;
}
