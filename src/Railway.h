//
// Created by Sergio on 10/03/2023.
//

#ifndef PROJETO_DA_1_RAILWAY_H
#define PROJETO_DA_1_RAILWAY_H

#include <string>
#include "Graph.h"

using namespace std;



class Railway {
private:

    /**
     *
     */
    Graph graph;
public:
    Railway();

    /**
     * @brief Creates the stations of the railway
     */
    void createStations(const string& filepath = "../data/stations.csv");

    /**
     * @brief Creates the lines of the railway
     * @return
     */
    void createLines(const string& filepath = "../data/network.csv");

    void cleanGraph();
    double RmaxFlow(string& source, string& dest);
    std:: vector<string> mostAmountOfTrains();
    void operationCost(string& source, string& dest);
};


#endif //PROJETO_DA_1_RAILWAY_H
