// By: Gonçalo Leão

#include "Graph.h"

int Graph::getNumVertex() const {
    return vertexSet.size();
}

std::vector<Vertex *> Graph::getVertexSet() const {
    return vertexSet;
}

/*
 * Auxiliary function to find a vertex with a given content.
 */
Vertex * Graph::findVertex(const string &name) const {
    for (auto v : vertexSet)
        if (v->getName() == name)
            return v;
    return nullptr;
}

/*
 * Finds the index of the vertex with a given content.
 */
int Graph::findVertexIdx(const string &name) const {
    for (unsigned i = 0; i < vertexSet.size(); i++)
        if (vertexSet[i]->getName() == name)
            return i;
    return -1;
}
/*
 *  Adds a vertex with a given content or info (in) to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already exists.
 */
bool Graph::addVertex(const string &name, const string& district, const string& municipality, const string& township, const string& station_line) {
    if (findVertex(name) != nullptr)
        return false;
    vertexSet.push_back(new Vertex(name, district, municipality, township, station_line));
    return true;
}

/*
 * Adds an edge to a graph (this), given the contents of the source and
 * destination vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */
bool Graph::addEdge(const string &source, const string &dest, double w, const string& service) {
    auto v1 = findVertex(source);
    auto v2 = findVertex(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    v1->addEdge(v2, w, service);
    return true;
}

bool Graph::addBidirectionalEdge(const string &source, const string &dest, double w, const string& service) {
    auto v1 = findVertex(source);
    auto v2 = findVertex(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    auto e1 = v1->addEdge(v2, w, service);
    auto e2 = v2->addEdge(v1, w, service);
    e1->setReverse(e2);
    e2->setReverse(e1);
    return true;
}

void deleteMatrix(int **m, int n) {
    if (m != nullptr) {
        for (int i = 0; i < n; i++)
            if (m[i] != nullptr)
                delete [] m[i];
        delete [] m;
    }
}

void deleteMatrix(double **m, int n) {
    if (m != nullptr) {
        for (int i = 0; i < n; i++)
            if (m[i] != nullptr)
                delete [] m[i];
        delete [] m;
    }
}

Graph::~Graph() {
    deleteMatrix(distMatrix, vertexSet.size());
    deleteMatrix(pathMatrix, vertexSet.size());
}

void Graph::cleanGraph() {
    /* remove all vertices and edges */
    for (auto v : vertexSet){

        for(auto e : v->getAdj()){
            delete e;
        }
        delete v;
    }
    vertexSet.clear();
}
void Graph :: maxFlow(string& source, string& dest){
    for (Vertex* v: vertexSet){
        for (Edge* e: v->getIncoming()){
            e->setFlow(0);

            Edge* reverse = new Edge(e->getDest(), e->getOrig(), e->getWeight(), e->getService());
            reverse->setFlow(0);
            reverse->setReverse(e);
            e->setReverse(reverse);
        }
    }

    double bottleneck;
    while(path(source,dest)){
        bottleneck = findBottleneck(dest);
        augmentedPath(dest, bottleneck);
    }
}
bool Graph::path(string& source, string& dest){
    for (Vertex* v: vertexSet){
        v->setVisited(false);
        v->setPath(nullptr);
    }
    std :: queue<string> s({source});
    findVertex(source)->setVisited(true);
    while(!s.empty()){
        Vertex* v = findVertex(s.front());
        for(Edge* e: v->getAdj()){
            if (!e->getDest()->isVisited() && e->getWeight() - e->getFlow() > 0){
                s.push(e->getDest()->getName());
                e->getDest()->setVisited(true);
                e->getDest()->setPath(e);
                if ( e->getDest()->getName() == dest){
                    return true;
                }
            }
        }

        for (Edge* e: v->getIncoming()){
            if(e->getReverse()->getOrig() == v && !e->getReverse()->getDest()->isVisited() && e->getReverse()->getFlow() != 0){
                s.push(e->getReverse()->getDest()->getName());
                e->getDest()->setVisited(true);
                e->getDest()->setPath(e);
                if ( e->getDest()->getName() == dest){
                    return true;
                }
            }
        }
        s.pop();
    }
    return false;
}
double Graph:: findBottleneck(string& dest){
    Vertex* v = findVertex(dest);
    double bottleneck = std::numeric_limits<double>::max();
    while(v->getPath() != nullptr){
        double remaining = v->getPath()->getWeight() - v->getPath()->getFlow();
        if (remaining < bottleneck){
            bottleneck = remaining;
        }
        v = v->getPath()->getOrig();
    }
    return bottleneck;
}
void Graph:: augmentedPath(string& dest, double bottleneck){
    Vertex* v = findVertex(dest);
    while(v->getPath() != nullptr){
        v->getPath()->setFlow(v->getPath()->getFlow() + bottleneck);
        v->getPath()->getReverse()->setFlow(v->getPath()->getReverse()->getFlow() - bottleneck);
        v = v->getPath()->getOrig();
    }
}
std::vector<Vertex*> Graph:: initialStops(){
    std::vector<Vertex*> res;
    for (Vertex* v: vertexSet){
        if (v->getIncoming().empty()) res.push_back(v);
    }
    return res;
}
