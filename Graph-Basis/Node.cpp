#include "Node.hpp"
#include "Edge.hpp"
#include <iostream>
#include <cfloat>
#include <climits>
using namespace std;

Node::Node(int id)
{
    this->id = id;
    this->weight = 0;
    this->firstEdge = nullptr;
    this->lastEdge = nullptr;
    this->nextNode = nullptr;
};

Node::~Node()
{
    Edge *nextEdge = this->firstEdge;

    while (nextEdge != nullptr)
    {
        Edge *auxEdge = nextEdge->getNextEdge();
        delete nextEdge;
        nextEdge = auxEdge;
    }

    this->id = INT_MIN;
    this->weight = 0;
    this->firstEdge = nullptr;
    this->lastEdge = nullptr;
    this->nextNode = nullptr;
};

// Getters
Edge *Node::getFirstEdge()
{
    return this->firstEdge;
}
Edge *Node::getLastEdge()
{
    return this->lastEdge;
}
int Node::getId() const
{
    return this->id;
}
float Node::getWeight()
{
    return this->weight;
}
Node *Node::getNextNode()
{
    return this->nextNode;
}

void Node::setNextNode(Node *nextNode)
{
    this->nextNode = nextNode;
}
void Node::setWeight(float weight)
{
    this->weight = weight;
}


void Node::insertEdge(int sourceId, int targetId)
{
    if (this->firstEdge != nullptr)
    {
        Edge *edge = new Edge(sourceId, targetId);
        this->lastEdge->setNextEdge(edge);
        this->lastEdge = edge;
    }
    else
    {
        this->firstEdge = new Edge(sourceId, targetId);
        this->lastEdge = this->firstEdge;
    }
}

void Node::removeAllEdges()
{
    if (this->firstEdge != nullptr)
    {
        Edge *next = nullptr;
        Edge *aux = this->firstEdge;
        while (aux != nullptr)
        {
            next = aux->getNextEdge();
            delete aux;
        }
    }
    this->firstEdge = this->lastEdge = nullptr;
}

int Node::removeEdge(int id, bool directed, Node *targetNode)
{
    if (this->hasEdgeBetween(id))
    {
        Edge *aux = this->firstEdge;
        Edge *previous = nullptr;

        while (aux->getTargetId() != id)
        {
            previous = aux;
            aux = aux->getNextEdge();
        }

        if (previous != nullptr)
            previous->setNextEdge(aux->getNextEdge());
        else
            this->firstEdge = aux->getNextEdge();

        if (aux == this->lastEdge)
            this->lastEdge = previous;

        if (aux->getNextEdge() == this->lastEdge)
            this->lastEdge = aux->getNextEdge();

        delete aux;

        return 1;
    }
    return 0;
}

Edge *Node::getEdgeBetween(int targetId)
{
    if (this == nullptr)
        return nullptr;
    else
        for (Edge *auxEdge = this->firstEdge; auxEdge != nullptr; auxEdge = auxEdge->getNextEdge())
        {
            if (auxEdge->getTargetId() == targetId)
                return auxEdge;
        }
    return nullptr;
}

bool Node::hasEdgeBetween(int targetId)
{
    if (this == nullptr)
        return false;
    else
        return this->getEdgeBetween(targetId) != nullptr;
}