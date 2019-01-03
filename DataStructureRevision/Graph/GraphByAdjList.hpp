//
//  GraphByAdjList.hpp
//  DataStructureRevision
//
//  Created by Evian张 on 2019/1/1.
//  Copyright © 2019 Evian张. All rights reserved.
//

#ifndef GraphByAdjList_hpp
#define GraphByAdjList_hpp

#include <iostream>

#include "../LinkedList/BiLinkedList.hpp"
#include "GraphByAdjMat.hpp"

template <typename T>
class GraphByAdjList
{
    static const int MAX_VERTEX_COUNT = 128;
    static const int INFINITY = INT_MAX;
    
    class ArcNode
    {
    public:
        /** 该边链接的节点，从0开始 */
        int ajdVex;
        int weight;
    };
    
    class VNode
    {
        friend std::ostream& operator<<(std::ostream& output, const VNode& vertex)
        {
            output << vertex.value;
            return output;
        }
    public:
        T value;
        BiLinkedList<ArcNode*> *arcs;
    };
    
    VNode* adjList[MAX_VERTEX_COUNT];
    
    int vertexCount;
    int edgeCount;
    
public:
    /** 初始化 */
    GraphByAdjList();
    
    /** 析构函数 */
    ~GraphByAdjList();
    
    /**
     @brief 打印图
     @discussion 按邻接矩阵打印图。需要对类T重载<<算符
     */
    void display();
    
    /**
     从邻接矩阵中建立邻接表

     @param graph 以邻接表形式存储的图
     */
    void createFromAdjMat(GraphByAdjMat<T> *graph);
};

template <typename T>
GraphByAdjList<T>::GraphByAdjList()
{
    this->vertexCount = 0;
    this->edgeCount = 0;
}

template <typename T>
GraphByAdjList<T>::~GraphByAdjList()
{
    for (int i = 0; i < this->vertexCount; i++)
    {
        delete this->adjList[i]->arcs;
        delete this->adjList[i];
    }
}

template <typename T>
void GraphByAdjList<T>::display()
{
    if (this->vertexCount == 0)
        std::cout << "NULL";
    else
    {
        for (int i = 0; i < this->vertexCount; i++)
        {
            VNode *node = this->adjList[i];
            std::cout << node->value;
            int arcIndex = 0;
            int verIndex = 0;
            ArcNode *arc = new ArcNode();
            while (node->arcs->get(arcIndex, arc))
            {
                verIndex = arc->ajdVex;
                std::cout << " -> " << *(this->adjList[verIndex]);
                arcIndex++;
            }
            std::cout << std::endl;
            delete arc;
        }
    }
}

template <typename T>
void GraphByAdjList<T>::createFromAdjMat(GraphByAdjMat<T> *graph)
{
    for (int i = 0; i < this->vertexCount; i++)
    {
        delete this->adjList[i]->arcs;
        delete this->adjList[i];
    }
    for (int i = 0; i < this->MAX_VERTEX_COUNT; i++)
        this->adjList[i] = NULL;
    this->vertexCount = graph->vertexCount;
    this->edgeCount = graph->edgeCount;
    for (int i = 0; i < this->vertexCount; i++)
    {
        VNode* addedVertex = new VNode();
        addedVertex->value = graph->vertices[i];
        addedVertex->arcs = new BiLinkedList<ArcNode*>();
        for (int j = 0; j < this->vertexCount; j++)
            if (graph->edges[i][j] && j != i)
            {
                ArcNode *addedArc = new ArcNode();
                addedArc->ajdVex = j;
                addedArc->weight = graph->edges[i][j];
                addedVertex->arcs->insertInTail(addedArc);
            }
        this->adjList[i] = addedVertex;
    }
}

#endif /* GraphByAdjList_hpp */
