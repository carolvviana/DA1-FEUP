// By: Gonçalo Leão

#ifndef DA_TP_CLASSES_VERTEX_EDGE
#define DA_TP_CLASSES_VERTEX_EDGE

#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>
//#include "../data_structures/MutablePriorityQueue.h"
#include <string>

class Edge;

using namespace std;

#define INF std::numeric_limits<double>::max()

/************************* Vertex  **************************/

class Vertex {
public:
    Vertex(string name, string district, string municipality, string township, string station_line);
    bool operator<(Vertex & vertex) const; // // required by MutablePriorityQueue

    std::string getName() const;
    std::vector<Edge *> getAdj() const;
    bool isVisited() const;

    double getDist() const;
    Edge *getPath() const;

    Edge* getPrev() const;
    std::vector<Edge *> getIncoming() const;
    bool isEnabled() const;

    void setVisited(bool visited);
    void setDist(double dist);
    void setPath(Edge *path);
    void setPrev(Edge *edge);
    Edge * addEdge(Vertex *dest, double w, string service);
    void setEnabled(bool enabled);
    bool disableEdge(const string& destName);

    struct CompareVertexPointers {
        bool operator()(const Vertex* v1, const Vertex* v2) {
            return v1->dist > v2->dist;
        }
    };

    string getMunicipality() const;
    string getDistrict() const;


protected:

    string name;
    string district;
    string municipality;
    string township;
    string station_line;
    bool enabled = true;

    std::vector<Edge *> adj;  // outgoing edges

    // auxiliary fields
    bool visited = false; // used by DFS, BFS, Prim ...
    bool processing = false; // used by isDAG (in addition to the visited attribute)
    unsigned int indegree; // used by topsort
    double dist = 0;
    double cost = 0;
    Edge *prev = nullptr;
    Edge *path = nullptr;

    std::vector<Edge *> incoming; // incoming edges

    //int queueIndex = 0; 		// required by MutablePriorityQueue and UFDS
};

/********************** Edge  ****************************/

class Edge {
public:
    Edge(Vertex *orig, Vertex *dest, double w, string service);

    Vertex * getDest() const;
    double getWeight() const;
    string getService() const;
    Vertex * getOrig() const;
    double getFlow() const;
    bool isEnabled() const;
    void setReverse(Edge *reverse);
    void setFlow(double flow);
    void setEnabled(bool enabled);

protected:
    Vertex * dest; // destination vertex

    string service; // type of service

    double weight; // edge weight, can also be used for capacity

    // auxiliary fields
    bool selected = false;
    bool enabled = true;

    // used for bidirectional edges
    Vertex *orig = nullptr;
    Edge *reverse = nullptr;

    double flow; // for flow-related problems
    double cost;
};

#endif /* DA_TP_CLASSES_VERTEX_EDGE */