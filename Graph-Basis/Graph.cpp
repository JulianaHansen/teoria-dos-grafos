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

bool Graph::isConnected()
{
    int numberOfNodes;
    int *nodeComponentList;
    int component = 0;
    this->createAuxNodeComponentArray(&numberOfNodes, &nodeComponentList);

    for (int i = 0; i < numberOfNodes; i++)
    {
        if (nodeComponentList[i] == -1)
        {
            component += 1;
            if (component != 1)
            {
                return false;
            }
            marksNodeComponent(i, component, &nodeComponentList);
        }
    }

    delete[] nodeComponentList;
    return true;
}

void Graph::marksNodeComponent(int idNode, int component, int **nodeComponentList)
{
    (*nodeComponentList)[idNode] = component;

    Edge *initialEdge = this->getNodeById(idNode)->getFirstEdge();
    while (initialEdge != nullptr)
    {
        int idAdjacentNode = initialEdge->getTargetId();
        if ((*nodeComponentList)[idAdjacentNode] == -1)
        {
            marksNodeComponent(idAdjacentNode, component, nodeComponentList);
        }
        initialEdge = initialEdge->getNextEdge();
    }
}

void Graph::createAuxNodeComponentArray(int *size, int **componentList)
{
    *componentList = new int[this->order];
    Node *nextNode = this->firstNode;
    int i = 0;
    while (nextNode != nullptr)
    {
        (*componentList)[i] = -1;
        nextNode = nextNode->getNextNode();
        i++;
    }
    *size = i;
}

void Graph::sortNodes(Node **nodeList, int size)
{
    float currentHeuristic = 0;
    float nextHeuristic = 0;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size - i - 1; j++)
        {
            currentHeuristic = nodeList[j]->getWeight();
            nextHeuristic = nodeList[j + 1]->getWeight();
            if (currentHeuristic > nextHeuristic)
            {
                Node *auxNode = nodeList[j];
                nodeList[j] = nodeList[j + 1];
                nodeList[j + 1] = auxNode;
            }
        }
    }
}

void Graph::greedy() {
 
}

void Graph::greedyAR(int seed) {
    std::srand(seed); //números aleatórios

    int totalNodes = this->getOrder();
    std::vector<int> nodeIds;

    // faz lista de IDs dos nós
    for (int i = 0; i < totalNodes; ++i) {
        nodeIds.push_back(i); 
    }

    // Cria um gerador aleatório
    std::default_random_engine generator(seed);
    // embaralha lista nós
    std::shuffle(nodeIds.begin(), nodeIds.end(), generator);

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
            partitions[partitionIndex].addNode(nodeIds[i], nodeValue);
        }
    }

    // Cálculo da soma dos gaps
    int totalGap = 0;
    for (const auto& partition : partitions) {
        totalGap += partition.getGap(); // Soma os gaps de cada partição
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
