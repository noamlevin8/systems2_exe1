// ID: 326662574
// MAIL: noamlevin11@gmail.com

#include "Algorithms.hpp"

using namespace std;

namespace Algorithms {

    void dfs(Graph g, int v, vector<bool>& visited)
    {
        visited[v] = true;

        int i;

        for(i = 0; i < g.getGraph().size(); i++)
        {
            if(g.getGraph()[v][i] == 1 && !visited[i])
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

    vector<int> reconstructPath(int start, int end, vector<vector<int>>& shortest_graph) 
    {
        vector<int> path;
        int i;

        for (i = start; i != end; i = shortest_graph[i][end]) 
        {
            if (i == -1) 
            {
                return {}; // No path exists
            }

            path.push_back(i);
        }

        if (shortest_graph[start][end] == -1) 
        {
            return {}; // No path exists
        }

        path.push_back(end);

        return path;
    }

    string shortestPath(Graph g, int start, int end) {

        if(negativeCycle(g) == "1")
            return "-1";

        vector<vector<int>> shortest_graph;

        int i, j, k;

        for(i = 0; i < g.getGraph().size(); i++)
        {
            for(j = 0; j < g.getGraph()[0].size(); j++)
            {
                shortest_graph[i][j] = g.getGraph()[i][j];
            }
        }

        for(k = 0; k < g.getGraph().size(); k++)
        {
            for(i = 0; i < g.getGraph().size(); i++)
            {
                for(j = 0; j < g.getGraph()[0].size(); j++)
                {
                    if(shortest_graph[i][k] != 0 && shortest_graph[k][j] != 0)
                    {
                        if(shortest_graph[i][j] > (shortest_graph[i][k] + shortest_graph[i][k]) || shortest_graph[i][j] == 0)
                            shortest_graph[i][j] = shortest_graph[i][k] + shortest_graph[i][k];
                    }
                }
            }
        }

        vector<int> path = reconstructPath(start, end, shortest_graph);

        if(path.empty())
            return "-1";

        string result;

        for(int node : path)
        {
            result += to_string(node) + "->";
        }

        return result;
    }

    bool hasCycleDFS(Graph g, int v, vector<bool>& visited, unordered_map<int,int>& parent, string& cycle)
    {
        visited[v] = true;

        for(int neighbor : g.getGraph()[v])
        {
            if(!visited[neighbor])
            {
                parent[neighbor] = v; // Store the parent of neighbor

                if(hasCycleDFS(g, neighbor, visited, parent, cycle))
                {
                    cycle += to_string(v);
                    return true;
                }
            }
            else if(parent.find(v) != parent.end() && parent[v] != neighbor)
            {
                cycle += to_string(neighbor) + "->";

                int u = v;

                while(u != neighbor)
                {
                    cycle += to_string(u) + "->";
                    u = parent[u];
                }

                cycle += to_string(neighbor);

                return true;
            }
        }

        return false;
    }

    string isContainsCycle(Graph g) {

        vector<bool> visited(g.getGraph().size(), false);

        unordered_map<int,int> parent;

        string cycle;

        int i;

        for(i = 0; i < g.getGraph().size(); i++)
        {
            if(!visited[i])
            {
                if(hasCycleDFS(g, i, visited, parent, cycle))
                {
                    return cycle + "\n";
                }
            }
        }

        return "0";
    }

    bool ifBipartite(Graph g, int src, vector<int>& color) 
    {
        queue<int> q;

        q.push(src);

        color[src] = 0; // Color the source node with 0

        while (!q.empty()) 
        {
            int u = q.front();
            q.pop();

            for (int v : g.getGraph()[u]) 
            {
                if (color[v] == -1) 
                {
                    color[v] = 1 - color[u]; // Color adjacent node with different color
                    q.push(v);
                } 
                
                else if (color[v] == color[u]) 
                {
                    return false; // If adjacent nodes have the same color, graph is not bipartite
                }
            }
        }
        return true;
}

    string isBipartite(Graph g) {

        vector<int> color(g.getGraph().size(), -1); // Initialize color array, -1 indicates uncolored
        vector<vector<int>> bipartition(2);

        int i;

        for(i = 0; i < g.getGraph().size(); i++)
        {
            if(color[i] == -1)
            {
                if(!ifBipartite(g, i, color))
                {
                    return "0";
                }
            }

            bipartition[color[i]].push_back(i); // Add node to appropriate partition based on color
        }

        string result;

        result += "The graph is bipartite: A = {";
        for (int node : bipartition[0]) {
            result += to_string(node) + ",";
        }

        result += "}, B = {";

        for (int node : bipartition[1]) {
            result += to_string(node) + ",";
        }

        result += "}";

        return result;
    }

    vector<int> bellmanFord(Graph g, int V, int src)
    {
        vector<int> dist(V, numeric_limits<int>::max());
        vector<int> parent(V, -1);
        dist[src] = 0;

        int i, j, k;

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
                    int node = j;

                    for (int i = 0; i < V; i++) 
                    {
                        node = parent[node];
                    }

                    int start = node;

                    do 
                    {
                        cycle.push_back(node);
                        node = parent[node];
                    } while (node != start);

                    // while (node != start)
                    // {
                    //     cycle.push_back(node);
                    //     node = parent[node];
                    // }

                    cycle.push_back(start);

                    return cycle;
                }
            }
        }

        return {}; // No negative cycle found
    }


    string negativeCycle(Graph g) {

        int V = g.getVertexNum();

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