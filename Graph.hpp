// ID: 326662574
// MAIL: noamlevin11@gmail.com

#pragma once

#include <iostream>
#include <vector>

using namespace std;

namespace ariel {

        class Graph {

        private:
                vector<vector<int>> graph;
                size_t vertex_num;
                size_t edge_num;
                int if_directed; // 1 - if directed, 0 - if not

        public:
                void loadGraph(vector<vector<int>> graph, int directed);
                void printGraph();

                vector<vector<int>> getGraph();
                size_t getVertexNum();
                size_t getEdgeNum();
                int getIfDirected();                

                Graph()
                {
                        //fill(graph.begin(), graph.end(), 0);
                        graph = {};
                        vertex_num = 0;
                        edge_num = 0;
                        if_directed = 0;
                }
        };
}