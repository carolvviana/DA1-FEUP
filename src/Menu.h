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
     * Function to get the menu on top menuState stack
     */
    void getMenu();

    /**
     * @var option - option selected by user
     */
    int option;

    /**
     * Initial menu of application
     */
    void InitMenu();

    /**
     * Main menu of application
     */
    void mainMenu();

    /**
     * Basic Service Metrics menu
     */
    void basicServiceMetrics();

    /**
     * Operations Cost Optimization menu
     */
    void operationsCostOptimization();

    /**
     * Reliability and Sensitivity to Line Failures menu
     */
    void reliabilityAndSensitivityToLineFailures();


    void subgraphMaxTrains();

    void subgraphMostSensitive();

    /**
     * Function to clear the Menu stack
     * This should be called before leaving the application to avoid memory leaks
     */
    void clearStack();

    string stationsFilepath = "../data/stations.csv";
    string linesFilepath= "../data/network.csv";

public:
    /**
     * Constructor of Menu class
     */
    Menu();


};


#endif //PROJETO_DA_1_MENU_H
