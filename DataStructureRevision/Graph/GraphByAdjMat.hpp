//
//  GraphByAdjMat.hpp
//  DataStructureRevision
//
//  Created by Evian张 on 2019/1/1.
//  Copyright © 2019 Evian张. All rights reserved.
//

#ifndef GraphByAdjMat_hpp
#define GraphByAdjMat_hpp

#include <iostream>

template <typename T>
class GraphByAdjList;

template <typename T>
class GraphByAdjMat
{
    friend class GraphByAdjList<T>;
    static const int MAX_VERTEX_COUNT = 128;
    static const int INFINITY = INT_MAX;
    T vertices[MAX_VERTEX_COUNT];
    int edges[MAX_VERTEX_COUNT][MAX_VERTEX_COUNT];
    int vertexCount;
    int edgeCount;
    
public:
    /** 初始化 */
    GraphByAdjMat();
    
    /**
     @brief 打印图
     @discussion 按邻接矩阵打印图。需要对类T重载<<算符
     */
    void display();
    
    /**
     @brief 增加节点
     @discussion 增加节点。需要对类T重载=算符
     */
    bool addVertex(T vertex);
    
    /**
     @brief 增加边
     @discussion 在第i个节点和第j个节点直接增加边

     @param i 第i个节点，从0开始
     @param j 第j个节点，从0开始
     */
    bool addEdge(int i, int j, int weight);
};

template <typename T>
GraphByAdjMat<T>::GraphByAdjMat()
{
    for (int i = 0; i < this->MAX_VERTEX_COUNT; i++)
    {
        for (int j = 0; j < this->MAX_VERTEX_COUNT; j++)
            this->edges[i][j] = 0;
        this->edges[i][i] = this->INFINITY;
    }
    this->vertexCount = 0;
    this->edgeCount = 0;
}

template <typename T>
void GraphByAdjMat<T>::display()
{
    for (int i = 0; i < this->vertexCount; i++)
    {
        for (int j = 0; j < this->vertexCount; j++)
            std::cout << this->edges[i][j] << " ";
        std::cout << std::endl;
    }
    
    for (int i = 0; i < this->vertexCount; i++)
        std::cout << "节点" << i << ": " << this->vertices[i] << std::endl;
}

template <typename T>
bool GraphByAdjMat<T>::addVertex(T vertex)
{
    if (this->vertexCount == this->MAX_VERTEX_COUNT)
        return false;
    this->vertices[this->vertexCount] = vertex;
    this->vertexCount++;
    return true;
}

template <typename T>
bool GraphByAdjMat<T>::addEdge(int i, int j, int weight)
{
    if (i >= this->vertexCount || j >= this->vertexCount || i == j)
        return false;
    this->edges[i][j] = weight;
    this->edgeCount++;
    return true;
}


#endif /* GraphByAdjMat_hpp */
