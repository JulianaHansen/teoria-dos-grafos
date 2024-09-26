#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED
#include "Edge.hpp"
#include <list>

using namespace std;

class Node
{
private:
    Edge *firstEdge;
    Edge *lastEdge;
    int id;
    float weight;
    Node *nextNode;

public:

    Node(int id);

    ~Node();

    Edge *getFirstEdge();
    Edge *getLastEdge();
    int getId() const;
    float getWeight();
    Node *getNextNode();

    void setNextNode(Node *node);
    void setWeight(float weight);

    void insertEdge(int sourceId, int targetId);
    int removeEdge(int id, bool directed, Node *targetNode);
    void removeAllEdges();

    Edge *getEdgeBetween(int targetId);
    bool hasEdgeBetween(int targetId);
};

#endif // NODE_H_INCLUDED