#include <iostream>
#include <vector>
#include <queue>
#include <limits.h>

using namespace std;

class Graph {
public:
    int n;
    vector<vector<pair<int, int>>> adj;

    // Constructor para inicializar el grafo con n nodos y las aristas dadas
    Graph(int n, vector<vector<int>>& edges) {
        this->n = n;
        adj.resize(n);
        for (const auto& edge : edges) {
            addEdge(edge);
        }
    }

    // Función para añadir una arista al grafo
    void addEdge(const vector<int>& edge) {
        int from = edge[0] - 1; // Convertimos los nodos a base 0
        int to = edge[1] - 1;   // Convertimos los nodos a base 0
        int cost = edge[2];
        adj[from].push_back({to, cost});
    }

    // Función para encontrar el camino más corto entre node1 y node2
    int shortestPath(int node1, int node2) {
        vector<int> dist(n, INT_MAX); // Inicializamos las distancias con infinito (INT_MAX)
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

        node1 -= 1; // Convertimos node1 a base 0
        node2 -= 1; // Convertimos node2 a base 0

        dist[node1] = 0; // La distancia desde el nodo de origen hacia sí mismo es 0
        pq.push({0, node1}); // Insertamos el nodo origen en la cola de prioridad

        while (!pq.empty()) {
            int currentDist = pq.top().first; // Distancia actual
            int u = pq.top().second; // Nodo actual
            pq.pop(); // Quitamos el nodo de la cola

            if (currentDist > dist[u]) continue; // Si la distancia ya no es óptima, ignoramos este nodo

            // Recorremos todos los vecinos del nodo actual
            for (const auto& [v, weight] : adj[u]) {
                // Si encontramos una ruta más corta hacia el nodo vecino
                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight; // Actualizamos la distancia
                    pq.push({dist[v], v}); // Añadimos el vecino a la cola de prioridad
                }
            }
        }

        // Si la distancia final hacia node2 sigue siendo "infinita", significa que no hay camino
        if (dist[node2] == INT_MAX) {
            return -1;  // No hay camino, devolvemos -1
        } else {
            return dist[node2];  // Retornamos la distancia mínima encontrada
        }
    }
};

int main() {
    // Inicializamos el grafo con las aristas correctas del ejemplo
    vector<vector<int>> edges = {
            {1, 2, 6},   // Nodo 1 a Nodo 2 con costo 6
            {2, 3, 5},   // Nodo 2 a Nodo 3 con costo 5
            {3, 4, 2},   // Nodo 3 a Nodo 4 con costo 2
            {4, 5, 3},   // Nodo 4 a Nodo 5 con costo 3
            {5, 6, 6},   // Nodo 5 a Nodo 6 con costo 6
            {1, 3, 2}    // Nodo 1 a Nodo 3 con costo 2
    };

    Graph* g = new Graph(6, edges);  // Creamos el grafo con 6 nodos

    // Ejecutamos las operaciones de acuerdo con el input de la imagen
    cout << "null" << endl; // Resultado de "Graph"
    cout << g->shortestPath(1, 6) << endl; // Resultado de "shortestPath(1, 6)"
    cout << g->shortestPath(6, 1) << endl; // Resultado de "shortestPath(6, 1)"

    g->addEdge({2, 4, 3}); // Añadimos una nueva arista: {2, 4, 3}
    cout << "null" << endl; // Resultado de "addEdge"

    cout << g->shortestPath(1, 6) << endl; // Resultado de "shortestPath(1, 6)" después de añadir la arista

    return 0;
}
