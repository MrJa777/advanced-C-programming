#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
#include <string>
#include <set>  // To track visited nodes

// BFS Function to traverse the graph
void breadthFirstPrint(std::unordered_map<std::string, std::vector<std::string>>& graph, const std::string& source) {
    std::queue<std::string> queue;      // Queue to explore nodes in BFS order
    std::set<std::string> visited;      // Set to keep track of visited nodes

    queue.push(source);                 // Start BFS from the source node
    visited.insert(source);             // Mark the source as visited

    while (!queue.empty()) {
        std::string current = queue.front();  // Get the front node from the queue
        queue.pop();                          // Remove it from the queue
        std::cout << current << std::endl;    // Print the current node

        // Traverse adjacent nodes
        for (const std::string& neighbor : graph[current]) {
            if (visited.find(neighbor) == visited.end()) {  // Check if neighbor is not visited
                queue.push(neighbor);                       // Add neighbor to the queue
                visited.insert(neighbor);                   // Mark neighbor as visited
            }
        }
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

    // Perform BFS starting from node "a"
    breadthFirstPrint(graph, "a");  // Expected output: a, b, c, d, e, f

    return 0;
}
