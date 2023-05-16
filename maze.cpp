#include <bits/stdc++.h>
#include <vector>
using namespace std;

struct Node {
    int x, y;
    int g, h; // 实际代价和估计代价
    Node* parent;

    Node(int x, int y, int g, int h, Node* parent)
        : x(x)
        , y(y)
        , g(g)
        , h(h)
        , parent(parent)
    {
    }

    int f() const { return g + h; }

    bool operator<(const Node& other) const
    {
        return f() > other.f();
    }
};

vector<pair<int, int>> maze = { /* 迷宫地图 */ };
int rows = /* 迷宫行数 */, cols = /* 迷宫列数 */;
pair<int, int> start = { /* 起点坐标 */ };
pair<int, int> end = { /* 终点坐标 */ };

int manhattan(int x1, int y1, int x2, int y2)
{
    return abs(x1 - x2) + abs(y1 - y2);
}

vector<pair<int, int>> get_neighbors(int x, int y)
{
    vector<pair<int, int>> neighbors;
    if (x > 0 && !maze[(x - 1) * cols + y])
        neighbors.push_back({ x - 1, y });
    if (x < rows - 1 && !maze[(x + 1) * cols + y])
        neighbors.push_back({ x + 1, y });
    if (y > 0 && !maze[x * cols + y - 1])
        neighbors.push_back({ x, y - 1 });
    if (y < cols - 1 && !maze[x * cols + y + 1])
        neighbors.push_back({ x, y + 1 });
    return neighbors;
}

vector<pair<int, int>> find_path()
{
    priority_queue<Node> q;
    q.emplace(start.first, start.second, 0, manhattan(start.first, start.second, end.first, end.second), nullptr);
    unordered_map<int, unordered_map<int, int>> visited;

    while (!q.empty()) {
        auto node = q.top();
        q.pop();
        if (visited[node.x][node.y])
            continue;
        visited[node.x][node.y] = node.g;

        if (node.x == end.first && node.y == end.second) {
            vector<pair<int, int>> path;
            while (node.parent) {
                path.emplace_back(node.x, node.y);
                node = *node.parent;
            }
            path.emplace_back(start.first, start.second);
            reverse(path.begin(), path.end());
            return path;
        }

        for (auto [nx, ny] : get_neighbors(node.x, node.y)) {
            int ng = node.g + 1;
            int nh = manhattan(nx, ny, end.first, end.second);
            if (!visited[nx][ny] || visited[nx][ny] > ng) {
                q.emplace(nx, ny, ng, nh, &node);
            }
        }
    }

    return {};
}