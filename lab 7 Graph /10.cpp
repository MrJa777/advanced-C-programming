#include <iostream>
#include <vector>
#include <unordered_set>
#include <string>

bool explore(const std::vector<std::vector<char>>& grid, int r, int c, std::unordered_set<std::string>& visited){
    bool rowInbounds = 0 <= r && r < grid.size();
    bool colInbounds = 0 <= c && c < grid[0].size();
    if (!rowInbounds || !colInbounds) return false;

    if (grid[r][c] == 'W') return false;

    std::string pos = std::to_string(r) + "," + std::to_string(c);
    if (visited.count(pos)) return false;

    visited.insert(pos);

    explore(grid, r-1, c, visited);
    explore(grid, r+1, c, visited);
    explore(grid, r, c-1, visited);
    explore(grid, r, c+1, visited);

    return true;
}

int islandCount(const std::vector<std::vector<char>>& grid){
    std::unordered_set<std::string> visited;
    int count = 0;

    for (int r = 0; r < grid.size(); ++r)
    {
        for (int c = 0; c < grid[0].size(); ++c)
        {
            if (explore(grid, r, c, visited))
            {
                count += 1;
            }
        }
    }
    return count;
}

int main() {
    std::vector<std::vector<char>> grid = {
        {'W', 'L', 'W', 'L', 'W'},
        {'L', 'L', 'W', 'L', 'W'},
        {'W', 'L', 'W', 'W', 'W'},
        {'W', 'W', 'W', 'L', 'L'},
        {'W', 'L', 'W', 'L', 'L'},
        {'W', 'W', 'W', 'W', 'W'}
    };

    int result = islandCount(grid);
    std::cout << "Number of islands: " << result << std::endl;

    return 0;
}
