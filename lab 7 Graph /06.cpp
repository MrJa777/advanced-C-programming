#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <utility>
#include <unordered_set>

// Function to build the graph from a list of edges
std::unordered_map<std::string, std::vector<std::string>> buildGraph(const std::vector<std::pair<std::string, std::string>>& edges) {
    std::unordered_map<std::string, std::vector<std::string>> graph;

    for (const auto& edge : edges) {
        const std::string& a = edge.first;
        const std::string& b = edge.second;

        // Add nodes if they don't already exist in the graph
        if (graph.find(a) == graph.end()) {
            graph[a] = std::vector<std::string>();
        }
        if (graph.find(b) == graph.end()) {
            graph[b] = std::vector<std::string>();
        }

        // Add the edges in both directions (undirected graph)
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    return graph;
}

// Function to perform DFS, tracking visited nodes to avoid cycles
void depthFirstPrint(const std::unordered_map<std::string, std::vector<std::string>>& graph, const std::string& source, std::unordered_set<std::string>& visited) {
    if (visited.find(source) != visited.end()) return;  // If already visited, return to avoid cycle

    visited.insert(source);  // Mark the node as visited
    std::cout << source << ": ";

    // Print neighbors of the current node
    for (size_t i = 0; i < graph.at(source).size(); ++i) {
        std::cout << graph.at(source)[i];
        if (i < graph.at(source).size() - 1) {
            std::cout << " ";
        }
    }
    std::cout << std::endl;

    // Recursively visit neighbors
    for (const std::string& neighbor : graph.at(source)) {
        depthFirstPrint(graph, neighbor, visited);
    }
}

// Main function to handle the undirected graph traversal
void undirectedPath(const std::vector<std::pair<std::string, std::string>>& edges, const std::string& startNode) {
    std::unordered_map<std::string, std::vector<std::string>> graph = buildGraph(edges);
    std::unordered_set<std::string> visited;

    depthFirstPrint(graph, startNode, visited);
}

int main() {
    // Define the edges of the graph
    std::vector<std::pair<std::string, std::string>> edges = {
        {"a", "b"}, {"a", "c"}, {"b", "d"}, {"c", "e"}, {"d", "f"}
    };

    // Start traversal from node "a"
    undirectedPath(edges, "a");

    return 0;
}
