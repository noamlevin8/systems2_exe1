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

        if(start >= g.getVertexNum() || end >= g.getVertexNum())
            throw invalid_argument("Invalid vertex: start/end out of range.");

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
                if(!g.getIfDirected() && parent[j] == i)
                    continue;

                if(dist[i] != numeric_limits<int>::max() && g.getGraph()[i][j] != 0 && dist[i] + g.getGraph()[i][j] < dist[j]) // Found a negative cycle
                {
                    return "-1";
                }
            }
        }

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

    string isBipartite(Graph g) {

        vector<int> parent (g.getVertexNum(), -1);
        vector<string> color (g.getVertexNum(), "white");
        queue<size_t> q;
        size_t u, v;

        color[0] = "blue";
        q.push(0);

        while(!q.empty())
        {
            u = q.front();
            q.pop();

            for(v = 0; v < g.getVertexNum(); v++)
            {
                if(g.getGraph()[u][v] != 0)
                {
                    if(parent[u] == v)
                        continue;

                    if(color[v] == color[u])
                        return "0";
                    
                    if(color[v] == "white")
                    {
                        parent[v] = u;

                        if(color[u] == "blue")
                            color[v] = "red";

                        else
                            color[v] = "blue";
                        
                       q.push(v); 
                    }
                }
            }
        }

        string a, b;

        a = "A={";
        b = "B={";

        for(v = 0; v < g.getVertexNum(); v++)
        {
            if(color[v] == "blue")
            {
                if(a == "A={")
                    a += to_string(v);

                else
                    a += ", " + to_string(v);
            }

            else
            {
                if(b == "B={")
                    b += to_string(v);

                else
                    b += ", " + to_string(v);
            }
        }

        a += "}";
        b += "}";

        return "The graph is bipartite: " + a + ", " + b;
    }

    string bellmanFord(Graph g, size_t V, size_t src)
    {
        vector<int> dist(V, numeric_limits<int>::max());
        vector<int> parent(V, -1);
        dist[src] = 0;

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

        for(i = 0; i < V; i++)
        {
            for(j = 0; j < V; j++)
            {
                // if(!g.getIfDirected() && parent[j] == i)
                //     continue;

                if(dist[i] != numeric_limits<int>::max() && g.getGraph()[i][j] != 0 && dist[i] + g.getGraph()[i][j] < dist[j]) // Found a negative cycle
                {
                    //parent[j] = i;

                    string path;

                    path = to_string(i);

                    size_t node = static_cast<size_t>(parent[i]);

                    while(node != i)
                    {
                        path = to_string(node) + "->" + path;
                        node = static_cast<size_t>(parent[node]);
                    }
                    
                    path = to_string(i) + "->" + path;

                    return "Negative cycle found: " + path;
                }
            }
        }
        return "No negative cycle found";
    }


    string negativeCycle(Graph g) {

        size_t V = static_cast<size_t>(g.getVertexNum());

        return bellmanFord(g, V, 0);
    }
}