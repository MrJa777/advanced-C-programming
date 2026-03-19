#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

// Recursive DFS function to check if a path exists
bool hasPath(std::unordered_map<std::string, std::vector<std::string>>& graph, const std::string& source, const std::string& destination) {
    // Base case: if source equals destination, a path exists
    if (source == destination) {
        return true;
    }

    // Explore each neighbor of the current source
    for (const std::string& neighbor : graph[source]) {
        if (hasPath(graph, neighbor, destination)) {
            return true;  // Return true as soon as a path is found
        }
    }

    return false;  // No path found, return false
}

int main() {
    // Define the graph (adjacency list)
    std::unordered_map<std::string, std::vector<std::string>> graph;
    graph["a"] = {"b", "c"};
    graph["b"] = {"d"};
    graph["c"] = {"e"};
    graph["d"] = {"f"};
    graph["e"] = {};
    graph["f"] = {};

    // Check if there's a path from "a" to "c"
    if (hasPath(graph, "a", "c")) {
        std::cout << "Path exists!" << std::endl;
    } else {
        std::cout << "No path found." << std::endl;
    }

    return 0;
}
