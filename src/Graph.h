// By: Gonçalo Leão

#ifndef DA_TP_CLASSES_GRAPH
#define DA_TP_CLASSES_GRAPH

#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>
//#include "../data_structures/MutablePriorityQueue.h"

#include "VertexEdge.h"

class Graph {
public:
    ~Graph();
    /*
    * Auxiliary function to find a vertex with a given ID.
    */
    Vertex *findVertex(const string &name) const;
    /*
     *  Adds a vertex with a given content or info (in) to a graph (this).
     *  Returns true if successful, and false if a vertex with that content already exists.
     */
    bool addVertex(const string &name,const string& district, const string& municipality, const string& township, const string& station_line);

    /*
     * Adds an edge to a graph (this), given the contents of the source and
     * destination vertices and the edge weight (w).
     * Returns true if successful, and false if the source or destination vertex does not exist.
     */
    bool addEdge(const string &source, const string &dest, double w, const string& service);
    bool addBidirectionalEdge(const string &source, const string &dest, double w, const string& service);

    int getNumVertex() const;
    std::vector<Vertex *> getVertexSet() const;

    void cleanGraph();


    /**
     * @brief Determine the maximum flow of a determined Graph
     * @return
     */
    void maxFlow(string& source, string& dest);
    bool path(string& source, string& dest);
    double findBottleneck(string& dest);
    void augmentedPath(string& dest, double bottleneck);

protected:
    std::vector<Vertex *> vertexSet;    // vertex set

    double ** distMatrix = nullptr;   // dist matrix for Floyd-Warshall
    int **pathMatrix = nullptr;   // path matrix for Floyd-Warshall

    /*
     * Finds the index of the vertex with a given content.
     */
    int findVertexIdx(const string &id) const;
};

void deleteMatrix(int **m, int n);
void deleteMatrix(double **m, int n);

#endif /* DA_TP_CLASSES_GRAPH */