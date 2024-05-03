// ID: 326662574
// MAIL: noamlevin11@gmail.com

#include "Graph.hpp"

using namespace std;
using namespace ariel;

void Graph::loadGraph(vector<vector<int>> new_graph, int directed) {
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
        
        if(!directed)
            edge_num = count/2;
        else
            edge_num = count;
        
        if_directed = directed;
    }

    else
    {
        throw invalid_argument("Invalid graph: The graph is not a square matrix.");
    }
}

void Graph::printGraph() {
        cout << "Graph with " << vertex_num << "vertices and " << edge_num << "edges.\n" << endl;
}

vector<vector<int>> Graph::getGraph()
{
    return graph;
}

int Graph::getVertexNum()
{
    return vertex_num;
}

int Graph::getEdgeNum()
{
    return edge_num;
}

int Graph::getIfDirected()
{
    return if_directed;
}