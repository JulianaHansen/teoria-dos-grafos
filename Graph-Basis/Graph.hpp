#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED
#include <iostream>
#include "Node.hpp"
#include "Partition.hpp"

using namespace std;

class Graph
{
    // Atributos
private:
    int p;
    int order;
    int numberEdges;
    Node *firstNode;
    Node *lastNode;
    vector<Partition> partitions; // Armazenar as partições

public:
    // Construtor
    Graph(string filePath);

    // Destrutor
    ~Graph();

    // Getters
    int getP();
    int getOrder();

    int getNumberEdges();
    Node *getFirstNode();
    Node *getLastNode();

    Node *insertNode(int id);
    Node *insertNode(int id, float weight);
    void insertEdge(Node *sourceNode, Node *targetNode);

    bool searchNode(int id);
    Node *getNodeById(int id);
    bool depthFirstSearch(int initialId, int targetId);
    void sortNodes(Node** nodeList);
    int gulosoRandomizadoAdaptivo(float alfa, int interacoes);
    int guloso(float alfa);
    int gulosoRandomizadoAdaptativoReativo(float alfas[], int tam_alfa, int iteracoes, int pacote);
    


private:
    bool depthFirstSearchAux(Node *currentNode, int targetId, bool visitedList[]);
};

#endif // GRAPH_H_INCLUDED