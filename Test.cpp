// ID: 326662574
// MAIL: noamlevin11@gmail.com

#include "doctest.h"
#include "Algorithms.hpp"
#include "Graph.hpp"

using namespace std;

TEST_CASE("Test isConnected")
{
    ariel::Graph g;
    vector<vector<int>> graph1 = { // Undirected connected graph
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph1, 0);
    CHECK(Algorithms::isConnected(g) == "1");

    vector<vector<int>> graph2 = { // Undirected unconnected graph
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph2, 0);
    CHECK(Algorithms::isConnected(g) == "0");

    vector<vector<int>> graph3 = { // Directed graph without strong connectivity
        {0, 1, 1},
        {0, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph3, 1);
    CHECK(Algorithms::isConnected(g) == "0");

    vector<vector<int>> graph4 = { // Directed graph with strong connectivity
        {0, 1, 0},
        {0, 0, 1},
        {1, 0, 0}};
    g.loadGraph(graph4, 1);
    CHECK(Algorithms::isConnected(g) == "1");

}

TEST_CASE("Test shortestPath")
{
    ariel::Graph g;
    vector<vector<int>> graph1 = { // Undirected graph with a path
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph1, 0);
    CHECK(Algorithms::shortestPath(g, 0, 2) == "0->1->2");

    CHECK_THROWS(Algorithms::shortestPath(g, 0, 3)); // Invalid end index

    vector<vector<int>> graph2 = { // Undirected graph without a path
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph2, 0);
    CHECK(Algorithms::shortestPath(g, 0, 4) == "-1");

    vector<vector<int>> graph3 = { // Directed graph with a path (working with negative and non-negative weights)
        {0, 1, 0, 2},
        {0, 0, 1, 0},
        {0, 0, 0, -1},
        {0, 0, 0, 0}};
    g.loadGraph(graph3, 1);
    CHECK(Algorithms::shortestPath(g, 0, 3) == "0->1->2->3"); 

    vector<vector<int>> graph4 = { // Directed graph with a path (Negative cycle)
        {0, 0, -2, 0, 0},
        {0, 0, 0, 5, 2},
        {1, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, -1, 0}};
    g.loadGraph(graph4, 1);
    CHECK(Algorithms::shortestPath(g, 1, 3) == "1->4->3");

    vector<vector<int>> graph5 = { // Directed graph without a path (Negative cycle)
        {0, 1, 0},
        {1, 0, 1},
        {-3, 0, 0}};
    g.loadGraph(graph5, 1);
    CHECK(Algorithms::shortestPath(g, 0, 2) == "-1");

    vector<vector<int>> graph6 = { // Undirected graph with a path (Negative cycle)
        {0, 1, 0, 1},
        {1, 0, 1, 0},
        {0, 1, 0, -3},
        {1, 0, -3, 0}};
    g.loadGraph(graph6, 0);
    CHECK(Algorithms::shortestPath(g, 0, 3) == "0->1->2->3");

    vector<vector<int>> graph7 = { // Undirected graph without a path (Negative cycle)
        {0, -2, 1, 0},
        {-2, 0, -1, 0},
        {1, -1, 0, 0},
        {0, 0, 0, 0}};
    g.loadGraph(graph7, 0);
    CHECK(Algorithms::shortestPath(g, 0, 2) == "-1");

    vector<vector<int>> graph8 = { // Shortest path = 0
        {0, 1, 0, 1},
        {1, 0, 1, 0},
        {0, 1, 0, -2},
        {1, 0, -2, 0}};
    g.loadGraph(graph8, 0);
    CHECK(Algorithms::shortestPath(g, 0, 3) == "0->1->2->3");
}

TEST_CASE("Test isContainsCycle")
{
    ariel::Graph g;
    vector<vector<int>> graph1 = { // Undirected graph without a cycle
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph1, 0);
    CHECK(Algorithms::isContainsCycle(g) == "0");

    vector<vector<int>> graph2 = { // Undirected graph with a cycle
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph2, 0);
    CHECK(Algorithms::isContainsCycle(g) == "The cycle is: 0->1->2->0");

    vector<vector<int>> graph3 = { // Directed graph without a cycle
        {0, 0, -1},
        {0, 0, 2},
        {0, 0, 0}};
    g.loadGraph(graph3, 1);
    CHECK(Algorithms::isContainsCycle(g) == "0");

    vector<vector<int>> graph4 = { // Directed graph with a cycle
        {0, 0, 0},
        {0, 0, -20},
        {0, 5, 0}};
    g.loadGraph(graph4, 1);
    CHECK(Algorithms::isContainsCycle(g) == "The cycle is: 1->2->1");

    vector<vector<int>> graph5 = { // Directed graph with negative cycle
        {0, 0, 1},
        {-5, 0, 0},
        {0, 2, 0}};
    g.loadGraph(graph5, 1);
    CHECK(Algorithms::isContainsCycle(g) == "The cycle is: 0->2->1->0");
}

TEST_CASE("Test isBipartite")
{
    ariel::Graph g;
    vector<vector<int>> graph1 = { // Undirected bipartite graph
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph1, 0);
    CHECK(Algorithms::isBipartite(g) == "The graph is bipartite: A={0, 2}, B={1}");

    vector<vector<int>> graph2 = { // Undirected non-bipartite graph
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph2, 0);
    CHECK(Algorithms::isBipartite(g) == "0");

    vector<vector<int>> graph3 = { // Directed bipatite graph
        {0, 1, 0, 0, 0},
        {0, 0, 3, 0, 0},
        {0, 0, 0, 4, 0},
        {0, 0, 0, 0, 7},
        {0, 2, 0, 0, 0}};
    g.loadGraph(graph3, 1);
    CHECK(Algorithms::isBipartite(g) == "The graph is bipartite: A={0, 2, 4}, B={1, 3}");

    vector<vector<int>> graph4 = { // Directed non-bipatite graph
        {0, 1, 0, 0, 0},
        {0, 0, 3, 0, 0},
        {0, 0, 0, 4, 0},
        {0, 0, 0, 0, 7},
        {2, 0, 0, 0, 0}};
    g.loadGraph(graph4, 1);
    CHECK(Algorithms::isBipartite(g) == "0");
}

TEST_CASE("Test NegativeCycle")
{
    ariel::Graph g;
    vector<vector<int>> graph1 = { // Directed graph with a negative cycle
        {0, 0, 0, 1, 0},
        {-3, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 1, 0, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph1, 1);
    CHECK(Algorithms::negativeCycle(g) == "Negative cycle found: 0->3->1->0");

    vector<vector<int>> graph2 = { // Directed graph without a negative cycle
        {0, -1, 2, 0},
        {0, 0, 0, -1},
        {0, 0, 0, -1},
        {0, 0, 0, 0}};
    g.loadGraph(graph2, 1);
    CHECK(Algorithms::negativeCycle(g) == "No negative cycle found");
    
    vector<vector<int>> graph3 = { // Undirected graph without a negative cycle
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph3, 0);
    CHECK(Algorithms::negativeCycle(g) == "No negative cycle found");

    vector<vector<int>> graph4 = { // Undirected graph with a negative cycle
        {0, -1, 0, 4},
        {-1, 0, 3, 0},
        {0, 3, 0, -7},
        {4, 0, -7, 0}};
    g.loadGraph(graph4, 0);
    CHECK(Algorithms::negativeCycle(g) == "Negative cycle found: 0->1->2->3->0");
}

TEST_CASE("Test invalid graph")
{
    ariel::Graph g;
    vector<vector<int>> graph1 = { // Invalid size (not a square matrix)
        {0, 1, 2, 0},
        {1, 0, 3, 0},
        {2, 3, 0, 4},
        {0, 0, 4, 0},
        {0, 0, 0, 5}};
    CHECK_THROWS(g.loadGraph(graph1, 1));

    vector<vector<int>> graph2 = { // Invalid self edge
        {0, 1, 1},
        {1, 1, 1},
        {1, 1, 0}};
    CHECK_THROWS(g.loadGraph(graph2, 0));

    vector<vector<int>> graph3 = { // Invalid undirected graph
        {0, 1, 0},
        {1, 0, 1},
        {0, 0, 0}};
    CHECK_THROWS(g.loadGraph(graph3, 0));
}