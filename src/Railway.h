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
     * @var graph - graph of the railway
     */
    Graph graph;

    /**
     * @var graph_municipalities - graph of the railway considering only the municipalities (each municipality is a vertex)
     */
    Graph graph_municipalities;

    /**
     * @var graph_districts - graph of the railway considering only the districts (each district is a vertex)
     */
    Graph graph_districts;

public:
    /*
     * Constructor
     */
    Railway();

    /**
     * @brief Creates the stations of the railway
     * Time Complexity: O(V^2) where V is the number of vertices
     * @param filepath Path to the file containing the stations
     */
    void createStations(const string& filepath = "../data/stations.csv");

    /**
     * @brief Creates the stations of the railway considering only the municipalities (each municipality is a vertex)
     * Time Complexity: O(V^2) where V is the number of vertices
     * @param filepath Path to the file containing the stations
     */
    void createStationsMunicipalities(const string& filepath = "../data/stations.csv");

    /**
     * @brief Creates the stations of the railway considering only the districts (each district is a vertex)
     * Time Complexity: O(V^2) where V is the number of vertices
     * @param filepath Path to the file containing the stations
     */
    void createStationsDistricts(const string& filepath = "../data/stations.csv");

    /**
     * @brief Creates the lines of the railway
     * Time complexity: O(V^2) where V is the number of vertices
     * @param filepath Path to the file containing the lines
     */
    void createLines(const string& filepath = "../data/network.csv");

    /**
     * @brief Creates the lines of the railway considering only the municipalities (each municipality gets all the lines that enter and leave it)
     * Time complexity: O(V^2) where V is the number of vertices
     * @param filepath Path to the file containing the lines
     */
    void createLinesMunicipalities(const string& filepath = "../data/network.csv");

    /**
     * @brief Creates the lines of the railway considering only the districts (each district gets all the lines that enter and leave it)
     * Time complexity: O(V^2) where V is the number of vertices
     * @param filepath Path to the file containing the lines
     */
    void createLinesDistricts(const string &filepath = "../data/network.csv");

    /**
     * @brief Resets the enable flag of all the stations and lines to true
     * Time Complexity: O(V + E) where V is the number of vertices and E is the number of edges
     */
    void resetGraph();

    /**
     * @brief Builds the graph of the railway by calling the CreateStations and CreateLines functions
     * @param stations_path Path to the file containing the stations
     * @param lines_path Path to the file containing the lines
     */
    void buildGraph(const string &stations_path, const string &lines_path);

    /**
     * @brief Disables a station from the graph to help in the creation of subgraphs
     * Time Complexity: O(V + E) where V is the number of vertices and E is the number of edges
     * @param stationName Name of the station to disable
     * @return True if the station was disabled, false otherwise
     */
    bool disableStation(const string& stationName);

    /**
     * @brief Disables a line from the graph to help in the creation of subgraphs (lines must be a direct connection between two stations)
     * Time Complexity: O(V + E) where V is the number of vertices and E is the number of edges
     * @param origStation Name of the station where the line starts
     * @param destStation Name of the station where the line ends
     * @return True if the line was disabled, false otherwise
     */
    bool disableLine(const string& origStation, const string& destStation);

    /**
     * @brief Cleans the graph to avoid memory leaks
     * Time Complexity: O(V + E) where V is the number of vertices and E is the number of edges
     */
    void cleanGraph();

    /**
     * @brief Calculates the maximum flow between two stations, using an adapted version of the Edmonds-Karp algorithm to take into consideration cases where the flow entering the source station is not infinite
     * Leaving the 3rd parameter empty will calculate the maximum flow between the two stations, with an infinite flow entering the source station, which is the default case for the Edmonds-Karp algorithm
     * Time Complexity: O(E * V^2) where V is the number of vertices and E is the number of edges
     * @param source Name of the source station
     * @param dest Name of the destination station
     * @param maxSourceFlow Maximum flow entering the source station
     * @return The maximum flow between the two stations with the given flow entering the source station
     */
    double RmaxFlow(const string& source, const string& dest, double maxSourceFlow = numeric_limits<double>::max());

    /**
     * @brief Calculates the maximum flow between every pair of stations, using RmaxFlow() function to take into consideration cases where the flow entering the source station is not infinite
     * Time Complexity:
     * @return A vector of pairs, where the first element is the maximum flow between the two stations and the second element is the name of those stations
     */
    std::vector<pair<double, string>> mostAmountOfTrains();

    /**
     * @brief Checks if a station exists
     * Time Complexity: O(V) where V is the number of vertices
     * @param stationName Name of the station to check
     * @return True if the station exists, false otherwise
     */
    bool stationExists(const string& stationName);

    /**
     * @brief Calculates the maximum flow between two municipalities, using an adapted version of the Edmonds-Karp algorithm to take into consideration cases where the flow entering the source municipality is not infinite
     * Time Complexity: O(E * V^2) where V is the number of vertices and E is the number of edges
     * @param source Name of the source municipality
     * @param dest Name of the destination municipality
     * @return The maximum flow between the two municipalities with the given flow entering the source municipality
     */
    double RmaxFlow_municipalities(string& source, string& dest);

    /**
     * @brief Calculates the maximum flow between two districts, using an adapted version of the Edmonds-Karp algorithm to take into consideration cases where the flow entering the source district is not infinite
     * Time Complexity: O(E * V^2) where V is the number of vertices and E is the number of edges
     * @param source Name of the source district
     * @param dest Name of the destination district
     * @return The maximum flow between the two districts with the given flow entering the source district
     */
    double RmaxFlow_districts(string& source, string& dest);

    /**
     * @brief Calculates the Top K districts with the bigger budget needs (Districts with bigger maximum flow need bigger budgets)
     * @param k Number of districts to return
     * @return A vector of strings with the names of the Top K districts, ordered
     */
    std::vector<string> topKDistricts(int k);

    /**
     * @brief
     * @param k
     * @return
     */
    std::vector<string> topKStations(int k);

    /**
     * @brief Calculates the Top K municipalities with the bigger budget needs (Municipalities with bigger maximum flow need bigger budgets)
     * Time Complexity:
     * @param k Number of municipalities to return
     * @return A vector of strings with the names of the Top K municipalities, ordered
     */
    std::vector<string> topKMunicipalities(int k);

    /**
     * @brief Calculates the maximum number of trains that can arrive at a station, using the Edmonds-Karp algorithm
     * @param dest Name of the destination station
     * @return The maximum number of trains that can arrive at the station
     */
    double maxNumberOfTrainsArriving(string dest);

    /**
     * @brief
     * Time Complexity:
     * @return
     */
    pair<int,int> operationCost(string& source, string& dest);


};

#endif //PROJETO_DA_1_RAILWAY_H
