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
    /*
     * Constructor
     */
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

    /**
     * @brief Cleans the graph to avoid memory leaks
     */
    void cleanGraph();

    /**
     * @brief Calculates the maximum flow between two stations, using an adapted version of the Edmonds-Karp algorithm to take into consideration cases where the flow entering the source station is not infinite
     * Leaving the 3rd parameter empty will calculate the maximum flow between the two stations, with an infinite flow entering the source station, which is the default case for the Edmonds-Karp algorithm
     * @param source
     * @param dest
     * @param maxSourceFlow
     * @return
     */
    double RmaxFlow(const string& source, const string& dest, double maxSourceFlow = numeric_limits<double>::max());

    /**
     *
     * @return
     */
    std::vector<pair<double, string>> mostAmountOfTrains();


    /**
     * @brief Checks if a station exists
     * @param stationName - name of the station to check
     * @return
     */
    bool stationExists(const string& stationName);
};


#endif //PROJETO_DA_1_RAILWAY_H
