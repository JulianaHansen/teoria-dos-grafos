#include "Graph.hpp"
#include <limits>
const float INF = std::numeric_limits<float>::infinity();

Graph::Graph() : _number_of_nodes(0), _number_of_edges(0), _directed(false), _weighted_edges(false), _weighted_nodes(false), _first(nullptr), _last(nullptr) {
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
    // para verificar se já não existe um nó com esse id
    for(Node* currentNode = _first; currentNode != nullptr; currentNode = currentNode->_next_node){
        if(currentNode->_id == node_id){
            return;
        } // um ponteiro criado dentro de uma estrutura de repetição é automaticamente deletado após o fim da mesma
    }
    // Se chegou aqui, é porque o nó não existe ainda, então vamos criá-lo!
    Node* newNode = new Node;
    newNode->_number_of_edges = 0;
    newNode->_id = node_id;
    newNode->_weight = weight;
    newNode->_first_edge = nullptr;
    newNode->_next_node = nullptr;
    newNode->_previous_node = _last;

    // agora, vamos ver se esse é o primeiro nó criado ou se ele deve ser posicionado após o último nó criado
    if(_first == nullptr){
        _first = newNode;
        _last = newNode;
    } 
    else{
        _last->_next_node = newNode;
        newNode->_previous_node = _last;
        _last = newNode;
    }
    _number_of_nodes++;
}



void Graph::add_edge(size_t source_node_id, size_t target_node_id, float weight) {
    
    Node* no_saida = nullptr;
    //Aqui ele vai procurar se o no de onde sai a aresta existe
    for (Node* current = _first; current != nullptr; current = current->_next_node) {
        if (current->_id == source_node_id) {
            no_saida = current; //Se ele encontrar
            break;
        }
    }

    // Se o nó de origem não existe, ele manda uma mensagem
    if (!no_saida) {
         std::cerr <<"nao existe um no com esse id "<< source_node_id << "para saida"<< std::endl;
            return;
    }

    Node* no_entrada = nullptr;
    //Aqui ele vai procurar se o no de entrada existe
    for (Node* current = _first; current != nullptr; current = current->_next_node) {
        if (current->_id == target_node_id) {
            no_entrada = current;//Se ele encontrar
            break;
        }
    }
    // Se o nó de origem não existe, ele manda uma mensagem
    if (!no_entrada) {
        std::cerr <<"nao existe um no com esse id"<< target_node_id << "para entrada" << std::endl;
            return;
    }

    // Cria uma nova aresta e declara tudo
    Edge* new_edge = new Edge{no_saida->_first_edge, weight, target_node_id};
    no_saida->_first_edge = new_edge;
    no_saida->_number_of_edges++;

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
            std::cout << edge->_target_id << " [" << edge->_weight << "] ";
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
            output_file << edge->_target_id << edge->_weight;
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
Node* Graph::get_node(size_t id) {
    Node* current = _first;
    while (current) {
        if (current->_id == id) return current;
        current = current->_next_node;
    }
    return nullptr;
}

int Graph::get_radius(){
        
    floyd_warshall();
    
    int radius = std::numeric_limits<int>::max();
    
    for (size_t i = 0; i < _number_of_nodes; ++i) {
       
        int eccentricity = 0;
        for (size_t j = 0; j < _number_of_nodes; ++j) {
            if (i != j) {
                
                if (dist[i][j] == std::numeric_limits<float>::infinity()) {
                    eccentricity = std::numeric_limits<int>::max();
                    break;
                }
                eccentricity = std::max(eccentricity, static_cast<int>(dist[i][j]));
            }
        }
        
    
        radius = std::min(radius, eccentricity);
    }
    
 
    return (radius == std::numeric_limits<int>::max()) ? -1 : radius;
}

int Graph::get_diameter(){
    floyd_warshall();
    
    int diameter = 0;
    
    for (size_t i = 0; i < _number_of_nodes; ++i) {
        for (size_t j = 0; j < _number_of_nodes; ++j) {
            if (i != j) {
                if (dist[i][j] == std::numeric_limits<float>::infinity()) {
                    return -1;
                }
                diameter = std::max(diameter, static_cast<int>(dist[i][j]));
            }
        }
    }
    
    return diameter;
}

int Graph::get_center(){
    return 0;
}

int Graph::get_periphery(){
    return 0;
}

void Graph::dist_min_Djkstra(size_t node_id_1, size_t node_id_2) {
    std::unordered_map<size_t, float> distances;
    std::unordered_map<size_t, bool> visited;
    auto compare = [](std::pair<float, size_t> a, std::pair<float, size_t> b) { return a.first > b.first; };
    std::priority_queue<std::pair<float, size_t>, std::vector<std::pair<float, size_t>>, decltype(compare)> pq(compare);

    Node* startNode = get_node(node_id_1);
    if (!startNode) {
        std::cerr << "esse no de partida nao existe" << std::endl;
        return;
    }

    distances[node_id_1] = 0.0;
    pq.push({0.0, node_id_1});

    while (!pq.empty()) {
        size_t current_id = pq.top().second;
        pq.pop();
        if (visited[current_id]) continue;
        visited[current_id] = true;

        Node* current = get_node(current_id);
        for (Edge* edge = current->_first_edge; edge; edge = edge->_next_edge) {
            size_t neighbor_id = edge->_target_id;
            float new_distance = distances[current_id] + edge->_weight;

            if (distances.find(neighbor_id) == distances.end() || new_distance < distances[neighbor_id]) {
                distances[neighbor_id] = new_distance;
                pq.push({new_distance, neighbor_id});
            }
        }
    }

    if (distances.find(node_id_2) != distances.end()) {
        std::cout << "Distancia do no " << node_id_1 << " ate o no " << node_id_2 << " é " << distances[node_id_2] << std::endl;
    } else {
        std::cout << "nao ha caminho atre esses nos " << std::endl;
    }
}
void Graph::floyd_warshall() {
    std::unordered_map<size_t, size_t> node_to_index;
    std::unordered_map<size_t, size_t> index_to_node;
    size_t index = 0;

    //  garantindo que os ids dos nós sejam contíguos e comecem em 0
    for (Node* current = _first; current; current = current->_next_node) {
        node_to_index[current->_id] = index;
        index_to_node[index] = current->_id;
        index++;
    }

    // Inicializar as matrizes dist e next
    dist.assign(_number_of_nodes, std::vector<float>(_number_of_nodes, INF));// armazena a menor distância conhecida do nó i ao nó j
    next.assign(_number_of_nodes, std::vector<int>(_number_of_nodes, -1));// rastreia os próximos nós no caminho mínimo entre dois nós

    // Preenche as matrizes dist e next com base nos índices mapeados
    Node *current = _first;
    while (current) {
        size_t u = node_to_index[current->_id];
        dist[u][u] = 0;
        for (Edge *edge = current->_first_edge; edge; edge = edge->_next_edge) {
            size_t v = node_to_index[edge->_target_id];
            dist[u][v] = edge->_weight;
            next[u][v] = v;
        }
        current = current->_next_node;
    }

    // algoritmo Floyd-Warshall
    for (size_t k = 0; k < _number_of_nodes; ++k) {
        for (size_t i = 0; i < _number_of_nodes; ++i) {
            for (size_t j = 0; j < _number_of_nodes; ++j) {
                if (dist[i][k] < INF && dist[k][j] < INF) {
                    if (dist[i][j] > dist[i][k] + dist[k][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                        next[i][j] = next[i][k];
                    }
                }
            }
        }
    }


    std::cout << "menor distancia entre pares de nos:" << std::endl;
    for (size_t i = 0; i < _number_of_nodes; ++i) {
        for (size_t j = 0; j < _number_of_nodes; ++j) {
            if (dist[i][j] == INF) {
                std::cout << "INF ";
            } else {
                std::cout << dist[i][j] << " ";
            }
        }
        std::cout << std::endl;
    }
}

//Utiliza a matriz de predecessores gerada pela floyd para reconstruir o caminho min entre dois nós
std::vector<size_t> Graph::get_shortest_path(size_t node_id_1, size_t node_id_2) {
    std::unordered_map<size_t, size_t> node_to_index;
    std::unordered_map<size_t, size_t> index_to_node;
    size_t index = 0;

    for (Node* current = _first; current; current = current->_next_node) {
        node_to_index[current->_id] = index;
        index_to_node[index] = current->_id;
        index++;
    }

    size_t u = node_to_index[node_id_1];
    size_t v = node_to_index[node_id_2];
    std::vector<size_t> path;

    if (next[u][v] == -1) return path;

    while (u != v) {
        path.push_back(index_to_node[u]);
        u = next[u][v];
    }
    path.push_back(index_to_node[v]);

    return path;
}
