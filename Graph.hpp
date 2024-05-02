// ID: 326662574
// MAIL: noamlevin11@gmail.com

#include <iostream>
#include <vector>

class Graph {

private:
        vector<vector<int>> graph;
        int vertex_num;
        int edge_num;

public:
        void loadGraph(vector<vector<int>> graph);
        void printGraph();

        Graph()
        {
                fill(graph.begin(), graph.end(), 0);
                vertex_num = 0;
                edge_num = 0;
        }
};