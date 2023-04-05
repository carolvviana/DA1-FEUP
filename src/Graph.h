// By: Gonçalo Leão

#ifndef DA_TP_CLASSES_GRAPH
#define DA_TP_CLASSES_GRAPH

#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>
#include <unordered_set>
#include <stack>

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

    bool removeVertex(const string &name);

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
     * @brief Determine the maximum flow of a determined Graph, this also takes into consideration the maximum flow of the source vertex which may not be infinite
     * @param source - Name of the source vertex
     * @param dest - Name of the destination vertex
     * @param maxSourceFlow - Maximum flow of the source vertex
     * @return
     */
    void maxFlow(const string& source, const string& dest, double maxSourceFlow);
    bool path(Vertex* s, Vertex* t, double maxSourceFlow);
    double findBottleneck(Vertex* s, Vertex* t, double maxSourceFlow);
    void augmentedPath(Vertex* s, Vertex* t, double bottleneck);
    std::vector<Vertex*> getInitialStops();

    bool dijkstra(string& source, string& dest, int& max_flow, int& min_cost);
    bool max_flow_min_cost(string& source, string& sink, int& flow, int& cost);


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