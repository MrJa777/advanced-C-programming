#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <string>

using namespace std;

unordered_map<string, vector<string>> buildGraph(const vector<pair<string, string>>& edges) {
    unordered_map<string, vector<string>> graph;

    for (const auto& edge : edges) {
        string a = edge.first;
        string b = edge.second;

        if (graph.find(a) == graph.end()) graph[a] = vector<string>();
        if (graph.find(b) == graph.end()) graph[b] = vector<string>();

        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    return graph;
}

int shortestPath(const vector<pair<string, string>>& edges, const string& nodeA, const string& nodeB) {
    unordered_map<string, vector<string>> graph = buildGraph(edges);
    queue<pair<string, int>> q;
    unordered_set<string> visited;
    
    q.push({nodeA, 0});
    visited.insert(nodeA);

    while (!q.empty()) {
        auto [node, distance] = q.front();
        q.pop();

        if (node == nodeB) return distance;

        for (const string& neighbor : graph[node]) {
            if (visited.find(neighbor) == visited.end()) {
                q.push({neighbor, distance + 1});
                visited.insert(neighbor); 
            }
        }
    }

    return -1;
}

int main() {
    vector<pair<string, string>> edges = {
        {"W", "X"}, 
        {"X", "Y"}, 
        {"Z", "Y"}, 
        {"Z", "V"}, 
        {"W", "V"}
    };
    
    string nodeA = "W";
    string nodeB = "Y";

    int distance = shortestPath(edges, nodeA, nodeB);
    if (distance != -1) {
        cout << "Shortest path from " << nodeA << " to " << nodeB << " is " << distance << endl;
    } else {
        cout << "There is no path between " << nodeA << " and " << nodeB << endl;
    }

    return 0;
}
