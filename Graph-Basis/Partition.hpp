#include "Node.hpp"
#include <vector>
#include <algorithm>
#include <iostream>

class Partition {
private:
    Node *firstNode;
    Node *lastNode; 
    int numberOfNodes;
    int minValue;   
    int maxValue;  

public:
    
    Partition();

    ~Partition();

    Node *insertNode(int id, float weight);

    int getGap();
    int getNumberOfNodes();

    void displayNodes() const;
};