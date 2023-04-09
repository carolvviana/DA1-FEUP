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
    Graph graph_municipalities;
    Graph graph_districts;

public:
    /*
     * Constructor
     */
    Railway();

    /**
     * @brief Creates the stations of the railway
     * Time Complexity: O(V^2) where V is the number of vertices
     * @param filepath - Path to the file containing the stations
     */
    void createStations(const string& filepath = "../data/stations.csv");

    /**
     * @brief Creates the stations of the railway
     * @param filepath
     */
    void createStationsMunicipalities(const string& filepath = "../data/stations.csv");
    void createStationsDistricts(const string& filepath = "../data/stations.csv");

    /**
     * @brief Creates the lines of the railway
     * Time complexity: O(V^2) where V is the number of vertices
     * @param filepath - Path to the file containing the lines
     */
    void createLines(const string& filepath = "../data/network.csv");

    void createLinesMunicipalities(const string& filepath = "../data/network.csv");
    void createLinesDistricts(const string &filepath = "../data/network.csv");

    bool disableStation(const string& stationName);
    bool disableLine(const string& origStation, const string& destStation);

    /**
     * @brief Cleans the graph to avoid memory leaks
     */
    void cleanGraph();

    pair<int,int> operationCost(string& source, string& dest);


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

    std::vector<string> topKMunicipalities(int k);

    double RmaxFlow_municipalities(string& source, string& dest);
    double RmaxFlow_districts(string& source, string& dest);
    std::vector<string> topKDistricts(int k);
    std::vector<string> topKStations(int k);
    double maxNumberOfTrainsArriving(string dest);

    void resetGraph();
    //void setOGGraph();

    std::vector<tuple<string, string, string, string, string>> originalStations;
    std::vector<tuple<string, string, string, string>> originalLines;

    void buildGraph(const string &stations_path, const string &lines_path);

};

#endif //PROJETO_DA_1_RAILWAY_H
