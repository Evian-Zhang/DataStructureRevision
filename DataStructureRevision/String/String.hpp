//
//  String.hpp
//  DataStructureRevision
//
//  Created by Evian张 on 2018/12/30.
//  Copyright © 2018 Evian张. All rights reserved.
//

#ifndef String_hpp
#define String_hpp

class String
{
    /**
     获得next数组

     @param str 模式串
     @param length 模式串长度
     @param next next数组
     */
    static void getNext(char* str, int length, int* next);
    
public:
    /**
     KMP前缀匹配算法

     @param str 目标串
     @param strLength 目标串长度
     @param substr 模式串
     @param substrLength 模式串长度
     @return 模式串在目标串中第一次出现的下标。若没有则返回-1
     */
    static int kmpMatch(char *str, int strLength, char *substr, int substrLength);
};

void String::getNext(char* str, int length, int* next)
{
    int prefixIndex = -1;
    next[0] = prefixIndex;
    for (int strIndex = 1; strIndex < length; strIndex++)
    {
        while (prefixIndex > -1 && str[prefixIndex + 1] != str[strIndex])
            prefixIndex = next[prefixIndex];
        if (str[prefixIndex + 1] == str[strIndex])
            prefixIndex++;
        next[strIndex] = prefixIndex;
    }
}

int String::kmpMatch(char *str, int strLength, char *substr, int substrLength)
{
    int *next = new int[substrLength];
    String::getNext(substr, substrLength, next);
    int matchIndex = -1;
    for (int strIndex = 0; strIndex < strLength; strIndex++)
    {
        while (matchIndex > -1 && substr[matchIndex + 1] != str[strIndex])
            matchIndex = next[matchIndex];
        if (substr[matchIndex + 1] == str[strIndex])
            matchIndex++;
        if (matchIndex == substrLength - 1)
        {
            delete[] next;
            return strIndex - substrLength + 1;
        }
    }
    delete[] next;
    return -1;
}

#endif /* String_hpp */
