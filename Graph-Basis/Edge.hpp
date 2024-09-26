#ifndef EDGE_H_INCLUDED
#define EDGE_H_INCLUDED

using namespace std;

class Edge
{
private:
    int sourceId;
    int targetId;
    Edge *nextEdge;


public:
    Edge(int sourceId, int targetId);

    ~Edge();

    int getSourceId();
    int getTargetId();
    Edge *getNextEdge();

    void setNextEdge(Edge *edge);
};

#endif // EDGE_H_INCLUDED