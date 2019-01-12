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
    
    /** 堆排序的辅助函数。已知array[s..m]中记录的关键字除array[s]之外均满足最大堆的定义 */
    static void heapAdjust(T *array, int s, int m);
    
    static void heapCreate(T *array, int length);
    
    /** 2-路归并排序的辅助函数。已知array[i..m]和array[m + 1..n]均有序。填入到有序的targetList[i..n] */
    static void merge(T *array, T *targetArray, int i, int m, int n);
    
    static void mergeSortWithTmpArray(T *array, T *targetArray, int start, int end);
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
    
    /**
     @brief 选择排序
     @discussion 选择排序，时间复杂度为O(n^2), 不稳定排序
     
     @param array 待排序数组。需对类T重载<
     @param length array的长度
     */
    static void selectSort(T *array, int length);
    
    /**
     @brief 堆排序
     @discussion 堆排序，时间复杂度为O(nlogn), 不稳定排序
     
     @param array 待排序数组。需对类T重载<
     @param length array的长度
     */
    static void heapSort(T *array, int length);
    
    /**
     @brief 归并排序
     @discussion 归并排序，时间复杂度为O(nlogn), 稳定排序

     @param array 待排序数组。需对类T重载<
     @param length array的长度
     */
    static void mergeSort(T *array, int length);
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
        for (int j = 0; j < length - i - 1; j++)
            if (array[j + 1] < array[j])
                Sort<T>::swap(array[j], array[j + 1]);
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

template <typename T>
void Sort<T>::selectSort(T *array, int length)
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
void Sort<T>::heapAdjust(T *array, int s, int m)
{
    T tmp = array[s];
    for (int i = 2 * s + 1; i <= m; i = 2 * i + 1)
    {
        if (i < m && array[i] < array[i + 1])
            i++;
        if (tmp > array[i])
            break;
        array[s] = array[i];
        s = i;
    }
    array[s] = tmp;
}

template <typename T>
void Sort<T>::heapCreate(T *array, int length)
{
    for (int i = (length - 2) / 2; i >= 0; i--)
        Sort<T>::heapAdjust(array, i, length - 1);
}

template <typename T>
void Sort<T>::heapSort(T *array, int length)
{
    Sort<T>::heapCreate(array, length);
    for (int i = length - 1; i > 0; i--)
    {
        Sort<T>::swap(array[i], array[0]);
        Sort<T>::heapAdjust(array, 0, i - 1);
    }
}

template <typename T>
void Sort<T>::merge(T *array, T* targetArray, int i, int m, int n)
{
    int j = m + 1;
    int k = i;
    while (i <= m && j <= n)
    {
        if (array[i] < array[j])
        {
            targetArray[k] = array[i];
            i++;
        }
        else
        {
            targetArray[k] = array[j];
            j++;
        }
        k++;
    }
    while (i <= m)
    {
        targetArray[k] = array[i];
        i++;
        k++;
    }
    while (j <= n)
    {
        targetArray[k] = array[j];
        j++;
        k++;
    }
}

template <typename T>
void Sort<T>::mergeSortWithTmpArray(T *array, T *targetArray, int start, int end)
{
    if (start == end)
        targetArray[start] = array[end];
    else
    {
        T tmpArray[end + 1];
        int mid = (start + end) / 2;
        Sort<T>::mergeSortWithTmpArray(array, tmpArray, start, mid);
        Sort<T>::mergeSortWithTmpArray(array, tmpArray, mid + 1, end);
        Sort<T>::merge(tmpArray, targetArray, start, mid, end);
    }
}

template <typename T>
void Sort<T>::mergeSort(T *array, int length)
{
    T tmpArray[length];
    Sort<T>::mergeSortWithTmpArray(array, tmpArray, 0, length - 1);
    for (int i = 0; i < length; i++)
        array[i] = tmpArray[i];
}

#endif /* Sort_hpp */
