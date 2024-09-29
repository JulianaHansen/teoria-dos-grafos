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

struct Candidato
{
    int p;
    int source_id;
    int target_id;
    int aumento_gap;

    friend bool operator<(Candidato c1, Candidato c2){
        return c1.aumento_gap < c2.aumento_gap;
    }

    friend bool operator>(Candidato c1, Candidato c2){
        return c1.aumento_gap > c2.aumento_gap;
    }

    friend bool operator==(Candidato c1, Candidato c2){
        return c1.target_id == c2.target_id;
    }

};

typedef struct{
    vector<int> vertices_ids;
    int maior;
    int menor;
}Solucao;

struct AuxAresta{
    int source;
    int target;
    int gap;

    friend bool operator<(AuxAresta a1, AuxAresta a2){
        return a1.gap < a2.gap;
    }

    friend bool operator>(AuxAresta a1, AuxAresta a2){
        return a1.gap > a2.gap;
    }
};

bool checkDisponivel(vector<int> v, int x, int y){
    int achado =0;
    for(int i = 0; i< v.size(); i++){
        if(v[i] == x || v[i] == y){
            achado++;
        }
        if(achado == 2){
            return true;
        }
    }
    return false;
}

void removePorValor(vector<int> &v, int value){
    int i;
    for(i=0; i<v.size();i++){
        if(v[i] == value){
            break;
        }
    }
    v.erase(v.begin() + 1);
}

void init_genrand(unsigned long s)
{   
    int N = 624;
    unsigned long mt[N];
    int mti = N + 1;	
	mt[0] = s & 0xffffffffUL;
	for (mti = 1; mti < N; mti++)
	{
		mt[mti] = (1812433253UL * (mt[mti - 1] ^ (mt[mti - 1] >> 30)) + mti);
		/* See Knuth TAOCP Vol2. 3rd Ed. P.106 for multiplier. */
		/* In the previous versions, MSBs of the seed affect   */
		/* only MSBs of the array mt[].                        */
		/* 2002/01/09 modified by Makoto Matsumoto             */
		mt[mti] &= 0xffffffffUL;
		/* for >32 bit machines */
	}
}

unsigned int intRandom(const unsigned int maxValue)
{
	#ifdef MTWISTER
		return ((double)genrand_real2()) * ((double)maxValue);
	#else
		static unsigned int res;
		static unsigned int rgen;
		static double factor;
		rgen = rand();
		factor = ((double)rgen / (double)INT_MAX);

		res = (unsigned int)(maxValue * factor);
		if (res == maxValue)
			res--;
		return res;
	#endif
}

int Graph::guloso(float alfa){
    
    vector<int> disponivel;
    for(int i=1; i<= order; i++){
        disponivel.push_back(i);
    }

    Solucao solucao[p];

    list<Candidato> candidatos;

    list<AuxAresta> todas_arestas;

    Node* node = firstNode;

    while(node != nullptr){
        Node* n = node->getNextNode();
        Edge* edge = node->getFirstEdge();

        while(edge != nullptr){
            Edge *e = edge->getNextEdge();
            AuxAresta aux;
            aux.source = n->getId();
            aux.target = e->getTargetId();
            aux.gap =  abs(n->getWeight() - getNodeById(e->getTargetId())->getWeight());
            todas_arestas.push_back(aux);
            edge = edge->getNextEdge();
        }
        node = node->getNextNode();
    }
    todas_arestas.sort();

    int adicionado = 0;

    list<AuxAresta>::iterator it;

    for(it= todas_arestas.begin(); it != todas_arestas.end(); ++it){
        if(adicionado < p){
            if(checkDisponivel(disponivel, it->source, it->target)){
                solucao[adicionado].vertices_ids.push_back(it->source);
                solucao[adicionado].vertices_ids.push_back(it->target);
                if(getNodeById(it->source)->getWeight() > getNodeById(it->target)->getWeight()){
                    solucao[adicionado].maior = getNodeById(it->source)->getWeight();
                    solucao[adicionado].menor = getNodeById(it->target)->getWeight();
                }else{
                    solucao[adicionado].menor = getNodeById(it->source)->getWeight();
                    solucao[adicionado].maior = getNodeById(it->target)->getWeight();
                }
                removePorValor(disponivel, it->source);
                removePorValor(disponivel, it->target);
                adicionado++;
            }
        }
    }

    for(int i =0; i< p; i++){
        for(int j = 0; j< solucao[i].vertices_ids.size(); j++){
            int atual_node_id = solucao[i].vertices_ids[j];
            Edge *aresta = getNodeById(atual_node_id)->getFirstEdge();
            while(aresta != nullptr){
                Edge *e = aresta->getNextEdge();

                bool id_disponivel = false;
                for(int i = 0; i< disponivel.size(); i++){
                    if(disponivel[i] == e->getTargetId()){
                        id_disponivel = true;
                    }
                }

                if(id_disponivel){
                    Candidato c;
                    c.p = i;
                    c.source_id = atual_node_id;
                    c.target_id = e->getTargetId();

                    int peso = getNodeById(e->getTargetId())->getWeight();
                    int menor_peso = solucao[i].menor;
                    int maior_peso = solucao[i].maior;

                    if(peso < menor_peso){
                        c.aumento_gap = abs(peso- menor_peso);
                    }else if(peso > maior_peso){
                        c.aumento_gap = abs(peso - maior_peso);
                    }else{
                        c.aumento_gap = 0;
                    }

                    candidatos.push_back(c);

                }
                aresta = aresta->getNextEdge();
            }
        }
    }

    int n = 1;

    while(disponivel.size() > 0){
        candidatos.sort();

        int candidatos_index;

        if(alfa != 0){
            init_genrand(time(0));
            int size_possibilidades = candidatos.size() * alfa;
            candidatos_index = intRandom(size_possibilidades);
        }else{
            candidatos_index = 0;
        }

        int node_escolhido;
        int p_escolhido;

        if(alfa!= 0){
            list<Candidato>::iterator it;
            int n =0;
            for(it = candidatos.begin(); it!= candidatos.end(); ++it){
                if(n == candidatos_index){
                    node_escolhido = it->target_id;
                    p_escolhido = it->p;
                    break;
                }
                n++;
            }
        }
        else{
            node_escolhido = candidatos.front().target_id;
            p_escolhido = candidatos.front().p;
        }

        solucao[p_escolhido].vertices_ids.push_back(node_escolhido);
        if(getNodeById(node_escolhido)->getWeight() > solucao[p_escolhido].maior){
            solucao[p_escolhido].maior = getNodeById(node_escolhido)->getWeight();
        }else if(getNodeById(node_escolhido)->getWeight() < solucao[p_escolhido].menor){
            solucao[p_escolhido].menor = getNodeById(node_escolhido)->getWeight();
        }

        removePorValor(disponivel, node_escolhido);

        Candidato aux;
        aux.target_id = node_escolhido;
        candidatos.remove(aux);

        Edge* aresta = getNodeById(node_escolhido)->getFirstEdge();
        while(aresta != nullptr){
            Edge* e = aresta->getNextEdge();

            bool id_disponivel = false;
            for(int i =0; i< disponivel.size(); i++){
                if(disponivel[i] == e->getTargetId()){
                    id_disponivel = true;
                }
            }

            if(id_disponivel){
                Candidato c;
                c.p = p_escolhido;
                c.source_id = node_escolhido;
                c.target_id = e->getTargetId();

                int peso = getNodeById(e->getTargetId())->getWeight();
                int menor_peso = solucao[p_escolhido].menor;
                int maior_peso = solucao[p_escolhido].maior;

                if(peso < menor_peso){
                    c.aumento_gap = abs(peso - menor_peso);
                }else if(peso > maior_peso){
                    c.aumento_gap = abs(peso - maior_peso);
                }else{
                    c.aumento_gap = 0;
                }
                candidatos.push_back(c);

            }

        }
        n++;
    }

    int custo = 0;
    for(int i=0; i< p;i++){
        custo += solucao[i].maior - solucao[i].menor;
    }

    return custo;

}