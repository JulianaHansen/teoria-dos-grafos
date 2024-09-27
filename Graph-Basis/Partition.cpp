#include "Partition.hpp"
#include <iostream>
#include <climits>

using namespace std;

Partition::Partition()
{
    this->firstNode = nullptr;
    this->lastNode = nullptr;
    this->numberOfNodes = 0;
    this->minValue = 0;
    this->maxValue = 0;
}

Partition::~Partition()
{
    this->firstNode = nullptr;
    this->lastNode = nullptr;
}

Node *Partition::insertNode(int id, float weight)
{
    Node *newNode = new Node(id);
    if (lastNode == nullptr)
    {
        firstNode = newNode;
        lastNode = newNode;
    }
    else
    {
        lastNode->setNextNode(newNode);
        lastNode = newNode;
    }
    newNode->setWeight(weight);

    if (weight > maxValue || maxValue == 0){
        maxValue = weight;
    }

    if (weight < minValue || minValue == 0) {
        minValue = weight;
    }

    numberOfNodes++;
    return newNode;
}

int Partition::getGap()
{
    return this->maxValue - this->minValue;
}

void Partition::displayNodes() const {
    cout << "Nós na partição: ";
    Node* node = firstNode;
    while (node != nullptr){
        cout << node->getId() << " ";
        node = node->getNextNode();
    }
    cout << "\nMínimo: " << minValue << ", Máximo: " << maxValue << std::endl;
}
