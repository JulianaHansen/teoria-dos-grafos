#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <tuple>
#include <string>
#include <utility>
#include <cmath> 

// Estrutura para armazenar subgrafos
struct Subgraph {
        std::vector<int> vertices;
        int pesoTotal = 0;
        std::vector<std::pair<int, int>> arestas; // Adicionado para guardar as arestas do subgrafo
    };

class Graph {
public:
    Graph(); // Construtor padrão

    // Função para ler o arquivo de entrada
    int lerArquivo(const std::string& nomeArquivo);

    // Função que implementa o algoritmo guloso para o MGGPP
    void algoritmoGulosoBalanceadoMGGPP();

    int calcularSomaDosGaps(const std::vector<Subgraph>& subgrafos);

    int calcularGap(const std::vector<Subgraph>& subgrafos);

    int escolherSubgrafoMinimoGap(const std::vector<Subgraph>& subgrafos, int v);

    // Variáveis públicas para armazenar os dados do grafo
    int p; // número de subgrafos
    std::vector<int> vertices; // Lista de vértices
    std::unordered_map<int, int> pesosVertices; // Mapeamento de vértices para seus pesos
    std::vector<std::pair<int, int>> arestas; // Lista de arestas
    std::vector<std::pair<int, int>> D0; // Conjunto de arestas específicas (se necessário)
    std::vector<std::tuple<int, int, int>> Y0; // Outra estrutura de dados para restrições específicas (se necessário)
   

private:
    // Função auxiliar para verificar se um conjunto de vértices está conectado
    bool isConexo(const std::vector<std::pair<int, int>>& arestas, const std::vector<int>& vertices);
    bool isGrafoConexo(const std::vector<std::pair<int, int>>& arestas, const std::vector<int>& vertices);
    bool existeArestaConectando(int v, const std::vector<int>& subgrafoVertices);
    bool verificaRestricoesD0Y0(const std::vector<Subgraph>& subgrafos, const std::vector<std::pair<int, int>>& D0, const std::vector<std::tuple<int, int, int>>& Y0);

    // Matriz de adjacência
    std::vector<std::vector<int>> adj;

    // Pesos dos vértices (usado internamente)
    std::vector<int> pesosVert;
};

#endif // GRAPH_H

