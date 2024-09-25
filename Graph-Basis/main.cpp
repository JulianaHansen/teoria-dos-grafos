#include "Graph.hpp"
#include <climits>
#include <iostream>
#include <vector>

int exec(Graph g, int alg, int n, int seed) {

    int somaDosGaps = -1;

    switch (alg){
        // GULOSO
        case 1:
            g.algoritmoGulosoMGGPP();
            somaDosGaps = g.calcularSomaDosGaps();
        break;
        // GULOSO RANDOMIZADO ADAPTATIVO
        case 2:
            for (int i = 0; i < n; i++){
                g.algoritmoGulosoAdaptativoMGGPP(seed);
                int novaSomaDosGaps = g.calcularSomaDosGaps();
                if (novaSomaDosGaps == -1) {
                    return -1;
                }
                if (somaDosGaps == -1 || somaDosGaps > novaSomaDosGaps) {
                    somaDosGaps = novaSomaDosGaps;
                }
            }
        break;
        // GULOSO RANDOMIZADO ADAPTATIVO REATIVO
        case 3:
            for (int i = 0; i < n; i++){
                g.algoritmoGulosoAdaptativoReativoMGGPP(seed);
                int novaSomaDosGaps = g.calcularSomaDosGaps();
                if (novaSomaDosGaps == -1) {
                    return -1;
                }
                if (somaDosGaps == -1 || somaDosGaps > novaSomaDosGaps) {
                    somaDosGaps = novaSomaDosGaps;
                }
            }
        break;
        // NENHUMA ALTERNATIVA SELECIONADA
        default:
            std::cout << "Nenhum algoritimo selecionado" << std::endl;
            return -1;
        }

        if (somaDosGaps != -1) {
            g.imprimirSubgrafos();
            std::cout << "Soma dos gaps: " << somaDosGaps << std::endl;
        }

    return 0;
}

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

        int n = 1;
        int seed = 1;

        if (argc > 3) {
            n = std::stoi(argv[3]);
        }

        if (argc > 4) {
            seed = std::stoi(argv[4]);
        }

       int result = exec(g, alg, n, seed);

       if (result != 0) {
        return -1;
       }
    }
    return 0;
}