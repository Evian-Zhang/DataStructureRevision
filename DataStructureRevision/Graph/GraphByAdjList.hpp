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
#include "../Queue/Queue.hpp"
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
        int adjVex;
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
    
    /** DFSTraverse的辅助函数 */
    void DFSTraverseFromNode(int vertexIndex, bool *visited, void (*visit)(T));
    
    /** BFSTraverse的辅助函数 */
    void BFSTraverseFromNode(int vertexIndex, bool *visited, void (*visit)(T));
    
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
    
    /** 深度优先遍历 */
    void DFSTraverse(void (*visit)(T));
    
    /** 广度优先遍历 */
    void BFSTraverse(void (*visit)(T));
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
            ArcNode *arc;
            while (node->arcs->get(arcIndex, arc))
            {
                verIndex = arc->adjVex;
                std::cout << " -> " << *(this->adjList[verIndex]);
                arcIndex++;
            }
            std::cout << std::endl;
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
                addedArc->adjVex = j;
                addedArc->weight = graph->edges[i][j];
                addedVertex->arcs->insertInTail(addedArc);
            }
        this->adjList[i] = addedVertex;
    }
}

template <typename T>
void GraphByAdjList<T>::DFSTraverseFromNode(int vertexIndex, bool *visited, void (*visit)(T))
{
    visit(this->adjList[vertexIndex]->value);
    visited[vertexIndex] = true;
    int arcIndex = 0;
    ArcNode *arc;
    while (this->adjList[vertexIndex]->arcs->get(arcIndex, arc))
    {
        if (!visited[arc->adjVex])
            this->DFSTraverseFromNode(arc->adjVex, visited, visit);
        arcIndex++;
    }
}

template <typename T>
void GraphByAdjList<T>::DFSTraverse(void (*visit)(T))
{
    bool visited[this->vertexCount];
    for (int i = 0; i < this->vertexCount; i++)
        visited[i] = false;
    for (int vertexIndex = 0; vertexIndex < this->vertexCount; vertexIndex++)
        if (!visited[vertexIndex])
            this->DFSTraverseFromNode(vertexIndex, visited, visit);
}

template <typename T>
void GraphByAdjList<T>::BFSTraverseFromNode(int vertexIndex, bool *visited, void (*visit)(T))
{
    Queue<int> *queue = new Queue<int>();
    int queueFront = vertexIndex;
    queue->enQueue(queueFront);
    while (!queue->isEmpty())
    {
        queue->deQueue(queueFront);
        if (visited[queueFront])
            continue;
        visit(this->adjList[queueFront]->value);
        visited[queueFront] = true;
        int arcIndex = 0;
        ArcNode *arc;
        while (this->adjList[queueFront]->arcs->get(arcIndex, arc))
        {
            queue->enQueue(arc->adjVex);
            arcIndex++;
        }
    }
    delete queue;
}

template <typename T>
void GraphByAdjList<T>::BFSTraverse(void (*visit)(T))
{
    bool visited[this->vertexCount];
    for (int i = 0; i < this->vertexCount; i++)
        visited[i] = false;
    for (int vertexIndex = 0; vertexIndex < this->vertexCount; vertexIndex++)
        if (!visited[vertexIndex])
            this->BFSTraverseFromNode(vertexIndex, visited, visit);
}

#endif /* GraphByAdjList_hpp */
