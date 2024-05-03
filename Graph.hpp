// ID: 326662574
// MAIL: noamlevin11@gmail.com

#include <iostream>
#include <vector>

namespace ariel {

        class Graph {

        private:
                vector<vector<int>> graph;
                int vertex_num;
                int edge_num;
                int if_directed; // 1 - if directed, 0 - if not

        public:
                void loadGraph(vector<vector<int>> graph, int directed);
                void printGraph();

                vector<vector<int>> getGraph();
                int getVertexNum();
                int getEdgeNum();
                int getIfDirected();                

                Graph()
                {
                        fill(graph.begin(), graph.end(), 0);
                        vertex_num = 0;
                        edge_num = 0;
                        if_directed = 0;
                }
        };
}