#include "Graph.hpp"



int main(int argc, char* argv[])
{
    int valor;
    std::ifstream input_file("instances_example/5nU_2.dat");

    while(valor != 0 && valor != 1)
    {
      std::cerr << "Ola! Voce quer trabalhar com um grafo Nao Direcionado(0)" << std::endl;
      std::cerr << "ou um grafo Direcionado(1)? " << std::endl; 
      std::cin >> valor;
    }
    
    if (valor == 0) //é um grafo nao direcionado entao sao os arquivos U
    {
        std::cerr << "Voce quer trabalhar com um grafo Nao Direcionado com quantos nos? 5, 15, 50 ou 100?" << std::endl;
        std::cin >> valor;

        if(valor == 5){
            input_file.close(); 
            input_file.open("instances_example/5nU_2.dat");
        }
        if(valor == 15){
            input_file.close(); 
            input_file.open("instances_example/15nU_2.dat");
        }
        if(valor == 50){
            input_file.close(); 
            input_file.open("instances_example/50nU_2.dat");
        }
        if(valor == 100){
            input_file.close(); 
            input_file.open("instances_example/100nU_2.dat");
        }
    }
    else //é um grafo direcionado entao sao os arquivos D
    {
        std::cerr << "Voce quer trabalhar com um grafo Direcionado com quantos nos? 5, 15, 50 ou 100?" << std::endl;
        std::cin >> valor;

        if(valor == 5){
            input_file.close(); 
            input_file.open("instances_example/5nD_2.dat");
        }
        if(valor == 15){
            input_file.close(); 
            input_file.open("instances_example/15nD_2.dat");
        }
        if(valor == 50){
            input_file.close(); 
            input_file.open("instances_example/50nD_2.dat");
        }
        if(valor == 100){
            input_file.close(); 
            input_file.open("instances_example/100nD_2.dat");
        }
    }
    
    
    if(!input_file){
         std::cerr << "Erro ao abrir o arquivo de instância." << std::endl;
         return 1;
    }

     Graph *graph = new Graph();

    size_t number_of_nodes;
    input_file >> number_of_nodes; // Lê o número de nós do arquivo de instância

    std::cerr << "Voce quer trabalhar com um grafo com Arestas Nao Ponderadas(0) ou Ponderadas (1)?" << std::endl;
    std::cin >> valor;

    if(valor == 0){
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
            graph->add_edge(node_id1,node_id2,0);
     } 
    }

    else{
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
    }
    graph->print_graph();
    return 0;
}