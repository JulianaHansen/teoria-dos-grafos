#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "Node.hpp"
#include "defines.hpp"
#include <string>
#include <unordered_set>

class Graph
{
public:
    /*Assinatura dos métodos básicos para o funcionamento da classe*/

    Graph(std::ifstream& instance);
    Graph();
    ~Graph();

    void remove_node(size_t node_id);
    void remove_edge(size_t node_id_1, size_t node_id_2);
    void add_node(size_t node_id, float weight = 0);
    void add_edge(size_t node_id_1, size_t node_id_2, float weight = 0);
    void print_graph(std::ofstream& output_file);
    void print_graph();
    void dist_min_Djkstra(size_t node_id_1, size_t node_id_2);
    Node* get_node(size_t id);
    int conected(size_t node_id_1, size_t node_id_2);
    void floyd_warshall();
    std::vector<size_t> get_shortest_path(size_t node_id_1, size_t node_id_2);
    int get_radius();
    int get_diameter();
    std::vector<size_t> get_center();
    std::vector<size_t> get_periphery();
    std::vector<size_t> direct_closure(size_t node_id);
    std::vector<size_t> indirect_closure(size_t node_id);
    std::string prim(std::vector<size_t> subgraph);
    std::string kruskal(std::vector<size_t>subgraph);
    void depth_first_search(size_t start_node);
    void find_articulation_points();
    void dfs(size_t u, std::unordered_set<size_t>& articulation_points, std::vector<size_t>& disc, std::vector<size_t>& low, std::vector<size_t>& parent, size_t& time, size_t root);
    
private:
    size_t _number_of_nodes;
    size_t _number_of_edges;
    bool   _directed;
    bool   _weighted_edges;
    bool   _weighted_nodes;
    Node  *_first;
    Node  *_last;
    std::vector<std::vector<float>> dist;
    std::vector<std::vector<int>> next;
};

#endif  //GRAPH_HPP
