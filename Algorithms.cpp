// ID: 326662574
// MAIL: noamlevin11@gmail.com

#include "Algorithms.hpp"

using namespace std;

namespace Algorithms {

    void dfs(Graph g, size_t v, vector<bool>& visited)
    {
        visited[v] = true;

        size_t i;

        for(i = 0; i < g.getVertexNum(); i++)
        {
            if(g.getGraph()[v][i] != 0 && !visited[i])
            {
                dfs(g, i, visited);
            }
        }
    }

    string isConnected(Graph g) {
        
        size_t i;

        for(i = 0; i < g.getVertexNum(); i++)
        {
            // Doing DFS from the vertex i
            vector<bool> visited(g.getVertexNum(),false);
            dfs(g, i, visited);

            // Checking if all the vertices are visited
            for(bool v : visited)
            {
                if(!v)
                    return "0";
            }
        }

        return "1";
    }

    string shortestPath(Graph g, size_t start, size_t end) { // Negative cycle

        // if(negativeCycle(g) != "No negative cycle found")
        //     return "-1";

        size_t V = g.getVertexNum();
        vector<int> dist(V, numeric_limits<int>::max());
        vector<int> parent(V, -1);
        dist[start] = 0;

        size_t i, j, k;

        // Relax |V| - 1 times
        for(k = 0; k < V - 1; k++)
        {
            for(i = 0; i < V; i++)
            {
                for(j = 0; j < V; j++)
                {
                    if(dist[i] != numeric_limits<int>::max() && g.getGraph()[i][j] != 0 && dist[i] + g.getGraph()[i][j] < dist[j])
                    {
                        dist[j] = dist[i] + g.getGraph()[i][j];
                        parent[j] = i;
                    }
                }
            }
        }

        if(dist[end] == numeric_limits<int>::max())
            return "-1";
        
        // Check for a negative cycle
        for(i = 0; i < V; i++)
        {
            for(j = 0; j < V; j++)
            {
                if(dist[i] != numeric_limits<int>::max() && g.getGraph()[i][j] != 0 && dist[i] + g.getGraph()[i][j] < dist[j]) // Found a negative cycle
                {
                    return "-1";
                }
            }
        }

        // cout << "dist:";
        // for(i = 0; i < V; i++)
        // {
        //     cout << " " << i << " - " << dist[i] << ",";
        // }
        // cout << endl;


        string path;

        path = to_string(end);

        i = static_cast<size_t>(parent[end]);

        while(i != start)
        {
            path = to_string(i) + "->" + path;
            i = static_cast<size_t>(parent[i]);
        }
        
        path = to_string(start) + "->" + path;

        return path;
    }


    int DFSVisit(Graph g, size_t u, vector<string> color, vector<int>& parent)
    {
        color[u] = "gray";

        size_t i;
        int result = -1;

        for(i = 0; i < g.getVertexNum(); i++)
        {
            if(u != i && g.getGraph()[u][i] != 0)
            {
                if(!g.getIfDirected() && parent[u] == i)
                    continue;

                if(color[i] == "white")
                {
                    parent[i] = u;
                    result = DFSVisit(g, i, color, parent);

                    if(result != -1)
                        break;
                }
                else if(color[i] == "gray")
                {
                    parent[i] = u;
                    return i;
                }
            }
        }
        color[u] = "black";
        
        return result;
    }


    string isContainsCycle(Graph g) {

        vector<string> color(g.getVertexNum(), "white");
        vector<int> parent(g.getVertexNum(), -1);
    
        size_t i;
        int j;
        int result;

        for(i = 0; i < g.getVertexNum(); i++)
        {
            if(color[i] == "white")
                result = DFSVisit(g, i, color, parent);

            if(result != -1)
            {
                string path;

                path = to_string(result);

                j = parent[static_cast<size_t>(result)];

                while(j != result)
                {
                    path = to_string(j) + "->" + path;
                    j = parent[static_cast<size_t>(j)];
                }
                
                path = to_string(result) + "->" + path;

                return "The cycle is: " + path;
            }
        }

        return "0";
    }

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

    string bellmanFord(Graph g, size_t V, size_t src)
    {
        vector<int> dist(V, numeric_limits<int>::max());
        vector<int> parent(V, -1);
        dist[src] = 0;

        size_t i, j, k;

        // Relax |V| - 1 times (if directed)
        for(k = 0; k < V - 1; k++)
        {
            for(i = 0; i < V; i++)
            {
                for(j = 0; j < V; j++)
                {
                    //cout << "test dist: " << i << " - " << dist[i] << endl;
                    if(dist[i] != numeric_limits<int>::max() && g.getGraph()[i][j] != 0 && dist[i] + g.getGraph()[i][j] < dist[j])
                    {
                        dist[j] = dist[i] + g.getGraph()[i][j];
                        parent[j] = i;
                    }
                }
            }
        }

        for(i = 0; i < V; i++)
        {
            for(j = 0; j < V; j++)
            {
                if(dist[i] != numeric_limits<int>::max() && g.getGraph()[i][j] != 0 && dist[i] + g.getGraph()[i][j] < dist[j]) // Found a negative cycle
                {
                    string path;

                    path = to_string(j);

                    size_t node = static_cast<size_t>(parent[j]);

                    while(i != j)
                    {
                        path = to_string(i) + "->" + path;
                        node = static_cast<size_t>(parent[node]);
                    }
                    
                    path = to_string(j) + "->" + path;

                    return path;

                    // vector<int> cycle;
                    // size_t node = j;

                    // for (int i = 0; i < V; i++) 
                    // {
                    //     node = static_cast<size_t>(parent[node]);
                    // }

                    // size_t start = node;

                    // do 
                    // {
                    //     cycle.push_back(static_cast<int>(node));
                    //     node = static_cast<size_t>(parent[node]);
                    // } while (node != start);

                    // // // while (node != start)
                    // // // {
                    // // //     cycle.push_back(node);
                    // // //     node = parent[node];
                    // // // }

                    // cycle.push_back(static_cast<int>(start));

                    // return cycle;
                }
            }
        }
        return "No negative cycle found"; // No negative cycle found
    }


    string negativeCycle(Graph g) {

        size_t V = static_cast<size_t>(g.getVertexNum());

        return bellmanFord(g, V, 0);

        // string result;

        // if (cycle.empty()) 
        // {
        //     return "No negative cycle found";
        // } 

        // else 
        // {
        //     result += "Negative cycle found: ";
        //     for (int node : cycle) 
        //     {
        //         result += to_string(node) + "->";
        //     }
        // }

    }
}