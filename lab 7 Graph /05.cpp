#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <stack>

// Iterative DFS function to check if a path exists
bool hasPathIterative(std::unordered_map<std::string, std::vector<std::string>>& graph, const std::string& source, const std::string& destination) {
    std::stack<std::string> stack;
    stack.push(source);

    while (!stack.empty()) {
        std::string current = stack.top();
        stack.pop();

        // If we reach the destination, return true
        if (current == destination) {
            return true;
        }

        // Push all neighbors onto the stack for exploration
        for (const std::string& neighbor : graph[current]) {
            stack.push(neighbor);
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
    if (hasPathIterative(graph, "a", "c")) {
        std::cout << "Path exists!" << std::endl;
    } else {
        std::cout << "No path found." << std::endl;
    }

    return 0;
}
