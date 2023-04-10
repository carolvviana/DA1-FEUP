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

    Vertex *findVertex(const string &name) const;

    bool addVertex(const string &name,const string& district, const string& municipality, const string& township, const string& station_line);

    bool removeVertex(const string &name);

    bool addEdge(const string &source, const string &dest, double w, const string& service);

    std::vector<Vertex *> getVertexSet() const;

    /**
     * @brief Deletes memory allocated for the graph
     * Time Complexity: O(V * E)
     */
    void cleanGraph();

    /**
     * @brief Determine the maximum flow of a determined Graph, this also takes into consideration the maximum flow of the source vertex which may not be infinite
     * Time Complexity: O(V^2 * E)
     * @param source - Name of the source vertex
     * @param dest - Name of the destination vertex
     * @param maxSourceFlow - Maximum flow of the source vertex
     * @return
     */
    void maxFlow(const string& source, const string& dest, double maxSourceFlow);

    /**
     * @brief Finds the shortest path between two vertices, using an adpated version of BFS algorithm to take into consideration disabled edges or stations
     * Also takes into consideration the maximum flow of the source vertex
     * Time Complexity: O(V + E)
     * @param s Vertex* - Source vertex
     * @param t Vertex* - Destination vertex
     * @param maxSourceFlow Maximum flow of the source vertex
     * @return True if there is a path between the two vertices, false otherwise
     */
    bool path(Vertex* s, Vertex* t, double maxSourceFlow);

    /**
     * @brief Finds the bottleneck of a path
     * Time Complexity: O(V)
     * @param s Vertex* - Source vertex
     * @param t Vertex* - Destination vertex
     * @param maxSourceFlow Maximum flow of the source vertex
     * @return The bottleneck of the path
     */
    double findBottleneck(Vertex* s, Vertex* t, double maxSourceFlow);

    /**
     * @brief Augments the path between two vertices
     * Time Complexity: O(V)
     * @param s Vertex* - Source vertex
     * @param t Vertex* - Destination vertex
     * @param bottleneck - The bottleneck of the path
     */
    void augmentedPath(Vertex* s, Vertex* t, double bottleneck);

    std::vector<Vertex*> getInitialStops();
    std::vector<Vertex*> getFinalStops();
    void setInitialStops();
    void setFinalStops();

    /**
     * @brief Finds the shortest path between two stations
     * Time Complexity: O((V+E)log(V))
     * @param source Name of Station_A
     * @param dest Name of Station_B
     * @param max_flow Flow (Max number of trains that can travel between the two stations)
     * @param min_cost Flow cost (Cost of travel between the two stations)
     * @return True if a path has been found. False otherwise.
     */
    bool dijkstra(string& source, string& dest, int& max_flow, int& min_cost);

    /**
     * @brief Finds the maximum flow and the flow cost between two stations
     * Time Complexity: O((V+E)log(V))
     * @param source Name of Station_A
     * @param sink Name of Station_B
     * @param flow Flow (Max number of trains that can travel between the two stations)
     * @param cost Flow cost (Cost of travel between the two stations)
     * @return True if the dijkstra algorithm found a path. False otherwise.
     */
    bool max_flow_min_cost(string& source, string& sink, int& flow, int& cost);


protected:
    std::vector<Vertex *> vertexSet;    // vertex set
    std::vector<Vertex *> initialStops; // initial stops of the graph (those with no incoming edges)
    std::vector<Vertex *> finalStops;

    double ** distMatrix = nullptr;   // dist matrix for Floyd-Warshall
    int **pathMatrix = nullptr;   // path matrix for Floyd-Warshall


};

void deleteMatrix(int **m, int n);
void deleteMatrix(double **m, int n);

#endif /* DA_TP_CLASSES_GRAPH */