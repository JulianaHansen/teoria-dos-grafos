#include <vector>
#include <algorithm> // Para std::min e std::max
#include <iostream>

class Particion {
private:
    std::vector<int> nodes; // Armazenar os IDs dos nós
    int minValue;           // Armazenar o menor valor
    int maxValue;           // Armazenar o maior valor

public:
    // Construtor
    Particion() : minValue(INT_MAX), maxValue(INT_MIN) {}

    // Adiciona um nó à partição
    void addNode(int nodeId, int value) {
        nodes.push_back(nodeId);
        minValue = std::min(minValue, value);
        maxValue = std::max(maxValue, value);
    }

    // Obtém a soma dos gaps
    int getGap() const {
        return maxValue - minValue;
    }

    // Exibe os nós na partição
    void displayNodes() const {
        std::cout << "Nós na partição: ";
        for (int id : nodes) {
            std::cout << id << " ";
        }
        std::cout << " | Mínimo: " << minValue << ", Máximo: " << maxValue << std::endl;
    }
};