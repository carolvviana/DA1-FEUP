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
    std::vector<string> res;
    std::vector<Vertex*> initialStops = graph.initialStops();
    string source = initialStops[0]->getName();
    string dest = graph.getVertexSet()[0]->getName();
    double maxFlow = RmaxFlow(source, dest);

    for (Vertex* v: graph.getVertexSet()){
        for (Vertex* vertex: initialStops){
            string s = vertex->getName();
            string t = v->getName();
            double localMax = RmaxFlow(s, t);

            if (localMax >= maxFlow){
                maxFlow = localMax;
            }
        }
    }

    for (Vertex* v: graph.getVertexSet()){
        for (Vertex* vertex: initialStops){
            string s = vertex->getName();
            string t = v->getName();
            double localMax = RmaxFlow(s, t);

            if (localMax == maxFlow){
                res.push_back(s);
                res.push_back(t);
            }
        }
    }

    return res;

}