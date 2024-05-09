// ID: 326662574
// MAIL: noamlevin11@gmail.com

#include "Graph.hpp"

using namespace std;
using namespace ariel;

void Graph::loadGraph(vector<vector<int>> new_graph, int directed) {

    if(new_graph.size() != new_graph[0].size())
        throw invalid_argument("Invalid graph: The graph is not a square matrix.");

    graph = new_graph;
    vertex_num = new_graph.size();
    if_directed = directed;

    size_t i, j;
    size_t count = 0;

    for(i = 0; i < new_graph.size(); i++)
    {
        for(j = 0; j < new_graph[0].size(); j++)
        {
            if(new_graph[i][j] != 0)
                count++;
        }
    }

    if(!directed)
        edge_num = count/2;
    else
        edge_num = count;
}

void Graph::printGraph() {
        cout << "Graph with " << vertex_num << " vertices and " << edge_num << " edges." << endl;
}

vector<vector<int>> Graph::getGraph()
{
    return graph;
}

size_t Graph::getVertexNum()
{
    return vertex_num;
}

size_t Graph::getEdgeNum()
{
    return edge_num;
}

int Graph::getIfDirected()
{
    return if_directed;
}