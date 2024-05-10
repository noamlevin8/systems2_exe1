// ID: 326662574
// MAIL: noamlevin11@gmail.com

#pragma once

#include "Graph.hpp"
#include <unordered_map>
#include <queue>
#include <limits>
#include <algorithm>

using namespace ariel;
using namespace std;

namespace Algorithms {
        string isConnected(Graph g);
        string shortestPath(Graph g, size_t start, size_t end);
        string isContainsCycle(Graph g);
        string isBipartite(Graph g);
        string negativeCycle(Graph g);

        void dfs(Graph g, size_t v, vector<bool>& visited); // For the connected function
        int DFSVisit(Graph g, size_t u, vector<string> color, vector<int>& parent); //For the contains cycle function
        string bellmanFord(Graph g, size_t V, size_t src);
}