//
//  SparseMatrix.hpp
//  DataStructureRevision
//
//  Created by Evian张 on 2018/12/30.
//  Copyright © 2018 Evian张. All rights reserved.
//

#ifndef SparseMatrix_hpp
#define SparseMatrix_hpp

#include <iostream>

template <typename T>
class SparseMatrix
{
    class MatrixEle
    {
    public:
        T e;
        int row;
        int column;
    };
    
    static const int MAX_ELEMENTS_LENGTH = 128;
    MatrixEle elements[MAX_ELEMENTS_LENGTH];
    int rowSize;
    int columnSize;
    int eleCount;
    
public:
    /** 初始化 */
    SparseMatrix(int rowSize, int ColumnSize);
    
    /** 析构函数 */
    ~SparseMatrix();
    
    /**
     @brief 打印稀疏矩阵
     @discussion 打印稀疏矩阵。需要对类T重载<<算符
     */
    void display();
    
    /**
     @brief 增加稀疏矩阵元素
     @discussion 增加稀疏矩阵的元素，需要按照行主序依次输入
     */
    bool addElement(T element, int row, int column);
    
    /**
     @brief 稀疏矩阵的转置

     @return 转置后的稀疏矩阵，元素按行主序排列
     */
    SparseMatrix<T>* transpose();
    
    /**
     @brief 稀疏矩阵的快速转置
     
     @return 转置后的稀疏矩阵，元素按行主序排列
     */
    SparseMatrix<T>* fastTranspose();
};

template <typename T>
SparseMatrix<T>::SparseMatrix(int rowSize, int columnSize)
{
    this->eleCount = 0;
    this->rowSize = rowSize;
    this->columnSize = columnSize;
}

template <typename T>
SparseMatrix<T>::~SparseMatrix()
{
    for (int i = 0; i < this->eleCount; i++)
        delete this->elements[i];
}

template <typename T>
void SparseMatrix<T>::display()
{
    int elementIndex = 0;
    for (int row = 0; row < this->rowSize; row++)
    {
        for (int column = 0; column < this->columnSize; column++)
        {
            MatrixEle* matEle = &(this->elements[elementIndex]);
            if (matEle->row == row && matEle->column == column)
            {
                std::cout << matEle->e << "\t";
                elementIndex++;
            }
            else
                std::cout << "0\t";
        }
        std::cout << std::endl;
    }
}

template <typename T>
bool SparseMatrix<T>::addElement(T element, int row, int column)
{
    if (row > this->rowSize || column > this->columnSize || this->eleCount == this->MAX_ELEMENTS_LENGTH)
        return false;
    MatrixEle* addedElement = new MatrixEle();
    addedElement->e = element;
    addedElement->row = row;
    addedElement->column = column;
    this->elements[this->eleCount] = *addedElement;
    this->eleCount++;
    return true;
}

template <typename T>
SparseMatrix<T>* SparseMatrix<T>::transpose()
{
    SparseMatrix<T>* transposedMatrix = new SparseMatrix<T>(this->columnSize, this->rowSize);
    transposedMatrix->eleCount = this->eleCount;
    
    int transposedIndex = 0;
    for (int row = 0; row < transposedMatrix->rowSize; row++)
    {
        for (int eleIndex = 0; eleIndex < this->eleCount; eleIndex++)
        {
            if (this->elements[eleIndex].column == row)
            {
                MatrixEle* addedElement = &(transposedMatrix->elements[transposedIndex]);
                addedElement->e = this->elements[eleIndex].e;
                addedElement->row = this->elements[eleIndex].column;
                addedElement->column = this->elements[eleIndex].row;
                transposedIndex++;
            }
        }
    }
    return transposedMatrix;
}

template <typename T>
SparseMatrix<T>* SparseMatrix<T>::fastTranspose()
{
    SparseMatrix<T>* transposedMatrix = new SparseMatrix<T>(this->columnSize, this->rowSize);
    transposedMatrix->eleCount = this->eleCount;
    
    int num[MAX_ELEMENTS_LENGTH];
    int cpot[MAX_ELEMENTS_LENGTH];
    
    for (int column = 0; column < this->columnSize; column++)
        num[column] = 0;
    for (int index = 0; index < this->eleCount; index++)
        num[this->elements[index].column]++;
    cpot[0] = 1;
    for(int column = 1; column < this->columnSize; column++)
        cpot[column] = cpot[column - 1] + num[column - 1];
    
    int transposedIndex = 0;
    for(int index = 0; index < this->eleCount; index++)
    {
        int column = this->elements[index].column;
        transposedIndex = cpot[column];
        transposedMatrix->elements[transposedIndex].row = this->elements[index].column;
        transposedMatrix->elements[transposedIndex].column = this->elements[index].row;
        transposedMatrix->elements[transposedIndex].e = this->elements[index].e;
        cpot[column]++;
    }
    return transposedMatrix;
}

#endif /* SparseMatrix_hpp */
