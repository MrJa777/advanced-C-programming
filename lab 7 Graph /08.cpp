#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

int exploreSize(const std::unordered_map<int, std::vector<int>>& graph, int node, std::unordered_set<int>& visited) {
    if (visited.find(node) != visited.end()) return 0;

    visited.insert(node);
    int size = 1;

    // Explore all the neighbors
    for (int neighbor : graph.at(node)) {
        size += exploreSize(graph, neighbor, visited);
    }

    return size;
}

int largestComponent(const std::unordered_map<int, std::vector<int>>& graph) {
    std::unordered_set<int> visited;
    int longest = 0;

    for (const auto& entry : graph) {
        int node = entry.first;
        int size = exploreSize(graph, node, visited);
        if (size > longest) {
            longest = size;
        }
    }

    return longest;
}

int main() {
    std::unordered_map<int, std::vector<int>> graph = {
        {0, {8, 1, 5}},
        {1, {0}},
        {5, {0, 8}},
        {8, {0, 5}},
        {2, {3, 4}},
        {3, {2, 4}},
        {4, {3, 2}},
    };

    std::cout << "Largest Component Size: " << largestComponent(graph) << std::endl;
    return 0;
}
