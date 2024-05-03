// ID: 326662574
// MAIL: noamlevin11@gmail.com

#include "Graph.hpp"
#include <unordered_map>
#include <queue>
#include <limits>

using namespace ariel;
using namespace std;

namespace Algorithms {
        string isConnected(Graph g);
        string shortestPath(Graph g, int start, int end);
        string isContainsCycle(Graph g);
        string isBipartite(Graph g);
        string negativeCycle(Graph g);

        void dfs(Graph g, int v, vector<bool>& visited); // For the connected function
        bool hasCycleDFS(Graph g, int v, vector<bool>& visited, unordered_map<int,int>& parent, string& cycle);
        bool ifBipartite(Graph g, int src, vector<int>& color);
        vector<int> bellmanFord(Graph g, int v, int src);
}