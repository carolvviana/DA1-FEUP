//
// Created by Sergio on 05/03/2023.
//

#ifndef PROJETO_DA_1_MENU_H
#define PROJETO_DA_1_MENU_H

#include <stack>
#include <iostream>
#include "Railway.h"

/*
 * Menu's states
 */
enum MenuState{
    INIT_MENU, // Initial menu
    MAIN_MENU,
    BASIC_SERVICE_METRICS,
    OPERATIONS_COST_OPTIMIZATION,
    RELIABILITY_AND_SENSITIVITY_TO_LINE_FAILURES,
    SUBGRAPH_MAX_TRAINS,
    SUBGRAPH_MOST_SENSITIVE
    // To add more menus, just add here
};

/*
 * Menu class to manage interface
 */
class Menu {
private:

    /**
     * @var railway - railway object
     */
    Railway railway;
    /**
     * @var menuState - stack of menu's states
     */
    std::stack<MenuState> menuState;

    /**
     * @brief Function to get the menu on top menuState stack
     */
    void getMenu();

    /**
     * @var option - option selected by user
     */
    int option;

    /**
     * @brief Initial menu of application
     */
    void InitMenu();

    /**
     * @brief Main menu of application
     */
    void mainMenu();

    /**
     * @brief Basic Service Metrics menu
     */
    void basicServiceMetrics();

    /**
     * @brief Operations Cost Optimization menu
     */
    void operationsCostOptimization();

    /**
     * @brief Reliability and Sensitivity to Line Failures menu
     */
    void reliabilityAndSensitivityToLineFailures();

    /**
     * @brief Subgraph analysis - Max trains menu
     */
    void subgraphMaxTrains();

    /**
     * @brief Subgraph analysis - Most sensitive menu
     */
    void subgraphMostSensitive();

    /**
     * @brief Function to clear the Menu stack
     * This should be called before leaving the application to avoid memory leaks
     */
    void clearStack();

    /**
     * @var stationsFilepath - filepath to stations file
     */
    string stationsFilepath = "../data/stations.csv";

    /**
     * @var linesFilepath - filepath to lines file
     */
    string linesFilepath= "../data/network.csv";

public:
    /**
     * Constructor of Menu class
     */
    Menu();
};


#endif //PROJETO_DA_1_MENU_H
