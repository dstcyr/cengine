#include "AStar.h"
#include "Log.h"
#include <queue>
// #include <cmath>
// #include <functional>
// #include <limits>

struct Node
{
    int index;
    int gScore;
    int hScore;
    Node* parent;

    Node() : Node(0, 0, 0, nullptr) {}
    Node(int index, int g, int h, Node* parent)
        : index(index), gScore(g), hScore(h), parent(parent){}

    int Score() const
    {
        return gScore + hScore;
    }
};

// Define a comparison function for the priority queue
struct CompareNode 
{
    bool operator()(const Node* a, const Node* b) const
    {
        return a->Score() > b->Score();
    }
};

bool IsValid(int x, int y, int width, int height, const std::vector<int>& grid)
{
    int idx = y * height + x;
    return !(x < 0 || x >= height || y < 0 || y >= width || grid[idx] == 1);
}

std::vector<std::pair<int, int>> CreatePath(Node* head, int width, int height)
{
    // Reconstruct the path
    std::vector<std::pair<int, int>> path;
    Node* current = head;
    while (current != nullptr)
    {
        int x = current->index % height;
        int y = current->index / height;
        path.emplace_back(x, y);
        current = current->parent;
    }

    std::reverse(path.begin(), path.end());
    return path;
}

int Engine::Heuristic(int x1, int y1, int x2, int y2)
{
    return std::abs(x1 - x2) + std::abs(y1 - y2);
}

std::vector<std::pair<int, int>> Engine::AStar(const std::vector<int>& grid, int numberOfRows, int numberOfCols, int startX, int startY, int goalX, int goalY)
{
    //if (startX < 0 || startX >= height || startY < 0 || startY >= width || grid[startIdx] == 1)
    if(!IsValid(startX, startY, numberOfRows, numberOfCols, grid))
    {
        LOG(LL_WARNING, "Invalid start position (%d, %d)", startX, startY);
        return {};
    }

    //if (goalX < 0 || goalX >= height || goalY < 0 || goalY >= width || grid[goalIdx] == 1)
    if (!IsValid(goalX, goalY, numberOfRows, numberOfCols, grid))
    {
        LOG(LL_WARNING, "Invalid goal position (%d, %d)", goalX, goalY);
        return {};
    }

    // Create a 1D array to track whether a node is visited or not
    std::vector<bool> visited(numberOfRows * numberOfCols, false);

    // Priority queue for open nodes
    std::priority_queue<Node*, std::vector<Node*>, CompareNode> openSet;

    int startIdx = startY * numberOfCols + startX;
    int goalIdx = goalY * numberOfCols + goalX;

    // Create the start node and add it to the open set
    Node* startNode = new Node(startIdx, 0, Heuristic(startX, startY, goalX, goalY), nullptr);
    openSet.push(startNode);

    const int dx[] = { 1, -1, 0, 0 };
    const int dy[] = { 0, 0, 1, -1 };

    // Main loop
    while (!openSet.empty())
    {
        Node* current = openSet.top();
        openSet.pop();

        // Check if the current node is the goal
        if (current->index == goalIdx)
        {
            //// Reconstruct the path
            //std::vector<std::pair<int, int>> path;
            //while (current != nullptr)
            //{
            //    int x = current->index % height;
            //    int y = current->index / height;
            //    path.emplace_back(x, y);
            //    current = current->parent;
            //}
            //std::reverse(path.begin(), path.end());
            //return path;

            return CreatePath(current, numberOfRows, numberOfCols);
        }

        visited[current->index] = true;

        // Generate neighboring nodes
        for (int i = 0; i < 4; i++)
        {
            int newX = current->index % numberOfCols + dx[i];
            int newY = current->index / numberOfCols + dy[i];
            int newIndex = newY * numberOfCols + newX;

            // Check if the neighbor is within bounds and not blocked
            if (newX >= 0 && newX < numberOfCols && newY >= 0 && newY < numberOfRows && grid[newIndex] != 1 && !visited[newIndex])
            {
                int newG = current->gScore + 1;  // Assuming a cost of 1 to move to a neighboring cell
                int newH = Heuristic(newX, newY, goalX, goalY);
                Node* neighbor = new Node(newIndex, newG, newH, current);
                openSet.push(neighbor);
            }
        }
    }

    // If the goal is not reachable, return an empty path
    return {};
}
