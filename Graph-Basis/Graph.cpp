#include "Graph.hpp"
#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <stack>
#include <algorithm> // para std::find
#include <climits>

#define INF std::numeric_limits<int>::max()

Graph::Graph() {
    // Inicialize os atributos aqui se necessário, como p = 0;
    p = 0;
    // Outras inicializações, se aplicável
}
int Graph::lerArquivo(const std::string& nomeArquivo) {
    std::ifstream file(nomeArquivo);
    if (!file.is_open()) {
        std::cerr << "Erro ao abrir o arquivo: " << nomeArquivo << std::endl;
        return -1;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);

        if (line.find("param p :=") != std::string::npos) {
            // Lê o valor de p
            iss.ignore(11); // Ignora "param p :="
            iss >> p;
            std::cout << "Numero de subgrafos (p): " << p << std::endl;
        } 
        else if (line.find("set V :=") != std::string::npos) {
            // Lê os vértices até encontrar o caractere ';'
            while (std::getline(file, line) && line != ";") {
                std::istringstream verticesStream(line);
                int v;
                while (verticesStream >> v) {
                    vertices.push_back(v);
                }
            }
            std::cout << "Numero de vértices lidos: " << vertices.size() << std::endl;
        }
        else if (line.find("param w :=") != std::string::npos) {
            // Lê os pesos dos vértices
            while (std::getline(file, line) && line != ";") {
                std::istringstream pesoStream(line);
                int v, w;
                pesoStream >> v >> w;
                pesosVertices[v] = w;
            }
        }

        else if (line.find("set E :=") != std::string::npos) {
            std::string allEdges;
    
             // Ler todas as linhas de arestas até encontrar o caractere ';'
            while (std::getline(file, line) && line != ";"){// Remove espaços extras e acumula a linha
                allEdges += line + " ";
            }


            // Processa cada par de arestas da string acumulada
            std::istringstream edgeStream(allEdges);
            char ignore;
            int u, v;

            // Adiciona cada par de arestas à lista de arestas
            while (edgeStream >> ignore >> u >> ignore >> v >> ignore) {
                //std::cout << "Aresta lida: (" << u << "," << v << ")" << std::endl;
                arestas.emplace_back(u, v);
                //std::cout << arestas.size() << std::endl; //contador de arestas (deu mais de 570)

            }

            std::cout << "Numero de arestas lidas: " << arestas.size() << std::endl;
    }


        else if (line.find("set D0 :=") != std::string::npos) {
   
        std::string allD0;
        bool reading = true;

            while (reading && std::getline(file, line)) {
                if (line.find(";") != std::string::npos) {
                // Se encontrar ";", remova-o e pare a leitura
                allD0 += line.substr(0, line.find(";"));
                reading = false;
        }       else {
                // Acumula o conteúdo das linhas
                allD0 += line + " ";
                 }
    }

    //std::cout << "Conteúdo total de D0: " << allD0 << std::endl;
    std::istringstream d0Stream(allD0);
    char ignore;
    int u, v;
    while (d0Stream >> ignore >> u >> ignore >> v >> ignore) {
        //std::cout << "Par D0 lido: (" << u << "," << v << ")" << std::endl;
        D0.emplace_back(u, v);
    }
    std::cout << "Conteudo total de D0: " << D0.size() << std::endl;
} 
else if (line.find("set Y0 :=") != std::string::npos) {
 
    std::string allY0;
    bool reading = true;

    while (reading && std::getline(file, line)) {
        if (line.find(";") != std::string::npos) {
            // Se encontrar ";", remova-o e pare a leitura
            allY0 += line.substr(0, line.find(";"));
            reading = false;
        } else {
            // Acumula o conteúdo das linhas
            allY0 += line + " ";
        }
    }

    //std::cout << "Conteúdo total de Y0: " << allY0 << std::endl;
    std::istringstream y0Stream(allY0);
    char ignore;
    int a, b, c;
    while (y0Stream >> ignore >> a >> ignore >> b >> ignore >> c >> ignore) {
        //std::cout << "Tripla Y0 lida: (" << a << "," << b << "," << c << ")" << std::endl;
        Y0.emplace_back(a, b, c);
    }
    std::cout << "Conteudo total de Y0: " << Y0.size() << std::endl;
}

    }

    file.close();
    return 0;
}



bool Graph::isGrafoConexo(const std::vector<std::pair<int, int>>& arestas, const std::vector<int>& vertices) {
    if (vertices.empty()) {
        return false;
    }

    // Inicializa a estrutura de visitados
    std::unordered_map<int, bool> visitado;
    for (int v : vertices) {
        visitado[v] = false;
    }

    // Realiza uma busca em profundidade (DFS) a partir de um vértice arbitrário
    std::stack<int> s;
    int primeiroVertice = vertices[0];
    s.push(primeiroVertice);
    visitado[primeiroVertice] = true;

    int visitados = 1; // Conta os vértices visitados

    while (!s.empty()) {
        int v = s.top();
        s.pop();

        // Para cada aresta, verifica as conexões
        for (const auto& aresta : arestas) {
            int vizinho = -1;
            if (aresta.first == v && !visitado[aresta.second]) {
                vizinho = aresta.second;
            } else if (aresta.second == v && !visitado[aresta.first]) {
                vizinho = aresta.first;
            }

            if (vizinho != -1 && !visitado[vizinho]) {
                visitado[vizinho] = true;
                s.push(vizinho);
                visitados++;
            }
        }
    }

    // O grafo é conexo se todos os vértices foram visitados
    return visitados == vertices.size();
}


bool Graph::existeArestaConectando(int vertice, const std::vector<int>& subgrafo) const {
    for (const auto& aresta : arestas) {
        if ((aresta.first == vertice && std::find(subgrafo.begin(), subgrafo.end(), aresta.second) != subgrafo.end()) ||
            (aresta.second == vertice && std::find(subgrafo.begin(), subgrafo.end(), aresta.first) != subgrafo.end())) {
            return true;
        }
    }
    return false;
}




void Graph::atualizarSomaPesos() {
    somaPesos.clear();
    somaPesos.resize(p, 0);

    for (int i = 0; i < p; ++i) {
        for (int vertice : subgrafos[i]) {
            somaPesos[i] += pesosVertices[vertice];
        }
    }
}

int Graph::calcularSomaDosGaps() const {
    if (subgrafos.empty()) {
        std::cerr << "Os subgrafos ainda não foram gerados." << std::endl;
        return -1; // Indicando erro, subgrafos não inicializados
    }

    // Encontrar o peso mínimo e máximo dos subgrafos
    int minPeso = *std::min_element(somaPesos.begin(), somaPesos.end());
    int maxPeso = *std::max_element(somaPesos.begin(), somaPesos.end());

    // Calcular a soma dos gaps
    int somaDosGaps = 0;
    for (int peso : somaPesos) {
        if (peso != minPeso && peso != maxPeso) {
            somaDosGaps += std::abs(peso - minPeso);
        }
    }

    return somaDosGaps;
}

void Graph::algoritmoGulosoMGGPP() {
    // Inicialização dos subgrafos e soma de pesos
    subgrafos.resize(p);
    somaPesos.resize(p, 0);

    // Ordem dos vértices (por exemplo, por peso, você pode usar uma ordem diferente)
    std::vector<int> ordemVertices = vertices;
    std::sort(ordemVertices.begin(), ordemVertices.end(), [this](int a, int b) {
        return pesosVertices[a] > pesosVertices[b];
    });

    // Atribuição gulosa
    for (int vertice : ordemVertices) {
        int subgrafo = escolherSubgrafo(vertice);
        subgrafos[subgrafo].push_back(vertice);
        somaPesos[subgrafo] += pesosVertices[vertice];
    }

    // Incorporar D0: garantir que as arestas em D0 estejam corretamente alocadas
    for (const auto& aresta : D0) {
    int u = aresta.first;
    int v = aresta.second;

    // Verifica se u e v estão em subgrafos diferentes
    int subgrafoU = -1;
    int subgrafoV = -1;
    for (int i = 0; i < p; ++i) {
        if (std::find(subgrafos[i].begin(), subgrafos[i].end(), u) != subgrafos[i].end()) {
            subgrafoU = i;
        }
        if (std::find(subgrafos[i].begin(), subgrafos[i].end(), v) != subgrafos[i].end()) {
            subgrafoV = i;
        }
    }

    if (subgrafoU != subgrafoV) {
        // Garantir que a aresta seja incluída no mesmo subgrafo
        if (somaPesos[subgrafoU] <= somaPesos[subgrafoV]) {
            // Move o vértice v para o subgrafo que contém u
            subgrafos[subgrafoU].push_back(v);
            somaPesos[subgrafoU] += pesosVertices[v];

            // Remove v do subgrafo original
            subgrafos[subgrafoV].erase(std::remove(subgrafos[subgrafoV].begin(), subgrafos[subgrafoV].end(), v), subgrafos[subgrafoV].end());
            somaPesos[subgrafoV] -= pesosVertices[v];
        } else {
            // Move o vértice u para o subgrafo que contém v
            subgrafos[subgrafoV].push_back(u);
            somaPesos[subgrafoV] += pesosVertices[u];

            // Remove u do subgrafo original
            subgrafos[subgrafoU].erase(std::remove(subgrafos[subgrafoU].begin(), subgrafos[subgrafoU].end(), u), subgrafos[subgrafoU].end());
            somaPesos[subgrafoU] -= pesosVertices[u];
        }
    }
}

    // Incorporar Y0: verificar e ajustar restrições específicas
    for (const auto& tupla : Y0) {
        int a, b, c;
        std::tie(a, b, c) = tupla;
        // Lógica para aplicar as restrições de Y0 aos subgrafos
        // (Exemplo: garantir que a restrição seja respeitada, ajustar partição se necessário)
    }
    atualizarSomaPesos();
}

void Graph::algoritmoGulosoAdaptativoMGGPP(int seed) {
}

void Graph::algoritmoGulosoAdaptativoReativoMGGPP(int seed) {
}

int Graph::escolherSubgrafo(int vertice) {
    // Inicialmente, escolhe o subgrafo com a menor soma de pesos
    int melhorSubgrafo = 0;
    int menorPeso = std::numeric_limits<int>::max();

    for (int i = 0; i < p; ++i) {
        bool podeAdicionar = true;

        // Verificar se adicionar o vértice ao subgrafo respeita as restrições de Y0
        for (const auto& tupla : Y0) {
            int a, b, c;
            std::tie(a, b, c) = tupla;
            if (std::find(subgrafos[i].begin(), subgrafos[i].end(), a) != subgrafos[i].end() &&
                std::find(subgrafos[i].begin(), subgrafos[i].end(), b) != subgrafos[i].end() &&
                existeArestaConectando(vertice, subgrafos[i])) {
                podeAdicionar = false;
                break;
            }
        }

        if (podeAdicionar && somaPesos[i] < menorPeso) {
            menorPeso = somaPesos[i];
            melhorSubgrafo = i;
        }
    }

    return melhorSubgrafo;
}

void Graph::imprimirSubgrafos() const {
    for (int i = 0; i < subgrafos.size(); ++i) {
        std::cout << "Subgrafo " << i << " (Peso Total: " << somaPesos[i] << "):\n";
        for (int vertice : subgrafos[i]) {
            std::cout << vertice << " ";
        }
        std::cout << "\n";
    }
}
