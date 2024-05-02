// ID: 326662574
// MAIL: noamlevin11@gmail.com

using namespace std;

#include "Graph.hpp"

void Graph::loadGraph(vector<vector<int>> new_graph) {
    if(graph.size() == graph[0].size())
    {
        graph = new_graph;
        vertex_num = new_graph.size();

        int count = 0, i, j;

        for(i = 0; i < new_graph.size(); i++)
        {
            for(j = 0; j < new_graph[0].size(); j++)
            {
                if(new_graph[i][j] > 0)
                    count++;
            }
        }

        edge_num = count;
    }

    else
    {
        throw std::invalid_argument("Invalid graph: The graph is not a square matrix.");
    }
}

void Graph::printGraph() {
        
}