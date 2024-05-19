#include "Graph.hpp"



int main(int argc, char* argv[])
{
    int valor;
    int direcionado; // vai salvar se o grafo é direcionado ou nao para usar essa inf no menu de funcionalidades
    std::ifstream input_file("instances_example/5nU_2.dat");

    while(direcionado != 0 && direcionado != 1)
    {
      std::cerr << "Ola! Voce quer trabalhar com um grafo Nao Direcionado(0)" << std::endl;
      std::cerr << "ou um grafo Direcionado(1)? " << std::endl; 
      std::cin >> direcionado;
    }
    
    if (direcionado == 0) //é um grafo nao direcionado entao sao os arquivos U
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
            graph->add_node(node_id1); // cria o no
            input_file >> node_id2; // Lê o no alvo
            graph->add_node(node_id2); // cria o no
            float weight;
            input_file >> weight; // Lê o edge weight
            graph->add_edge(node_id1,node_id2,weight);
     } 
    }
    std::cerr << "O seu grafo foi criado! Veja-o abaixo:" << std::endl;
    graph->print_graph();

    valor = 1;

    while (valor != 0 )
    {
        std::cerr << "FUNCIONALIDADES: O que voce quer ver?" << std::endl;
        std::cerr << "Selecione um dos valores abaixo:" << std::endl;
        std::cerr << "(1) Caminho min entre dois vertices (alg Djkstra)       (2) Caminho min entre dois vertices (alg Floyd)" << std::endl;
        std::cerr << "(3) Arvore Geradora Minima (alg Prim)                   (4) Arvore Geradora Minima (alg Kruskal)" << std::endl;
        std::cerr << "(5) Arvore em ordem de caminhamento em profundidade     (6) O raio, o diametro, o centro e a periferia do grafo" << std::endl;
        std::cerr << "(7) O conjunto de vertices de articulacao               ";

        if(direcionado == 1) // Essas duas funcio. so aparecem p/ grafos direcionados
        {
            std::cerr << "(8) Fecho transitivo direto de um vertice "<< std::endl << "(9) Fecho transitivo direto de um vertice " << std::endl;
        }

        std::cerr << "Clique no 0 para finalizar" << std::endl;
        std::cin >> valor;
        
        if(valor == 1) //Caminho min entre dois vertices (alg Djkstra)
        {
            int vertice1, vertice2; // a funcao usa dois parametros (vertice inicial e vertice final)

            std::cerr << "Qual o vertice inicial?" << std::endl;
            std::cin >> vertice1;
            std::cerr << "Qual o vertice final?" << std::endl;
            std::cin >> vertice2;

            //inserir a funcao aqui 
        }
        else if(valor == 2) //Caminho min entre dois vertices (alg Floyd)
        {
            int vertice1, vertice2; // a funcao usa dois parametros (vertice inicial e vertice final)

            std::cerr << "Qual o vertice inicial?" << std::endl;
            std::cin >> vertice1;
            std::cerr << "Qual o vertice final?" << std::endl;
            std::cin >> vertice2;

            //inserir a funcao aqui 
        }
        else if(valor == 3) //Arvore Geradora Minima (alg Prim) 
        {

        }
        else if(valor == 4) //Arvore Geradora Minima (alg Kruskal)
        {

        }
        else if(valor == 5) //Arvore em ordem de caminhamento em profundidade
        {

        }
        else if(valor == 6) //O raio, o diametro, o centro e a periferia do grafo
        {

        }
        else if(valor == 7) //Caminho min entre dois vertices (alg Djkstra)
        {

        }
        else if(valor == 8) //Caminho min entre dois vertices (alg Djkstra)
        {

        }
        else if(valor == 9) //Caminho min entre dois vertices (alg Djkstra)
        {

        }
    }
    
    
    return 0;
}