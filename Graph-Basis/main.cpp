#include <iostream>
#include <vector>
#include "Graph.hpp"
#include <climits>

int main() {
    Graph g;
    std::string nomeArquivo = "MGGPP/n100d03p2i5.txt";

    if (g.lerArquivo(nomeArquivo) != 0) {
        return -1;
    }

    // Executa o algoritmo guloso para resolver o MGGPP
    g.algoritmoGulosoBalanceadoMGGPP();

    return 0;
}
