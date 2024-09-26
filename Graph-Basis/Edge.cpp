#include "Edge.hpp"
#include <iostream>
#include <climits>

using namespace std;

Edge::Edge(int sourceId, int targetId)
{
    this->sourceId = sourceId;
    this->targetId = targetId;
    this->nextEdge = nullptr;
}

Edge::~Edge()
{
    this->sourceId = INT_MIN;
    this->targetId = INT_MIN;
    this->nextEdge = nullptr;
}

int Edge::getSourceId() { return this->sourceId; }
int Edge::getTargetId() { return this->targetId; }
Edge *Edge::getNextEdge() { return this->nextEdge; }

void Edge::setNextEdge(Edge *edge) { this->nextEdge = edge; }
