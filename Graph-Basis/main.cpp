#include "Graph.hpp"
#include <climits>
#include <iostream>
#include <vector>

int main(int argc, char *argv[]) {

    if (argc < 3){
        std::cout << "Nenhuma instância reconhecida" << std::endl;
        return -1;
    } else {

        Graph g;
        std::string nomeArquivo = argv[1];
        int alg = std::stoi(argv[2]);

        if (g.lerArquivo(nomeArquivo) != 0) {
            return -1;
        }

        switch (alg){
            // GULOSO
            case 1:
                // Executa o algoritmo guloso para resolver o MGGPP
                g.algoritmoGulosoMGGPP();
                g.imprimirSubgrafos();
            break;
            // GULOSO RANDOMIZADO ADAPTATIVO
            case 2:
            break;
            // GULOSO RANDOMIZADO ADAPTATIVO REATIVO
            case 3:
            break;
            // NENHUMA ALTERNATIVA SELECIONADA
            default:
                std::cout << "Nenhum algoritimo selecionado" << std::endl;
                return -1;
        }
        
        int somaDosGaps = g.calcularSomaDosGaps();
        if (somaDosGaps != -1) {
            std::cout << "Soma dos gaps: " << somaDosGaps << std::endl;
        }
    }
    return 0;
}