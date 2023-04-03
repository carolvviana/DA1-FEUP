//
// Created by Sergio on 10/03/2023.
//

#include "Railway.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <list>

using namespace std;

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

Railway::Railway() = default;

void Railway::cleanGraph() {
    graph.cleanGraph();
}

double Railway:: RmaxFlow(string& source, string& dest){
    double result;
    graph.maxFlow(source, dest);
    Vertex* v = graph.findVertex(dest);
    for (Edge* e :v->getIncoming()){
        result+=e->getFlow();
    }
    return result;
}

std::vector<string> Railway::mostAmountOfTrains(){
    //add a super source
    Vertex SuperSource = Vertex("SuperSource", "SuperSource", "SuperSource", "SuperSource", "SuperSource");

    //add edges from super source to all initial stops
    vector<Vertex*> initialStops = graph.getInitialStops();
    for(Vertex* v : initialStops){
        graph.addEdge("SuperSource", v->getName(), INF , "SuperSource");
    }

    //go through all combinations of stops


}

void Railway::operationCost(string& source, string& dest, int mincost) {
    graph.dijkstra(source, dest);

    Vertex* target = graph.findVertex(dest);
    stack<Vertex*> path;

    // Erro pq????
    cout << graph.findVertex(dest)->getPrev()->getName() << "\n";

    if ((target->getPrev() != nullptr) || (target == graph.findVertex(source))) {
        cout << "inside if" << "\n";
        while (target != nullptr) {
            path.push(target->getPrev());
            cout << target->getCost() << '\n';
            cout << target->getName() << '\n';
            target = target->getPrev();
        }
    }
}

