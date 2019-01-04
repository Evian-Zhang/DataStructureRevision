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

#include "../LinkedList/BiLinkedList.hpp"
#include "../Stack/Stack.hpp"

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
    
    /** topologicalSort的辅助函数 */
    void findInDegree(int *indegree);
    
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
    
    /**
     Prim 算法计算最小生成树
     
     @param initialVertexIndex 初始顶点的位置
     @return 最小生成树的权重和
     */
    int Prim(int initialVertexIndex);
    
    /**
     拓扑排序
     
     @return 若存在回路则返回false, 否则返回true
     */
    bool topologicalSort();
    
    /** Dijkstra 算法计算最短路径 */
    BiLinkedList<T>** Dijkstra(int initiulaVertexIndex);
};

template <typename T>
GraphByAdjMat<T>::GraphByAdjMat()
{
    for (int i = 0; i < this->MAX_VERTEX_COUNT; i++)
    {
        for (int j = 0; j < this->MAX_VERTEX_COUNT; j++)
            this->edges[i][j] = 0;
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

template <typename T>
int GraphByAdjMat<T>::Prim(int initialVertexIndex)
{
    int lowcost[this->vertexCount], closest[this->vertexCount], leastWeight;
    leastWeight = 0;
    
    for (int tmpVertexIndex = 0; tmpVertexIndex < this->vertexCount; tmpVertexIndex++)
    {
        closest[tmpVertexIndex] = initialVertexIndex;
        lowcost[tmpVertexIndex] = this->edges[initialVertexIndex][tmpVertexIndex];
    }
    
    for (int vertexIndex = 0; vertexIndex < this->vertexCount - 1; vertexIndex++)
    {
        int connectedVertexIndex;
        int min = this->INFINITY;
        for (int tmpVertexIndex = 0; tmpVertexIndex < this->vertexCount; tmpVertexIndex++)
        {
            if (lowcost[tmpVertexIndex] != 0 && lowcost[tmpVertexIndex] < min)
            {
                min = lowcost[tmpVertexIndex];
                connectedVertexIndex = tmpVertexIndex;
            }
        }
        
        lowcost[connectedVertexIndex] = 0;
        leastWeight += min;
        
        for (int tmpVertexIndex = 0; tmpVertexIndex < this->vertexCount; tmpVertexIndex++)
        {
            if (this->edges[connectedVertexIndex][tmpVertexIndex] != 0 && this->edges[connectedVertexIndex][tmpVertexIndex] < lowcost[tmpVertexIndex])
            {
                lowcost[tmpVertexIndex] = this->edges[connectedVertexIndex][tmpVertexIndex];
                closest[tmpVertexIndex] = connectedVertexIndex;
            }
        }
    }
    
    return leastWeight;
}

template <typename T>
void GraphByAdjMat<T>::findInDegree(int *indegree)
{
    for (int vertexIndex = 0; vertexIndex < this->vertexCount; vertexIndex++)
    {
        indegree[vertexIndex] = 0;
        for (int connectedIndex = 0; connectedIndex < this->vertexCount; connectedIndex++)
            if (this->edges[connectedIndex][vertexIndex])
                indegree[vertexIndex]++;
    }
}

template <typename T>
bool GraphByAdjMat<T>::topologicalSort()
{
    int indegree[this->vertexCount];
    this->findInDegree(indegree);
    Stack<int> *stack = new Stack<int>();
    for (int i = 0; i < this->vertexCount; i++)
        if (!indegree[i])
            stack->push(i);
    int sortedCount = 0;
    while (!stack->isEmpty())
    {
        int vertexIndex;
        stack->pop(vertexIndex);
        sortedCount++;
        for (int connectedIndex = 0; connectedIndex < this->vertexCount; connectedIndex++)
            if (this->edges[vertexIndex][connectedIndex] && connectedIndex != vertexIndex)
            {
                indegree[connectedIndex]--;
                if (!indegree[connectedIndex])
                    stack->push(connectedIndex);
            }
    }
    
    delete stack;
    if (sortedCount < this->vertexCount)
        return false;
    return true;
}

template <typename T>
BiLinkedList<T>** GraphByAdjMat<T>::Dijkstra(int initialVertexIndex)
{
    int dist[this->vertexCount];
    BiLinkedList<T>** path = new BiLinkedList<T>*[this->vertexCount];
    int s[this->vertexCount];
    bool visited[this->vertexCount];
    
    for (int vertexIndex = 0; vertexIndex < this->vertexCount; vertexIndex++)
    {
        visited[vertexIndex] = false;
        dist[vertexIndex] = this->edges[initialVertexIndex][vertexIndex];
        path[vertexIndex] = new BiLinkedList<T>();
        if (dist[vertexIndex] != 0)
        {
            path[vertexIndex]->insertInTail(this->vertices[initialVertexIndex]);
            path[vertexIndex]->insertInTail(this->vertices[vertexIndex]);
        }
    }
    s[0] = initialVertexIndex;
    visited[initialVertexIndex] = true;
    int num = 1;
    while (num < this->vertexCount)
    {
        int smallestVertexIndex = 0, min = this->INFINITY;
        for (int vertexIndex = 0; vertexIndex < this->vertexCount; vertexIndex++)
        {
            if (!visited[vertexIndex] && dist[vertexIndex] < min && dist[vertexIndex] != 0)
            {
                smallestVertexIndex = vertexIndex;
                min = dist[vertexIndex];
            }
        }
        
        s[num++] = smallestVertexIndex;
        visited[smallestVertexIndex] = true;
        
        for (int vertexIndex = 0; vertexIndex < this->vertexCount; vertexIndex++)
        {
            if (!visited[vertexIndex] && dist[vertexIndex] > dist[smallestVertexIndex] + this->edges[smallestVertexIndex][vertexIndex])
            {
                dist[vertexIndex] = dist[smallestVertexIndex] + this->edges[smallestVertexIndex][vertexIndex];
                path[vertexIndex]->insertInTail(this->vertices[vertexIndex]);
            }
        }
    }
    return path;
}

#endif /* GraphByAdjMat_hpp */
