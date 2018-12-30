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
using namespace std;

int main()
{
    char str[1000] = "abdstfhgjkhgfdhjgfdjhvbcfghjgvcghjgvgugvjkbknbmbvgfdsrdtfyuababac";
    char substr[100] = "ababac";
    int i = String::kmpMatch(str, 65, substr, 6);
    cout << i;
    return 0;
}
