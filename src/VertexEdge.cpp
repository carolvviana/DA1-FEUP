// By: Gonçalo Leão

#include "VertexEdge.h"

/************************* Vertex  **************************/

Vertex::Vertex(string name, string district, string municipality, string township, string station_line):
    name(name), district(district), municipality(municipality), township(township), station_line(station_line) {}

/*
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * with a given destination vertex (d) and edge weight (w).
 */
Edge * Vertex::addEdge(Vertex *d, double w, string service){
    auto newEdge = new Edge(this, d, w, service);
    adj.push_back(newEdge);
    d->incoming.push_back(newEdge);
    return newEdge;
}

bool Vertex::operator<(Vertex & vertex) const {
    return this->dist < vertex.dist;
}

string Vertex::getName() const {
    return this->name;
}

std::vector<Edge*> Vertex::getAdj() const {
    return this->adj;
}

bool Vertex::isVisited() const {
    return this->visited;
}


double Vertex::getDist() const {
    return this->dist;
}

Edge *Vertex::getPath() const {
    return this->path;
}

Edge* Vertex::getPrev() const {
    return this->prev;
}

std::vector<Edge *> Vertex::getIncoming() const {
    return this->incoming;
}

string Vertex::getMunicipality() const{
    return this->municipality;
}
string Vertex::getDistrict() const{
    return this->district;
}

void Vertex::setVisited(bool visited) {
    this->visited = visited;
}


void Vertex::setDist(double dist) {
    this->dist = dist;
}

void Vertex::setPath(Edge *path) {
    this->path = path;
}


void Vertex::setPrev(Edge *edge) {
    this->prev = edge;
}

bool Vertex::isEnabled() const {
    return enabled;
}

void Vertex::setEnabled(bool enabled) {
    this->enabled = enabled;
}

bool Vertex::disableEdge(const string &destName) {
    for (auto & edge : adj) {
        if (edge->getDest()->getName() == destName) {
            edge->setEnabled(false);
            return true;
        }
    }
    return false;
}

/********************** Edge  ****************************/

Edge::Edge(Vertex *orig, Vertex *dest, double w, string service): orig(orig), dest(dest), weight(w), service(service) {}

Vertex * Edge::getDest() const {
    return this->dest;
}

double Edge::getWeight() const {
    return this->weight;
}

Vertex * Edge::getOrig() const {
    return this->orig;
}

double Edge::getFlow() const {
    return flow;
}

bool Edge::isEnabled() const {
    return enabled;
}

void Edge::setReverse(Edge *reverse) {
    this->reverse = reverse;
}

void Edge::setFlow(double flow) {
    this->flow = flow;
}

string Edge::getService() const{
    return this->service;
}

void Edge::setEnabled(bool enabled) {
    this->enabled = enabled;
}

