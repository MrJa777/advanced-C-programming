#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string>

// Helper function for exploring nodes (DFS)
bool explore(const std::unordered_map<int, std::vector<int>>& graph, int current, std::unordered_set<int>& visited) {
    if (visited.find(current) != visited.end()) {
        return false; // Node has already been visited
    }

    visited.insert(current); // Mark the node as visited

    // Explore all neighbors recursively
    for (int neighbor : graph.at(current)) {
        explore(graph, neighbor, visited);
    }

    return true; // A new connected component was found
}

// Function to count connected components
int connectedComponentsCount(const std::unordered_map<int, std::vector<int>>& graph) {
    std::unordered_set<int> visited;
    int count = 0;

    // Iterate through all nodes in the graph
    for (const auto& node : graph) {
        int nodeKey = node.first;
        if (explore(graph, nodeKey, visited)) {
            count += 1; // Increment count for each new connected component
        }
    }

    return count;
}

int main() {
    // Sample graph as an adjacency list
    std::unordered_map<int, std::vector<int>> graph = {
        {3, {}},            // Node 3 has no neighbors
        {4, {6}},           // Node 4 is connected to 6
        {6, {4, 5, 7, 8}},  // Node 6 is connected to 4, 5, 7, 8
        {8, {6}},           // Node 8 is connected to 6
        {7, {6}},           // Node 7 is connected to 6
        {5, {6}},           // Node 5 is connected to 6
        {1, {2}},           // Node 1 is connected to 2
        {2, {1}}            // Node 2 is connected to 1
    };

    // Count connected components
    int count = connectedComponentsCount(graph);

    std::cout << "Connected Components Count: " << count << std::endl;

    return 0;
}
