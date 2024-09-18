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


bool Graph::existeArestaConectando(int v, const std::vector<int>& subgrafoVertices) {
    // Verifica se o vértice 'v' está conectado a qualquer vértice do subgrafo
    for (const auto& aresta : arestas) {
        if ((aresta.first == v && std::find(subgrafoVertices.begin(), subgrafoVertices.end(), aresta.second) != subgrafoVertices.end()) ||
            (aresta.second == v && std::find(subgrafoVertices.begin(), subgrafoVertices.end(), aresta.first) != subgrafoVertices.end())) {
            return true;
        }
    }
    return false;
}



int Graph::calcularSomaDosGaps(const std::vector<Subgraph>& subgrafos) {
    int somaGaps = 0;
    
    // Itera sobre todos os pares de subgrafos
    for (size_t i = 0; i < subgrafos.size(); ++i) {
        for (size_t j = i + 1; j < subgrafos.size(); ++j) {
            int gap = std::abs(subgrafos[i].pesoTotal - subgrafos[j].pesoTotal);
            somaGaps += gap;
        }
    }
    
    return somaGaps;
}

int Graph::escolherSubgrafoMinimoGap(const std::vector<Subgraph>& subgrafos, int v) {
    int subgrafoEscolhido = -1;
    int menorAumentoGap = INT_MAX;

    for (int i = 0; i < subgrafos.size(); ++i) {
        if (existeArestaConectando(v, subgrafos[i].vertices)) {
            int pesoAtual = subgrafos[i].pesoTotal;
            int novoPeso = pesoAtual + pesosVertices[v];
            std::vector<Subgraph> tempSubgrafos = subgrafos;
            tempSubgrafos[i].pesoTotal = novoPeso;
            int novoSomaGaps = calcularSomaDosGaps(tempSubgrafos);

            int aumentoGap = novoSomaGaps - calcularSomaDosGaps(subgrafos);
            if (aumentoGap < menorAumentoGap) {
                menorAumentoGap = aumentoGap;
                subgrafoEscolhido = i;
            }
        }
    }

    return subgrafoEscolhido;
}

void Graph::algoritmoGulosoBalanceadoMGGPP() {
    std::vector<Subgraph> subgrafos(p);

    // Inicializa os subgrafos com um vértice cada
    for (int i = 0; i < p; ++i) {
        subgrafos[i].vertices.push_back(vertices[i]);
        subgrafos[i].pesoTotal = pesosVertices[vertices[i]];
    }

    // Adiciona os vértices restantes
    for (int i = p; i < vertices.size(); ++i) {
        int v = vertices[i];
        bool alocado = false;

        // Tenta alocar o vértice em um subgrafo que mantenha a conectividade
        for (int tentativa = 0; tentativa < p; ++tentativa) {
            int subgrafoEscolhido = escolherSubgrafoMinimoGap(subgrafos, v);
            if (subgrafoEscolhido != -1) {
                Subgraph& sgEscolhido = subgrafos[subgrafoEscolhido];

                // Verifica se o vértice está conectado a algum vértice do subgrafo
                if (existeArestaConectando(v, sgEscolhido.vertices)) {
                    // Adiciona o vértice ao subgrafo, já que ele mantém a conectividade
                    sgEscolhido.vertices.push_back(v);
                    sgEscolhido.pesoTotal += pesosVertices[v];

                    // Adiciona as arestas que conectam o novo vértice aos existentes
                    for (const auto& aresta : arestas) {
                        if (aresta.first == v || aresta.second == v) {
                            sgEscolhido.arestas.push_back(aresta);
                        }
                    }
                    alocado = true;
                    break; // Vértice alocado com sucesso
                }
            }
        }

        // Se não conseguiu alocar, algo está errado
        if (!alocado) {
            std::cerr << "Erro: não foi possível adicionar o vértice " << v << " mantendo o subgrafo conexo!" << std::endl;
            return;
        }
    }

    // Exibe as partições resultantes
    for (int i = 0; i < p; i++) {
        std::cout << "Subgrafo " << i + 1 << ": Peso total = " << subgrafos[i].pesoTotal << std::endl;
        std::cout << "Vértices: ";
        for (int v : subgrafos[i].vertices) {
            std::cout << v << " ";
        }
        std::cout << std::endl;
    }

    // Calcula e exibe a soma dos gaps
    int somaGaps = calcularSomaDosGaps(subgrafos);
    std::cout << "Soma dos gaps dos subgrafos: " << somaGaps << std::endl;
}
