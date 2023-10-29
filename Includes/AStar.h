#pragma once
#include <vector>

namespace Engine
{
    int Heuristic(int x1, int y1, int x2, int y2);
    std::vector<std::pair<int, int>> AStar(const std::vector<int>& grid, int numberOfRows, int numberOfCols, int startX, int startY, int goalX, int goalY);
}