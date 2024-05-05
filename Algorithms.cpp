// ID: 326662574
// MAIL: noamlevin11@gmail.com

#include "Algorithms.hpp"

using namespace std;

namespace Algorithms {

    void dfs(Graph g, size_t v, vector<bool>& visited)
    {
        visited[v] = true;

        size_t i;

        for(i = 0; i < g.getGraph().size(); i++)
        {
            if(g.getGraph()[v][i] != 0 && !visited[i])
            {
                dfs(g, i, visited);
            }
        }
    }

    string isConnected(Graph g) {
        // if(!g.getIfDirected())
        //     return 0;

        // Doing DFS from the first vertex
        vector<bool> visited(g.getGraph().size(),false);
        dfs(g, 0, visited);

        // Checking if all the vertices are visited
        for(bool v : visited)
        {
            if(!v)
                return "0";
        }

        return "1";
    }

    string shortestPath(Graph g, int start, int end) { // Negative cycle

        int size = g.getGraph().size();
        int dis[size][size]; 
        int Next[size][size]; 

        const int INF = 1e7;


        for (size_t i = 0; i < size; i++) 
        { 
            for (size_t j = 0; j < size; j++) 
            { 
                if(g.getGraph()[i][j] == 0)
                    dis[i][j] = INF; 

                else
                    dis[i][j] = g.getGraph()[i][j];
    
                // No edge between node 
                // i and j 
                if (g.getGraph()[i][j] == 0) 
                    Next[i][j] = -1; 
                else
                    Next[i][j] = j; 
            } 
        }

        size_t k, i, j;

        for(k = 0; k < g.getGraph().size(); k++)
        {
            for(i = 0; i < g.getGraph().size(); i++)
            {
                for(j = 0; j < g.getGraph()[0].size(); j++)
                {
                    if(dis[i][k] != INF && dis[k][j] != INF)
                    {
                        if(dis[i][j] > (dis[i][k] + dis[i][k]))
                        {
                            dis[i][j] = dis[i][k] + dis[i][k];
                            Next[i][j] = Next[i][k];
                        }
                    }
                }
            }
        }

        // If there's no path between 
        // node u and v, simply return 
        // an empty array 
        if (Next[start][end] == -1) 
            return "-1"; 
    
        // Storing the path in a vector 
        vector<int> path = { start }; 

        while (start != end) 
        { 
            start = Next[start][end]; 
            path.push_back(start); 
        } 

        string result;

        size_t n = path.size();

        for (size_t i = 0; i < n - 1; i++) 
            result += to_string(path[i]) + "->"; 

        result += to_string(path[n - 1]); 

        return result;
    }

    // bool hasCycleDFS(Graph g, size_t v, vector<bool>& visited, unordered_map<int,int>& parent, string& cycle)
    // {
    //     visited[v] = true;

    //     size_t i;

    //     for(i = 0; i < g.getGraph()[v].size(); i++)
    //     {
    //         int neighbor = g.getGraph()[v][i];

    //         if(!visited[static_cast<size_t>(neighbor)])
    //         {
    //             parent[neighbor] = v;

    //             if(hasCycleDFS(g, neighbor, visited, parent, cycle))
    //             {
    //                 cycle += to_string(v);
    //                 return true;
    //             }
    //         }
    //         else if(parent.find(v) != parent.end() && parent[v] != neighbor)
    //         {
    //             cycle += to_string(neighbor) + "->";

    //             int u = v;

    //             while(u != neighbor)
    //             {
    //                 cycle += to_string(u) + "->";
    //                 u = parent[u];
    //             }

    //             cycle += to_string(neighbor);

    //             return true;
    //         }
    //     }

    //     return false;
    // }

    // string isContainsCycle(Graph g) {

    //     vector<bool> visited(g.getGraph().size(), false);

    //     unordered_map<int,int> parent;

    //     string cycle;

    //     size_t i;

    //     for(i = 0; i < g.getGraph().size(); i++)
    //     {
    //         if(!visited[i])
    //         {
    //             if(hasCycleDFS(g, i, visited, parent, cycle))
    //             {
    //                 return cycle;
    //             }
    //         }
    //     }

    //     return "0";
    // }

    // bool ifBipartite(Graph g, size_t src, vector<int>& color) 
    // {
    //     queue<int> q;

    //     q.push(src);

    //     color[src] = 0; // Color the source node with 0

    //     while (!q.empty()) 
    //     {
    //         size_t u = q.front();
    //         q.pop();

    //         for (size_t v : g.getGraph()[u]) 
    //         {
    //             if (color[v] == -1) 
    //             {
    //                 color[v] = 1 - color[u]; // Color adjacent node with different color
    //                 q.push(v);
    //             } 
                
    //             else if (color[v] == color[u]) 
    //             {
    //                 return false; // If adjacent nodes have the same color, graph is not bipartite
    //             }
    //         }
    //     }
    //     return true;
    // }

    // string isBipartite(Graph g) {

    //     vector<int> color(g.getGraph().size(), -1); // Initialize color array, -1 indicates uncolored
    //     vector<vector<int>> bipartition(2);

    //     size_t i;

    //     for(i = 0; i < g.getGraph().size(); i++)
    //     {
    //         if(color[i] == -1)
    //         {
    //             if(!ifBipartite(g, i, color))
    //             {
    //                 return "0";
    //             }
    //         }

    //         // Cast the index to size_t
    //         bipartition[static_cast<size_t>(color[i])].push_back(static_cast<int>(i)); // Add node to appropriate partition based on color
    //     }

    //     string result;

    //     result += "The graph is bipartite: A = {";
    //     for (int node : bipartition[0]) {
    //         result += to_string(node) + ",";
    //     }

    //     result += "}, B = {";

    //     for (int node : bipartition[1]) {
    //         result += to_string(node) + ",";
    //     }

    //     result += "}";

    //     return result;
    // }

    vector<int> bellmanFord(Graph g, size_t V, size_t src)
    {
        vector<int> dist(V, numeric_limits<int>::max());
        vector<int> parent(V, -1);
        dist[src] = 0;

        size_t i, j, k;

        // Relax |V| - 1 times (if directed)
        for(k = 0; k < V - 1; k++)
        {
            for(i = 0; i < g.getGraph().size(); i++)
            {
                for(j = 0; j < g.getGraph()[0].size(); j++)
                {
                    if(dist[i] != numeric_limits<int>::max() && dist[i] + g.getGraph()[i][j] < dist[j])
                    {
                        dist[j] = dist[i] + g.getGraph()[i][j];
                        parent[j] = i;
                    }
                }
            }
        }


        for(i = 0; i < g.getGraph().size(); i++)
        {
            for(j = 0; j < g.getGraph()[0].size(); j++)
            {
                if(dist[i] != numeric_limits<int>::max() && dist[i] + g.getGraph()[i][j] < dist[j]) // Found a negative cycle
                {
                    vector<int> cycle;
                    size_t node = j;

                    for (int i = 0; i < V; i++) 
                    {
                        node = static_cast<size_t>(parent[node]);
                    }

                    size_t start = node;

                    do 
                    {
                        cycle.push_back(static_cast<int>(node));
                        node = static_cast<size_t>(parent[node]);
                    } while (node != start);

                    // while (node != start)
                    // {
                    //     cycle.push_back(node);
                    //     node = parent[node];
                    // }

                    cycle.push_back(static_cast<int>(start));

                    return cycle;
                }
            }
        }
        return {}; // No negative cycle found
    }


    string negativeCycle(Graph g) {

        size_t V = static_cast<size_t>(g.getVertexNum());

        vector<int> cycle = bellmanFord(g, V, 0);

        string result;

        if (cycle.empty()) 
        {
            return "No negative cycle found";
        } 

        else 
        {
            result += "Negative cycle found: ";
            for (int node : cycle) 
            {
                result += to_string(node) + "->";
            }
        }

        return result;
    }
}