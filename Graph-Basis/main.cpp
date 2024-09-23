#include "Graph.hpp"
#include <climits>
#include <iostream>
#include <vector>

int main() {
    Graph g;
    std::string nomeArquivo = "MGGPP/n100d03p2i5.txt";

    if (g.lerArquivo(nomeArquivo) != 0) {
        return -1;
    }

    // Executa o algoritmo guloso para resolver o MGGPP
    g.algoritmoGulosoMGGPP();
    g.imprimirSubgrafos();
    
    int somaDosGaps = g.calcularSomaDosGaps();
    if (somaDosGaps != -1) {
        std::cout << "Soma dos gaps: " << somaDosGaps << std::endl;
    }
    return 0;
}