#include <iostream>
#include <stack>
#include <unordered_map>
#include <vector>
#include <string>

// Function to perform DFS traversal starting from the source node
void depthFirstPrint(std::unordered_map<std::string, std::vector<std::string>>& graph, const std::string& source) {
    std::stack<std::string> stack;  // Initialize stack
    stack.push(source);  // Push the source node to the stack

    while (!stack.empty()) {  // Continue until the stack is empty
        std::string current = stack.top();  // Get the top node from the stack
        stack.pop();  // Remove the top node from the stack
        std::cout << current << std::endl;  // Print the current node

        // Traverse the adjacent nodes in reverse order
        for (auto it = graph[current].rbegin(); it != graph[current].rend(); ++it) {
            stack.push(*it);  // Push each adjacent node to the stack
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

    // Perform DFS starting from node "a"
    depthFirstPrint(graph, "a");  // Expected output: a, b, d, f, c, e

    return 0;
}
