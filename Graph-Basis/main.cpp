#include "Graph.hpp"
#include <climits>
#include <iostream>
#include <vector>
#include <string>


using namespace std;

int exec(Graph g, int alg, int n, int seed) {

    int somaDosGaps = -1;

    switch (alg){
        // GULOSO
        case 1:
            g.guloso(0);
        break;
        // GULOSO RANDOMIZADO ADAPTATIVO
        case 2:
            for (int i = 0; i < n; i++){
                //g.greedyA(seed);
            }
        break;
        // GULOSO RANDOMIZADO ADAPTATIVO REATIVO
        case 3:
            for (int i = 0; i < n; i++){
                //g.greedyAR(seed);
            }
        break;
        // NENHUMA ALTERNATIVA SELECIONADA
        default:
            cout << "Nenhum algoritimo selecionado" << endl;
            return -1;
        }

        if (somaDosGaps != -1) {
            cout << "Soma dos gaps: " << somaDosGaps << endl;
        }

    return 0;
}

int main(int argc, char *argv[]) {

    if (argc < 3){
        cout << "Nenhuma instância reconhecida" << endl;
        return -1;
    } else {

        string nomeArquivo = argv[1];
        int alg = stoi(argv[2]);

        Graph g = Graph(nomeArquivo);

        int n = 1;
        int seed = 1;

        if (argc > 3) {
            n = stoi(argv[3]);
        }

        if (argc > 4) {
            seed = stoi(argv[4]);
        }

       int result = exec(g, alg, n, seed);

       if (result != 0) {
        return -1;
       }
    }
    return 0;
}