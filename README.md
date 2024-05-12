# README

## System Programming 2 - Task 1


In this project, I've created a namespace named `ariel`, within which I've defined the class `Graph`.

### Graph Class

The `Graph` class is characterized by two files (`Graph.hpp`, `Graph.cpp`).

#### Graph.hpp

In the header file of the class, I've defined 4 fields:

1. `graph`: Holds the adjacency matrix that characterizes the graph.
2. `vertex_num`: Holds the number of vertices in the graph.
3. `edge_num`: Holds the number of edges in the graph.
4. `if_directed`: Indicates whether the graph is directed or undirected (by 0 and 1).

Additionally, I've defined 6 functions (4 get functions for the fields):

1. `loadGraph`: A function that takes an adjacency matrix and a number indicating whether the graph is directed or not. The function inserts the adjacency matrix into the `graph` field of my graph and updates the `if_directed` field according to the received number.
2. `print_Graph`: A function that prints the number of vertices and edges in the graph.

#### Graph.cpp

In this file, the implementation of the functions defined in `Graph.hpp` resides.


#### Algorithms Namespace

I've also created a namespace named `Algorithms`, within which there are 5 main functions and 3 additional helper functions.

#### Algorithms.hpp

In the header file of the `Algorithms` namespace, I've defined 8 functions:

1. `isConnected`: A function that takes a `Graph` object and returns 1 if it represents a graph with strong connectivity or 0 if it does not.
2. `shortestPath`: A function that takes a `Graph` object, and two starting and ending vertices. The function returns the order of vertices representing the shortest path if it exists, and returns -1 if there is no path.
3. `isContainsCycle`: A function that takes a `Graph` object. The function returns the order of vertices representing the cycle if one exists, and returns 0 if there is no cycle in the graph.
4. `isBipartite`: A function that takes a `Graph` object. The function returns the division of the graph into two sets if possible, and returns 0 if such a division does not exist.
5. `negativeCycle`: A function that takes a `Graph` object. The function returns the order of vertices representing the negative cycle in the graph if one exists, and returns a string indicating that there is no negative cycle if there is no negative cycle in the graph.
6. `dfs`: A helper function for the `isConnected` function, implementing the DFS algorithm.
7. `DFSVisit`: A helper function for the `isContainsCycle` function, implementing part of the DFS algorithm.
8. `bellmanFord`: A helper function for the `negativeCycle` function, implementing the Bellman Ford algorithm.

#### Algorithms.cpp

This file contains the implementation of all the functions defined in `Algorithms.hpp`.


### Additional Files

`Demo.cpp`, `Test.cpp` - Files containing tests for our code.
