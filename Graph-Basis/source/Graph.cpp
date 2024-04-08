#include "../include/Graph.hpp"

Graph::Graph(std::ifstream& instance)
{
    this->_number_of_nodes = 0;
    this->_number_of_edges = 0;
    this->_first = nullptr;
    this->_last = nullptr;
}

Graph::Graph()
{
}

Graph::~Graph()
{
}

void Graph::remove_node(size_t node_position)
{
    Node *node = this->_first;

    while (node != nullptr)
    {
        if (node->_id == node_position)
        {
            if (node == this->_first)
            {
                this->_first = node->_next_node;
                this->_first->_previous_node = nullptr;
            }
            else if (node == this->_last)
            {
                this->_last = node->_previous_node;
                this->_last->_next_node = nullptr;
            }
            else
            {
                Node *previous_node = node->_previous_node;
                Node *next_node = node->_next_node;
                previous_node->_next_node = next_node;
                next_node->_previous_node = previous_node;
            }

            //deletar as arestas ligadas nesse nó:
            Node *nodeCompared = this->_first;
            while (nodeCompared != nullptr)
            {
                if (conected(nodeCompared->_id, node_position) == 1)
                {
                    remove_edge(nodeCompared->_id, node_position);
                }

                nodeCompared = nodeCompared->_next_node;
            }

            delete node;
            this->_number_of_nodes--;
            return;
        }

        node = node->_next_node;
    }
}

void Graph::remove_edge(size_t node_position_1, size_t node_position_2)
{
    Node *node1 = this->_first;
    Node *node2 = this->_first;

    while (node1 != nullptr)
    {
        if (node1->_id == node_position_1)
        {
            break;
        }
        node1 = node1->_next_node;
    }

    while (node2 != nullptr)
    {
        if (node2->_id == node_position_2)
        {
            break;
        }
        node2 = node2->_next_node;
    }

    Edge *edge = node1->_first_edge;
    while (&edge->_target_id != nullptr)
    {
        if (edge->_target_id == node2->_id)
        {
            break;
        }
        edge = edge->_next_edge;
    }

    if (edge == node1->_first_edge)
    {
        node1->_first_edge = edge->_next_edge;
    }
    else
    {
        Edge *aux = node1->_first_edge;
        while (aux->_next_edge != edge)
        {
            aux = aux->_next_edge;
        }
        aux->_next_edge = edge->_next_edge;
    }

    delete edge;
    node1->_number_of_edges = node1->_number_of_edges - 1;
    node2->_number_of_edges = node2->_number_of_edges - 1;
    
}

void Graph::add_node(size_t node_id, float weight)
{
    Node *newNode = new Node;
    newNode->_id = node_id;
    newNode->_weight = weight;

    if (this->_first == nullptr)
    {
        this->_first = newNode;
        this->_last = newNode;
        newNode->_next_node = nullptr;
    }
    else
    {
        this->_last->_next_node = newNode;
        newNode->_next_node = nullptr;
        newNode->_previous_node = this->_last;
        this->_last = newNode;
    }
    this->_number_of_nodes++;
}

void Graph::add_edge(size_t node_id_1, size_t node_id_2, float weight)
{
    Node *node1 = this->_first;
    Node *node2 = this->_first;

    while (node1 != nullptr)
    {
        if (node1->_id == node_id_1)
        {
            break;
        }
        node1 = node1->_next_node;
    }

    while (node2 != nullptr)
    {
        if (node2->_id == node_id_2)
        {
            break;
        }
        node2 = node2->_next_node;
    }

    Edge *newEdge = new Edge;
    newEdge->_next_edge = node1->_first_edge;
    node1->_first_edge = newEdge;
    node1->_number_of_edges = node1->_number_of_edges + 1;
    node2->_number_of_edges = node2->_number_of_edges + 1;
    newEdge->_target_id = node2->_id;
    newEdge->_weight = weight;
}

void Graph::print_graph()
{
    Node *node = this->_first;
    while (node != nullptr)
    {
        std::cout << node->_id << " -- ";
        Edge *edge = node->_first_edge;
        while (edge != nullptr)
        {
            std::cout << edge->_target_id << " [label=\"" << edge->_weight << "\"] ";
            edge = edge->_next_edge;
        }
        std::cout << std::endl;
        node = node->_next_node;
    }
}

void Graph::print_graph(std::ofstream& output_file)
{
    Node *node = this->_first;
    while (node != nullptr)
    {
        output_file << node->_id << " -- ";
        Edge *edge = node->_first_edge;
        while (edge != nullptr)
        {
            output_file << edge->_target_id << " [label=\"" << edge->_weight << "\"] ";
            edge = edge->_next_edge;
        }
        output_file << std::endl;
        node = node->_next_node;
    }
    output_file.close();
}

int Graph::conected(size_t node_id_1, size_t node_id_2)
{
    Node *node1 = this->_first;
    Node *node2 = this->_first;

    while (node1 != nullptr)
    {
        if (node1->_id == node_id_1)
        {
            break;
        }
        node1 = node1->_next_node;
    }

    while (node2 != nullptr)
    {
        if (node2->_id == node_id_2)
        {
            break;
        }
        node2 = node2->_next_node;
    }

    Edge *edge = node1->_first_edge;
    while (edge != nullptr)
    {
        if (edge->_target_id == node2->_id)
        {
            return 1;
        }
        edge = edge->_next_edge;
    }
    
    return 0;
}