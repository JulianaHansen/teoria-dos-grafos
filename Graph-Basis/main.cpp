#include "Graph.hpp"



int main(int argc, char* argv[])
{
    printf("Stop\n");

    std::ifstream input_file("instances_example/5nD_2.dat");

    if(!input_file){
         std::cerr << "Erro ao abrir o arquivo de instância." << std::endl;
         return 1;
    }

     Graph *graph = new Graph();

    size_t number_of_nodes;
    input_file >> number_of_nodes; // Lê o número de nós do arquivo de instância

    for (size_t i = 0; i < number_of_nodes; ++i) {
        size_t node_id1;
        size_t node_id2;  
        input_file >> node_id1;// Lê o no de saida
        std::cerr << "criando no" << node_id1 << std::endl;
         graph->add_node(node_id1); // cria o no
         input_file >> node_id2; // Lê o no alvo
         graph->add_node(node_id2); // cria o no
         float weight;
         input_file >> weight; // Lê o edge weight
         graph->add_edge(node_id1,node_id2,weight);
     }
     graph->print_graph();
    return 0;
}