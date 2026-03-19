#include <iostream>  
#include <vector>  
#include <unordered_set>  
#include <string>

int  exploreSize(const std::vector<std::vector<char>>& grid, int r, int c, std::unordered_set<std::string>& visited){
    bool rowInbounds = 0 <= r && r < grid.size();  
    bool colInbounds = 0 <= c && c < grid[0].size();

    if (!rowInbounds || !colInbounds) return 0;
    if (grid[r][c] == 'W') return 0;

    std::string pos = std::to_string(r) + "," + std::to_string(c);  
    if (visited.count(pos)) return 0;

    visited.insert(pos);

    int size = 1;

    

    size += exploreSize(grid, r-1, c, visited);  
    size += exploreSize(grid, r+1, c, visited);  
    size += exploreSize(grid, r, c-1, visited);  
    size += exploreSize(grid, r, c+1, visited);  

    return size;
}

int minimumIsland(const std::vector<std::vector<char>>& grid){  
    std::unordered_set<std::string> visited;  
    int minSize = INT_MAX;  
  
    for (int r = 0; r < grid.size(); ++r)  
    {  
        for (int c = 0; c < grid[0].size(); ++c)  
        {  
            int size = exploreSize(grid, r, c, visited);
            if (size > 0 && size < minSize)
            {
                minSize = size;
            }
        }  
    }  
    return minSize;  
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
  
    int result = minimumIsland(grid);  
    std::cout << "Minimum island size: " << result << std::endl;  
  
    return 0;  
}
