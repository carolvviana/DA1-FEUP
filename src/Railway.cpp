//
// Created by Sergio on 10/03/2023.
//

#include "Railway.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <list>
#include <unordered_map>
#include <set>

using namespace std;

Railway::Railway() = default;

void Railway::createStations(const string& filepath) {
    ifstream file;
    file.open(filepath);
    string line;

    /* Check if file is open */
    if(!file.is_open()){
        cout << "Error opening file" << endl;
        return;
    }

    /* Read the first line (labels) */
    getline(file,line);

    if(line != "Name,District,Municipality,Township,Line"){
        cout << "Error reading file, wrong format of file" << endl;
        return;
    }

    /* Read the rest of the file */
    while(getline(file, line)){
        istringstream iss(line);

        /* Labels */
        string name, district, municipality, township, station_line;
        list<string* > labels = {&name, &district, &municipality, &township, &station_line};

        for(string* label : labels) {
            std::string labelData;

            if (iss.peek() == '"') {
                iss >> std::quoted(labelData);
                std::string discard;
                std::getline(iss, discard, ',');
            }
            else {
                std::getline(iss, labelData, ',');
            }

            *label = labelData;
        }

        graph.addVertex(name, district, municipality, township, station_line);
    }
}
void Railway::createStationsMunicipalities(const string& filepath) {
    std::set<string> municipalities;
    ifstream file;
    file.open(filepath);
    string line;

    /* Check if file is open */
    if(!file.is_open()){
        cout << "Error opening file" << endl;
        return;
    }

    /* Read the first line (labels) */
    getline(file,line);

    if(line != "Name,District,Municipality,Township,Line"){
        cout << "Error reading file, wrong format of file" << endl;
        return;
    }

    /* Read the rest of the file */
    while(getline(file, line)){
        istringstream iss(line);

        /* Labels */
        string name, district, municipality, township, station_line;
        list<string* > labels = {&name, &district, &municipality, &township, &station_line};

        for(string* label : labels) {
            std::string labelData;

            if (iss.peek() == '"') {
                iss >> std::quoted(labelData);
                std::string discard;
                std::getline(iss, discard, ',');
            }
            else {
                std::getline(iss, labelData, ',');
            }

            *label = labelData;
        }

        municipalities.insert(municipality);
    }
    municipalities.erase("");
    for (string mun: municipalities){
        graph_municipalities.addVertex(mun, "", "", "", "");
    }
}

void Railway::createLines(const string &filepath) {
    ifstream file;
    file.open(filepath);
    string line;

    /* Check if file is open */
    if(!file.is_open()){
        cout << "Error opening file" << endl;
        return;
    }

    /* Read the first line (labels) */
    getline(file,line);

    if(line != "Station_A,Station_B,Capacity,Service"){
        cout << "Error reading file, wrong format of file" << endl;
        return;
    }

    /* Read the rest of the file */
    while(getline(file, line)){
        istringstream iss(line);

        /* Labels */
        string station_a, station_b, capacity, service;
        list<string* > labels = {&station_a, &station_b, &capacity, &service};

        for(string* label : labels) {
            std::string labelData;

            if (iss.peek() == '"') {
                iss >> std::quoted(labelData);
                std::string discard;
                std::getline(iss, discard, ',');
            }
            else {
                std::getline(iss, labelData, ',');
            }

            *label = labelData;
        }

        graph.addEdge(station_a, station_b, stoi(capacity), service);
    }
}
void Railway::createLinesMunicipalities(const string &filepath) {

    ifstream file;
    file.open(filepath);
    string line;

    /* Check if file is open */
    if(!file.is_open()){
        cout << "Error opening file" << endl;
        return;
    }

    /* Read the first line (labels) */
    getline(file,line);

    if(line != "Station_A,Station_B,Capacity,Service"){
        cout << "Error reading file, wrong format of file" << endl;
        return;
    }

    /* Read the rest of the file */
    while(getline(file, line)){
        istringstream iss(line);

        /* Labels */
        string station_a, station_b, capacity, service;
        list<string* > labels = {&station_a, &station_b, &capacity, &service};

        for(string* label : labels) {
            std::string labelData;

            if (iss.peek() == '"') {
                iss >> std::quoted(labelData);
                std::string discard;
                std::getline(iss, discard, ',');
            }
            else {
                std::getline(iss, labelData, ',');
            }

            *label = labelData;
        }
        Vertex *source = graph.findVertex(station_a);
        Vertex *dest = graph.findVertex(station_b);

        if (source->getMunicipality()!= dest->getMunicipality()){
            graph_municipalities.addEdge(source->getMunicipality(), dest->getMunicipality(), stoi(capacity), service);
        }
    }
}

void Railway::cleanGraph() {
    graph.cleanGraph();
    graph_municipalities.cleanGraph();
}

double Railway:: RmaxFlow(const string& source, const string& dest, double maxSourceFlow){
    double result = 0;
    graph.maxFlow(source, dest, maxSourceFlow);
    Vertex* v = graph.findVertex(dest);
    for (Edge* e :v->getIncoming()){
        result+=e->getFlow();
    }
    return result;
}
double Railway:: RmaxFlow_municipalities(string& source, string& dest){
    double result = 0;
    graph_municipalities.maxFlow(source, dest, std::numeric_limits<double>::max());
    Vertex* v = graph_municipalities.findVertex(dest);
    for (Edge* e :v->getIncoming()){
        result+=e->getFlow();
    }
    return result;
}

std::vector<pair<double, string>> Railway::mostAmountOfTrains(){
    vector<pair<double, string>> result;

    //add a super source
    graph.addVertex("SuperSource", "SuperSource", "SuperSource", "SuperSource", "SuperSource");

    //add edges from super source to all initial stops
    vector<Vertex*> initialStops = graph.getInitialStops();
    for(Vertex* v : initialStops){
        if(v->getName() != "SuperSource")
            graph.addEdge("SuperSource", v->getName(), std::numeric_limits<double>::max() , "SuperSource");
    }


    vector<Vertex *> vertexSet = graph.getVertexSet();
    unordered_map<string, double> incomingFlows; //cache to store incoming flows from SuperSource to vertices

    //go through all combinations of stops
    for(Vertex* a : vertexSet){
        if(a->getName() == "SuperSource") continue;

        //node A incomming flow
        double Aflow;
        if(incomingFlows.find(a->getName()) != incomingFlows.end()){
            Aflow = incomingFlows[a->getName()];
        }
        else{
            Aflow = RmaxFlow("SuperSource", a->getName(), std::numeric_limits<double>::max());
            incomingFlows[a->getName()] = Aflow;
        }
        if(Aflow == 0) continue; //if no flow from super source to a, skip

        for(Vertex* b : vertexSet){
            if(b->getName() == "SuperSource") continue;

            if(a->getName() != b->getName() && b->getName() != "SuperSource"){
                //find the max flow from a to b
                double maxFlow = RmaxFlow(a->getName(), b->getName(), Aflow);
                //add to result
                if(maxFlow > 0){
                    result.push_back({maxFlow, a->getName() + " -> " + b->getName()});
                }
            }
        }
    }

    //remove super source
    graph.removeVertex("SuperSource");

    //sort in descending order
    sort(result.rbegin(), result.rend());

    return result;
}

bool Railway::stationExists(const string& stationName) {
    return graph.findVertex(stationName) != nullptr;

}

std::vector<string> Railway::topKMunicipalities(int k){
    vector<string> rtrn;
    vector<pair<string, double>> res;


    //add a super source
    //Vertex SuperSource = Vertex("SuperSource", "SuperSource", "SuperSource", "SuperSource", "SuperSource");
    graph_municipalities.addVertex("SuperSource", "SuperSource", "SuperSource", "SuperSource", "SuperSource");
    graph_municipalities.addVertex("SuperSink", "SuperSink", "SuperSink", "SuperSink", "SuperSink");
    //add edges from super source to all initial stops
    vector<Vertex*> initialStops = graph.getInitialStops();
    for(Vertex* v : initialStops){
        graph_municipalities.addEdge("SuperSource", v->getMunicipality(), INF , "SuperSource");
    }

    vector<Vertex*> finalStops;
    for (auto v: graph_municipalities.getVertexSet()){
        if (v->getAdj().empty()){
            finalStops.push_back(v);
        }
    }
    for(Vertex* v : initialStops){
        graph_municipalities.addEdge("SuperSource", v->getMunicipality(), INF , "SuperSource");
    }
    for(Vertex* v : finalStops){
        graph_municipalities.addEdge(v->getName(), "SuperSink", INF , "SuperSink");
    }


    string source = graph_municipalities.findVertex("SuperSource")->getName();
    string sink = graph_municipalities.findVertex("SuperSink")->getName();

    double flow = RmaxFlow_municipalities(source, sink);

    for (auto v: graph_municipalities.getVertexSet()){
        double f = 0;
        for (auto e: v->getIncoming()){
            f += e->getFlow();
        }
        res.push_back({v->getName(),f});
    }

    //go through all combinations of stops
    //for (auto it = initialStopsMunicipalities.begin(); it != initialStopsMunicipalities.end(); it++){
        //for (Vertex *v: graph_municipalities.getVertexSet()) {
    //for (string d: initialStopsMunicipalities) {
            //string dest = v->getName();
            //string source = s->getMunicipality();
            //string source = *(it);
            //string test= "FARO";
            //double flow = RmaxFlow_municipalities(source, test);
            //res.push_back({test, flow});
            //rtrn.push_back(res[0].first);
        //}
    //}

    std::sort(res.begin(), res.end(), [](auto &left, auto &right) {
        return left.second > right.second;
    });
    for (int i = 1; i <= k; i++){
        rtrn.push_back((res[i].first));
    }
    return rtrn;
}