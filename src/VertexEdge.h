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
    bool isProcessing() const;
    unsigned int getIndegree() const;
    double getDist() const;
    Edge *getPath() const;
    double getCost() const;
    Edge* getPrev() const;
    std::vector<Edge *> getIncoming() const;

    void setVisited(bool visited);
    void setProcesssing(bool processing);
    void setIndegree(unsigned int indegree);
    void setDist(double dist);
    void setPath(Edge *path);
    void setCost(double cost);
    void setPrev(Edge *edge);
    Edge * addEdge(Vertex *dest, double w, string service);
    bool removeEdge(const string& destName);

    struct CompareVertexPointers {
        bool operator()(const Vertex* v1, const Vertex* v2) {
            return v1->dist > v2->dist;
        }
    };
    string getMunicipality() const;
    string getDistrict() const;

    //friend class MutablePriorityQueue<Vertex>;
protected:

    string name;
    string district;
    string municipality;
    string township;
    string station_line;

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
    bool isSelected() const;
    Vertex * getOrig() const;
    Edge *getReverse() const;
    double getFlow() const;
    double getCost() const;

    void setCost(double cost);
    void setSelected(bool selected);
    void setReverse(Edge *reverse);
    void setFlow(double flow);
    void setWeight(double weight);
protected:
    Vertex * dest; // destination vertex

    string service; // type of service

    double weight; // edge weight, can also be used for capacity

    // auxiliary fields
    bool selected = false;

    // used for bidirectional edges
    Vertex *orig;
    Edge *reverse = nullptr;

    double flow; // for flow-related problems
    double cost;
};

#endif /* DA_TP_CLASSES_VERTEX_EDGE */