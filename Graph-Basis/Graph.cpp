#include "Graph.hpp"

using namespace std;

#include "Graph.hpp"
#include "Edge.hpp"
#include <math.h>
#include <cstdlib>
#include <algorithm>
#include <climits>
#include <cfloat>
#include <fstream>
#include <list>
#include <random> 
#include <algorithm>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif
#include <sstream>

using namespace std;

// Construtor
Graph::Graph(string filePath)
{
    this->order = 0;
    this->firstNode = nullptr;
    this->lastNode = nullptr;
    this->numberEdges = 0;

    ifstream file(filePath);
    if (!file.is_open()) {
        cerr << "Erro ao abrir o arquivo!" << endl;
        return;
    }

    string line;
    while (getline(file, line)) {

         if (line.find("param p :=") != string::npos) {
            istringstream iss(line);
            iss.ignore(11);
            iss >> this->p;
        } else if (line.find("set V :=") != string::npos) {

            while (getline(file, line) && line.find(";") == string::npos) {
                istringstream iss(line);
                int v;
                while (iss >> v) {
                    this->insertNode(v);
                }
            }

        } else if (line.find("param w :=") != string::npos) {
            while (getline(file, line) && line.find(";") == string::npos) {
                istringstream iss(line);
                int v, w;
                while (iss >> v >> w) {
                    Node* node = getNodeById(v);
                    if (node != nullptr){
                        node->setWeight(w);
                    }
                }
            }
        } else if (line.find("set E :=") != string::npos) {
            while (getline(file, line) && line.find(";") == string::npos) {
                istringstream iss(line);
                char ch;
                int s, t;
                while (iss >> ch >> s >> ch >> t >> ch) {
                    this->insertEdge(s, t);
                }
            }
        }
    }

    file.close();   
}

// Destrutor
Graph::~Graph(){}

int Graph::getP()
{
    return this->p;
}
int Graph::getOrder()
{
    return this->order;
}
int Graph::getNumberEdges()
{
    return this->numberEdges;
}
Node *Graph::getFirstNode()
{
    return this->firstNode;
}
Node *Graph::getLastNode()
{
    return this->lastNode;
}

Node *Graph::insertNode(int id)
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
    order++;
    return newNode;
}

Node *Graph::insertNode(int id, float weight)
{
    Node *newNode = this->insertNode(id);
    newNode->setWeight(weight);
    return newNode;
}

void Graph::insertEdge(int sourceId, int targetId, Node **sourceNode, Node **targetNode)
{
    if (sourceId == targetId)
        return;

    *sourceNode = getNodeById(sourceId);
    if (*sourceNode == nullptr)
       *sourceNode = insertNode(sourceId);
        else
            return;

    *targetNode = getNodeById(targetId);
    if (*targetNode == nullptr)
        *targetNode = insertNode(targetId);
        else
            return;
    int targetNodeId = (*targetNode)->getId();

    Edge *nextEdge = (*sourceNode)->getFirstEdge();
    bool alreadyExists = false;
    while (nextEdge != nullptr)
    {
        if (nextEdge->getTargetId() == targetNodeId)
            alreadyExists = true;
        nextEdge = nextEdge->getNextEdge();
    }
    if (!alreadyExists)
    {
        (*sourceNode)->insertEdge((*sourceNode)->getId(), targetNodeId);
        (*targetNode)->insertEdge(targetNodeId, (*sourceNode)->getId());
    }

    numberEdges++;
}

void Graph::insertEdge(int sourceId, int targetId)
{
    Node *sourceNode = nullptr;
    Node *targetNode = nullptr;
    this->insertEdge(sourceId, targetId, &sourceNode, &targetNode);
}

void Graph::insertEdge(Node *sourceNode, Node *targetNode)
{
    if (sourceNode != nullptr && targetNode != nullptr)
    {
        int sourceNodeId = sourceNode->getId();
        int targetNodeId = targetNode->getId();
        sourceNode->insertEdge(sourceNodeId, targetNodeId);
        targetNode->insertEdge(targetNodeId,sourceNodeId);
    }

    numberEdges++;
}

bool Graph::searchNode(int id)
{
    return this->getNodeById(id) != nullptr;
}

Node *Graph::getNodeById(int id)
{
    Node *nextNode = this->firstNode;
    while (nextNode != nullptr)
    {
        if (nextNode->getId() == id)
            return nextNode;

        nextNode = nextNode->getNextNode();
    }
    return nullptr;
}

bool Graph::depthFirstSearch(int initialId, int targetId)
{
    bool *visitedList = new bool[this->order];
    for (int i = 0; i < this->order; i++)
        visitedList[i] = false;
    return depthFirstSearchAux(this->getNodeById(initialId), targetId, visitedList);
}

bool Graph::depthFirstSearchAux(Node *currentNode, int targetId, bool visitedList[])
{
    int currentNodeId = currentNode->getId();
    if (currentNodeId == targetId)
        return true;
    if (visitedList[currentNodeId])
        return false;
    visitedList[currentNodeId] = true;

    for (Edge *e = currentNode->getFirstEdge(); e != nullptr; e = e->getNextEdge())
    {
        Node *nextNode = this->getNodeById(e->getTargetId());
        bool found = this->depthFirstSearchAux(nextNode, targetId, visitedList);
        if (found)
            return true;
    }
    return false;
}

void Graph::sortNodes(Node ** nodeList)
{

    int counter = 0;
    Node *node = firstNode;
    while (node != nullptr) {
        nodeList[counter] = node;
        node = node->getNextNode();
        counter++;
    }

    float current = 0;
    float next = 0;
    for (int i = 0; i < order; i++)
    {
        for (int j = 0; j < order - i - 1; j++)
        {
            current = nodeList[j]->getWeight();
            next = nodeList[j + 1]->getWeight();
            if (current > next)
            {
                Node *auxNode = nodeList[j];
                nodeList[j] = nodeList[j + 1];
                nodeList[j + 1] = auxNode;
            }
        }
    }
}

void Graph::greedy() {

    Partition **partitions = new Partition*[this->p];
    for (int i = 0; i < this->p; ++i) {
        partitions[i] = new Partition(); 
    }

    Node ** nodeList = new Node*[this->order]; 
    sortNodes(nodeList);

    for (int i = 0; i < order; ++i){
        int pos = (i/this->p);
        Node* node = nodeList[i];

        partitions[pos]->insertNode(node->getId(), node->getWeight());
    }

    int totalGaps = 0;
    for (int i = 0; i < this->p; ++i){
        cout << i << ":";
        partitions[i]->displayNodes();
        totalGaps += partitions[i]->getGap();
    }
    cout << "Result:" << totalGaps << "\n";
}

void Graph::greedyA(int seed) {
    srand(seed); //números aleatórios

    int totalNodes = this->getOrder();
    vector<int> nodeIds;

    // faz lista de IDs dos nós
    for (int i = 0; i < totalNodes; ++i) {
        nodeIds.push_back(i); 
    }

    // Cria um gerador aleatório
    default_random_engine generator(seed);
    // embaralha lista nós
    shuffle(nodeIds.begin(), nodeIds.end(), generator);

    // Inicializa as partições
    partitions.resize(p); //p é o num de partiçoes

    // faz as partiçoes
    for (int i = 0; i < totalNodes; ++i) {
        int partitionIndex = rand() % p; // Escolhe uma partição aleatoriamente

        // Obtém o nó pelo ID
        Node* node = this->getNodeById(nodeIds[i]); // Método que retorna o nó pelo ID
        if (node) {
            // Usa o método getWeight() para obter o valor associado ao nó
            float nodeValue = node->getWeight();

            // Adiciona o nó à partição
            partitions[partitionIndex].insertNode(nodeIds[i], nodeValue);
        }
    }

    int totalGap = 0;
    for (int i = 0; i < partitions.size(); i++){
        totalGap += partitions[i].getGap();
    }

    std::cout << "Soma total dos gaps: " << totalGap << std::endl;

    // exibir as partições
    for (int i = 0; i < p; ++i) {
        std::cout << "Partição " << i + 1 << ": ";
        partitions[i].displayNodes(); // Exibe os nós e valores mínimo e máximo
    }
}

void Graph::greedyAR(int seed) {
}
