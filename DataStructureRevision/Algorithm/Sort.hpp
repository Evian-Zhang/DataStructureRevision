//
//  Sort.hpp
//  DataStructureRevision
//
//  Created by Evian张 on 2019/1/12.
//  Copyright © 2019 Evian张. All rights reserved.
//

#ifndef Sort_hpp
#define Sort_hpp

template <typename T>
class Sort
{
    static void swap(T &a, T &b)
    {
        T c = a;
        a = b;
        b = c;
    }
    
    static void quickSortWithStartAndEnd(T *array, int start, int end);
    
public:
    /**
     @brief 插入排序
     @discussion 插入排序，时间复杂度为O(n^2), 稳定排序

     @param array 待排序数组。需对类T重载<
     @param length array的长度
     */
    static void insertSort(T *array, int length);
    
    /**
     @brief 折半插入排序
     @discussion 折半插入排序，时间复杂度为O(n^2), 稳定排序

     @param array 待排序数组。需对类T重载<
     @param length array的长度
     */
    static void biInsertSort(T *array, int length);
    
    /**
     @brief 2-路插入排序
     @discussion 2-路插入排序，时间复杂度为O(n^2), 稳定排序

     @param array 待排序数组。需对类T重载<
     @param length array的长度
     */
    static void twoWayInsertSort(T *array, int length);
    
    /**
     @brief 冒泡排序
     @discussion 冒泡排序，时间复杂度为O(n^2), 不稳定排序

     @param array 待排序数组。需对类T重载<
     @param length array的长度
     */
    static void bubbleSort(T *array, int length);
    
    /**
     @brief 快速排序
     @discussion 快速排序，时间复杂度为O(n^2), 不稳定排序
     
     @param array 待排序数组。需对类T重载<
     @param length array的长度
     */
    static void quickSort(T *array, int length);
};

template <typename T>
void Sort<T>::insertSort(T *array, int length)
{
    if (length < 2)
        return;
    
    for (int i = 1; i < length; i++)
    {
        T tmp = array[i];
        int j = i;
        while (j > 0 && tmp < array[j - 1])
        {
            array[j] = array[j - 1];
            j--;
        }
        array[j] = tmp;
    }
}

template <typename T>
void Sort<T>::biInsertSort(T *array, int length)
{
    if (length < 2)
        return;
    for (int i = 1; i < length; i++)
    {
        int high = i - 1;
        int low = 0;
        T tmp = array[i];
        while (high >= low)
        {
            int mid = (low + high) / 2;
            if (tmp < array[mid])
                high = mid - 1;
            else
                low = mid + 1;
        }
        for (int j = i; j > high + 1; --j)
        {
            array[j] = array[j - 1];
        }
        array[high + 1] = tmp;
    }
}

template <typename T>
void Sort<T>::twoWayInsertSort(T *array, int length)
{
    if (length < 2)
        return;
    
    T tmpArray[length];
    int front = 0;
    int rear = 0;
    tmpArray[0] = array[0];
    for (int i = 1; i < length; i++)
    {
        if (array[i] < tmpArray[front])
        {
            front = (front + length - 1) % length;
            tmpArray[front] = array[i];
        }
        else if (array[i] > tmpArray[rear])
        {
            rear = (rear + length + 1) % length;
            tmpArray[rear] = array[i];
        }
        else
        {
            T tmp = array[i];
            rear = (rear + length + 1) % length;
            int j = rear;
            while (tmp < tmpArray[(j + length - 1) % length])
            {
                tmpArray[j] = tmpArray[(j + length - 1) % length];
                j = (j + length - 1) % length;
            }
            tmpArray[j] = tmp;
        }
    }
    
    for (int i = 0; i < length; i++)
        array[i] = tmpArray[(front + i + length) % length];
}

template <typename T>
void Sort<T>::bubbleSort(T *array, int length)
{
    if (length < 2)
        return;
    
    for (int i = 0; i < length; i++)
    {
        int smallestIndex = i;
        for (int j = i + 1; j < length; j++)
        {
            if (array[j] < array[smallestIndex])
                smallestIndex = j;
        }
        Sort<T>::swap(array[i], array[smallestIndex]);
    }
}

template <typename T>
void Sort<T>::quickSortWithStartAndEnd(T *array, int start, int end)
{
    if (start >= end)
        return;
    int first = start;
    int last = end;
    T key = array[first];
    
    while (first < last)
    {
        while (last > first)
        {
            if (array[last] < key)
                break;
            last--;
        }
        array[first] = array[last];
        
        while (first < last)
        {
            if (key < array[first])
                break;
            first++;
        }
        array[last] = array[first];
    }
    
    array[first] = key;
    Sort<T>::quickSortWithStartAndEnd(array, start, first - 1);
    Sort<T>::quickSortWithStartAndEnd(array, first + 1, end);
}

template <typename T>
void Sort<T>::quickSort(T *array, int length)
{
    Sort<T>::quickSortWithStartAndEnd(array, 0, length - 1);
}

#endif /* Sort_hpp */
