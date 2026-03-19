#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

// Recursive DFS function to traverse the graph
void depthFirstPrint(std::unordered_map<std::string, std::vector<std::string>>& graph, const std::string& source) {
    std::cout << source << std::endl;  // Print the current node

    // Traverse the adjacent nodes recursively
    for (auto it = graph[source].begin(); it != graph[source].end(); ++it) {
        depthFirstPrint(graph, *it);  // Recursive call to visit each neighbor
    }
}

int main() {
    // Define the graph using an unordered_map (adjacency list representation)
    std::unordered_map<std::string, std::vector<std::string>> graph;
    graph["a"] = {"b", "c"};
    graph["b"] = {"d"};
    graph["c"] = {"e"};
    graph["d"] = {"f"};
    graph["e"] = {};
    graph["f"] = {};

    // Perform DFS starting from node "a"
    depthFirstPrint(graph, "a");  // Expected output: a, b, d, f, c, e

    return 0;
}
