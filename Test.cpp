#include "doctest.h"
#include "Algorithms.hpp"
#include "Graph.hpp"

using namespace std;

TEST_CASE("Test isConnected")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph, 1);
    CHECK(Algorithms::isConnected(g) == "1");

    vector<vector<int>> graph2 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph2, 1);
    CHECK(Algorithms::isConnected(g) == "0");
}

TEST_CASE("Test shortestPath")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph, 1);
    CHECK(Algorithms::shortestPath(g, 0, 2) == "0->1->2");

    vector<vector<int>> graph2 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph2, 1);
    CHECK(Algorithms::shortestPath(g, 0, 4) == "-1");
}
// TEST_CASE("Test isContainsCycle")
// {
//     ariel::Graph g;
//     vector<vector<int>> graph = {
//         {0, 1, 0},
//         {1, 0, 1},
//         {0, 1, 0}};
//     g.loadGraph(graph, 1);
//     CHECK(Algorithms::isContainsCycle(g) == "0");

//     vector<vector<int>> graph2 = {
//         {0, 1, 1, 0, 0},
//         {1, 0, 1, 0, 0},
//         {1, 1, 0, 1, 0},
//         {0, 0, 1, 0, 0},
//         {0, 0, 0, 0, 0}};
//     g.loadGraph(graph2, 1);
//     CHECK(Algorithms::isContainsCycle(g) == "1");
// }
// TEST_CASE("Test isBipartite")
// {
//     ariel::Graph g;
//     vector<vector<int>> graph = {
//         {0, 1, 0},
//         {1, 0, 1},
//         {0, 1, 0}};
//     g.loadGraph(graph, 1);
//     CHECK(Algorithms::isBipartite(g) == "The graph is bipartite: A={0, 2}, B={1}");

//     vector<vector<int>> graph2 = {
//         {0, 1, 1, 0, 0},
//         {1, 0, 1, 0, 0},
//         {1, 1, 0, 1, 0},
//         {0, 0, 1, 0, 0},
//         {0, 0, 0, 0, 0}};
//     g.loadGraph(graph2, 1);
//     CHECK(Algorithms::isBipartite(g) == "0");

//     vector<vector<int>> graph3 = {
//         {0, 1, 0, 0, 0},
//         {1, 0, 3, 0, 0},
//         {0, 3, 0, 4, 0},
//         {0, 0, 4, 0, 5},
//         {0, 0, 0, 5, 0}};
//     g.loadGraph(graph3, 1);
//     CHECK(Algorithms::isBipartite(g) == "The graph is bipartite: A={0, 2, 4}, B={1, 3}");
// }

TEST_CASE("Test NegativeCycle")
{
    ariel::Graph g;
    vector<vector<int>> graph4 = {
        {0, 0, 0, 1, 0},
        {-3, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 1, 0, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph4, 1);
    CHECK(Algorithms::negativeCycle(g) == "Negative cycle found: 0->1->3->0->");
    
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph, 0);
    CHECK(Algorithms::negativeCycle(g) == "No negative cycle found");

    vector<vector<int>> graph5 = {
        {0, -1, 2, 0},
        {0, 0, 0, -1},
        {0, 0, 0, -1},
        {0, 0, 0, 0}};
    g.loadGraph(graph5, 1);
    CHECK(Algorithms::negativeCycle(g) == "No negative cycle found");
}

TEST_CASE("Test invalid graph")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 2, 0},
        {1, 0, 3, 0},
        {2, 3, 0, 4},
        {0, 0, 4, 0},
        {0, 0, 0, 5}};
    CHECK_THROWS(g.loadGraph(graph, 1));
}