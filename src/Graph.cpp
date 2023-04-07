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
        v->getAdj().clear();

//        for(auto e : v->getIncoming()){
//            delete e;
//        }
//        v->getIncoming().clear();

        delete v;
    }

    vertexSet.clear();
}

void Graph :: maxFlow(const string& source, const string& dest, double maxSourceFlow){
    Vertex* s = findVertex(source);
    Vertex* t = findVertex(dest);

    if(s == nullptr || t == nullptr){
        cout << "Source or destination not found" << endl;
        return;
    }

    for (Vertex* v: vertexSet){
        for (Edge* e: v->getAdj()){
            e->setFlow(0);
        }
    }

    double bottleneck;
    while(path(s, t, maxSourceFlow)){
        bottleneck = findBottleneck(s, t, maxSourceFlow);
        augmentedPath(s,t, bottleneck);
    }
}

bool Graph::path(Vertex* s, Vertex* t, double maxSourceFlow){
    for (Vertex* v: vertexSet){
        v->setVisited(false);
        v->setPath(nullptr);
    }

    s->setVisited(true);
    std :: queue<Vertex*> q;
    q.push(s);

    while(!q.empty() && !t->isVisited()){
        Vertex* v = q.front(); q.pop();

        if(!v->isEnabled()){
            continue;
        }

        if (v == s) {
            double totalFlow = 0;
            for (Edge *e: v->getAdj()) {
                totalFlow += e->getFlow();
            }
            if (totalFlow >= maxSourceFlow) {
                return false;
            }
        }

        for (Edge* e: v->getAdj()){
            if (e->isEnabled() && !e->getDest()->isVisited() && e->getWeight() - e->getFlow() > 0){
                e->getDest()->setVisited(true);
                e->getDest()->setPath(e);
                q.push(e->getDest());
            }
        }

        for(Edge* e: v->getIncoming()){
            if (e->isEnabled() && !e->getOrig()->isVisited() && e->getFlow() > 0){
                e->getOrig()->setVisited(true);
                e->getOrig()->setPath(e);
                q.push(e->getOrig());
            }
        }
    }

    return t->isVisited();
}

double Graph::findBottleneck(Vertex* s, Vertex* t, double maxSourceFlow){

    double bottleneck = std::numeric_limits<double>::max();
    for(Vertex* v = t; v!=s;){
        Edge* e = v->getPath();
        if(e->getDest()==v){
            bottleneck = std::min(bottleneck, e->getWeight() - e->getFlow());
            v = e->getOrig();
        } else {
            bottleneck = std::min(bottleneck, e->getFlow());
            v = e->getDest();
        }
    }

    double totalFlow = 0;
    for (Edge* e : s->getIncoming()) {
        totalFlow += e->getFlow();
    }
    bottleneck = std::min(bottleneck, maxSourceFlow - totalFlow);


    return bottleneck;
}

void Graph::augmentedPath(Vertex* s, Vertex* t, double bottleneck){
    for(Vertex* v = t; v!=s;){
        Edge* e = v->getPath();
        if(e->getDest()==v){
            e->setFlow(e->getFlow() + bottleneck);
            v = e->getOrig();
        } else {
            e->setFlow(e->getFlow() - bottleneck);
            v = e->getDest();
        }
    }
}

std::vector<Vertex*> Graph:: getInitialStops(){
    return initialStops;
}

void Graph::setInitialStops() {
    for (Vertex* v: vertexSet){
        if (v->getIncoming().empty()) initialStops.push_back(v);
    }
}


bool Graph::dijkstra(string& source, string& dest, int& max_flow, int& min_cost) {

    priority_queue<Vertex *, vector<Vertex *>, Vertex::CompareVertexPointers> stations;

    for (Vertex *v: vertexSet) {
        v->setVisited(false);
        v->setDist(INT32_MAX);
        v->setPrev(nullptr);
    }

    findVertex(source)->setDist(0);
    stations.push(findVertex(source));

    while (!stations.empty()) {
        Vertex *top = stations.top();
        stations.pop();

        if (top->isVisited()) continue;
        top->setVisited(true);

        if (top->getName() == dest) {
            break;
        }

        for (Edge *v: top->getAdj()) {

            Vertex *to = v->getDest();

            if (to->isVisited()) continue;

            double cost = (v->getService() == "STANDARD" ? 2 : 4) * (v->getWeight() - v->getFlow());

            if (to->getDist() > top->getDist() + cost) {
                to->setDist(top->getDist() + cost);
                to->setPrev(v);
                stations.push(to);
            }
        }
    }

    if (!findVertex(dest)->isVisited()) return false;

    double f = INF;

    for (Vertex *v = findVertex(dest); v->getPrev() != nullptr; v = v->getPrev()->getOrig()) {
        f = min(f, v->getPrev()->getWeight() - v->getPrev()->getFlow());
    }

    for (Vertex *v = findVertex(dest); v->getPrev() != nullptr; v = v->getPrev()->getOrig()) {

        if ("STANDARD" != v->getPrev()->getService()) {
            min_cost += f * 4;
        }
        else {
            min_cost += f * 2;
        }
    }

    max_flow = f;

    return true;
}

bool Graph::max_flow_min_cost(string& source, string& dest, int& flow, int& cost) {
    for (Vertex* v: vertexSet){
        for (Edge* e: v->getIncoming()){
            e->setFlow(0);

            Edge* reverse = new Edge(e->getDest(), e->getOrig(), e->getWeight(), e->getService());
            reverse->setFlow(0);
            reverse->setReverse(e);
            e->setReverse(reverse);
        }
    }

    if (!dijkstra(source, dest, flow, cost)) return false;

    return true;
}

bool Graph::removeVertex(const string &name) {
    for (Vertex* v: vertexSet){
        if (v->getName() == name){

            for (Edge* e: v->getAdj()){
                delete e;
            }
            v->getAdj().clear();

//            for (Edge* e: v->getIncoming()){
//                delete e;
//            }
//            v->getIncoming().clear();

            vertexSet.erase(std::remove(vertexSet.begin(), vertexSet.end(), v), vertexSet.end());
            delete v;
            return true;
        }
    }
    return false;
}
