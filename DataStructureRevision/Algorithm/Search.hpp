//
//  Search.hpp
//  DataStructureRevision
//
//  Created by Evian张 on 2019/1/6.
//  Copyright © 2019 Evian张. All rights reserved.
//

#ifndef Search_hpp
#define Search_hpp

template <typename T>
class Search
{
    
    
public:
    /**
     @brief 顺序查找
     @discussion 顺序查找，时间复杂度为O(n)

     @param length array的长度
     @param key 关键字。需要对类T重载==
     @return key第一次出现时所在位置的下标；若不存在则返回-1
     */
    static int seqSearch(T *array, int length, T key);
    
    /**
     @brief 二分查找
     @discussion 二分查找，时间复杂度为O(logn)

     @param array 待查找数组。需要按关键字升序。
     @param length array的长度
     @param key 关键字。需要对类T重载==
     @return key第一次出现时所在位置的下标；若不存在则返回-1
     */
    static int binarySearch(T *array, int length, T key);
};

template <typename T>
int Search<T>::seqSearch(T *array, int length, T key)
{
    for (int index = 0; index < length; index++)
        if (array[index] == key)
            return index;
    return -1;
}

template <typename T>
int Search<T>::binarySearch(T *array, int length, T key)
{
    int low = 0, high = length - 1;
    while (low <= high)
    {
        int mid = (low + high) / 2;
        if (array[mid] == key)
            return mid;
        else if (array[mid] < key)
            high = mid - 1;
        else
            low = mid + 1;
    }
    return -1;
}

#endif /* Search_hpp */
