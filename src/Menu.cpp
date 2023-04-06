//
// Created by Sergio on 05/03/2023.
//

#include "Menu.h"

using namespace std;

Menu::Menu() {
    this->menuState.push(INIT_MENU);
    railway = Railway();
    getMenu();
}

void Menu::getMenu() {
    if(!this->menuState.empty()){
        switch(this->menuState.top()){
            case INIT_MENU: InitMenu(); break;
            case MAIN_MENU: mainMenu(); break;
            case BASIC_SERVICE_METRICS: basicServiceMetrics(); break;
            case OPERATIONS_COST_OPTIMIZATION: operationsCostOptimization(); break;
            case RELIABILITY_AND_SENSITIVITY_TO_LINE_FAILURES: reliabilityAndSensitivityToLineFailures(); break;
            case SUBGRAPH_MAX_TRAINS: subgraphMaxTrains(); break;
        }
    } else {
        railway.cleanGraph(); //to avoid memory leaks before leaving the programm
        exit(0);
    }
}

void Menu::InitMenu() {

    do {
        cout << "Initial Menu" << endl;
        cout << "1 - Read default files" << endl;
        cout << "2 - Read custom files" << endl;
        cout << "3 - Exit" << endl;
        cout << "Option: ";
        cin >> this->option;

        if (this->option < 1 || this->option > 3) {
            cout << "Invalid Option!" << endl;
        }
        cin.clear();
        cin.ignore(1000, '\n');

    } while (this->option < 1 || this->option > 3);

    switch (this->option) {
        case 1: {
            /* clean the graph if it already exists */
            railway.cleanGraph();

            railway.createStations();
            railway.createLines();
            railway.createStationsMunicipalities();
            railway.createLinesMunicipalities();
            railway.createStationsDistricts();
            railway.createLinesDistricts();

            menuState.push(MAIN_MENU);
            break;
        }
        case 2: {
            /* clean the graph if it already exists */
            railway.cleanGraph();

            /* ask for file paths */
            string stations_path, lines_path;
            cout << "Stations file path: ";
            getline(cin, stations_path);
            cout << "Lines file path: ";
            getline(cin, lines_path);

            railway.createStations(stations_path);
            railway.createLines(lines_path);
            railway.createStationsMunicipalities(stations_path);
            railway.createLinesMunicipalities(lines_path);
            railway.createStationsDistricts(stations_path);
            railway.createLinesDistricts(lines_path);

            menuState.push(MAIN_MENU);
            break;
        }
        case 3: {
            menuState.pop();
            break;
        }
    }

    getMenu();
}

void Menu::mainMenu() {
    do{
        cout << "Main Menu" << endl;
        cout << "1 - Basic Service Metrics" << endl;
        cout << "2 - Operations Cost Optimization" << endl;
        cout << "3 - Line Reliability and Sensitivity" << endl;
        cout << "4 - Back" << endl;
        cout << "5 - Exit" << endl;
        cout << "Option: ";
        cin >> this->option;

        if (this->option < 1 || this->option > 4) {
            cout << "Invalid Option!" << endl;
        }

        cin.clear(); // clear input buffer to restore cin to a usable state
        cin.ignore(1000, '\n'); // ignore last input

    } while (this->option < 1 || this->option > 4);

    switch(this->option){
        case 1: {
            menuState.push(BASIC_SERVICE_METRICS);
            break;
        }
        case 2: {
            menuState.push(OPERATIONS_COST_OPTIMIZATION);
            break;
        }
        case 3:{
            menuState.push(RELIABILITY_AND_SENSITIVITY_TO_LINE_FAILURES);
            break;
        }
        case 4: {
            //return
            menuState.pop();
            break;
        }
        case 5: {
            //exit
            clearStack();
            break;
        }
    }

    getMenu();
}

void Menu::basicServiceMetrics(){
    do{
        cout << "Basic Service Metrics" << endl;
        cout << "1 - Max number of trains between stations" << endl;
        cout << "2 - Most amount of trains between two stations" << endl;
        cout << "3 - Budget Allocation" << endl;
        cout << "4 - Max number of trains arriving at given station" << endl;
        cout << "5 - Back" << endl;
        cout << "6 - Exit" << endl;
        cout << "Option: ";
        cin >> this->option;

        if (this->option < 1 || this->option > 6) {
            cout << "Invalid Option!" << endl;
        }

        cin.clear(); // clear input buffer to restore cin to a usable state
        cin.ignore(1000, '\n'); // ignore last input

    } while (this->option < 1 || this->option > 6);

    switch (option) {
        case 1:{
            string station1, station2;

            do {

                cout << "Origin Station: ";
                getline(cin, station1);
                cout << "Destination Station: ";
                getline(cin, station2);

                if (!railway.stationExists(station1) || !railway.stationExists(station2)) {
                    cout << "Invalid Station!" << endl;
                }

            } while(!railway.stationExists(station1) || !railway.stationExists(station2));

            cout << railway.RmaxFlow(station1, station2, std::numeric_limits<double>::max()) << endl;

            cout << "Press enter to continue..." << endl;
            std::cin.get(); // wait for user input

            break;
        }
        case 2:{
            cout << "This may take a while :)" << endl;
            cout << "Should take around 1 minute" << endl;

            std::vector<pair<double, string>>  result = railway.mostAmountOfTrains();

            for (int i = 0; i < 10; i++) {
                auto s = result.at(i);
                cout << "  " << s.first << " " << s.second <<'\n';
            }

            cout << "Press enter to continue..." << endl;
            std::cin.get(); // wait for user input

            break;
        }
        case 3:{
            do{
                cout << "1 - Between Municipalities" << endl;
                cout << "2 - Between Districts" << endl;
                cout << "Option:" << endl;
                cin >> this->option;

                if (this->option < 1 || this->option > 2) {
                    cout << "Invalid Option!" << endl;
                }

                cin.clear(); // clear input buffer to restore cin to a usable state
                cin.ignore(1000, '\n'); // ignore last input

            } while(this->option < 1 || this->option > 3);

            string number;
            vector<string> res;

            switch(this->option){
                case 1:{

                    cout << "How many municipalities do you want to cover?" << endl;
                    getline(cin, number);

                    int k = stoi(number);
                    res = railway.topKMunicipalities(k);

                    cout << "These are the top-" << number << " of municipalities where management should assign the most budget" << endl;
                    for (string s: res){
                        cout << s << " | ";
                    }
                    cout << endl; cout << endl;

                    break;
                }
                case 2:{
                    cout << "How many districts do you want to cover?" << endl;
                    getline(cin, number);

                    int k = stoi(number);
                    if (k < 1 || k > 17) {
                        cout << "Invalid number!" << endl;
                        break;
                    }
                    res = railway.topKDistricts(k);
                    cout << "These are the top-" << number << " of districts where management should assign the most budget" << endl;
                    for (string s: res){
                        cout << s << " | ";
                    }
                    cout << endl; cout << endl;

                    break;
                }
            }
            break;

        }
        case 4:{
            string station1;

            do {
                cout << "Destination Station: ";
                getline(cin, station1);

                if (!railway.stationExists(station1)) {
                    cout << "Invalid Station!" << endl;
                }

            } while(!railway.stationExists(station1));

            cout << railway.maxNumberOfTrainsArriving(station1) << endl;

            cout << "Press enter to continue..." << endl;
            std::cin.get(); // wait for user input
            break;

        }
        case 5:{
            //back
            menuState.pop();
            break;
        }
        case 6:{
            //exit
            clearStack();
            break;
        }
    }

    getMenu();
}

void Menu::operationsCostOptimization() {
    do{
        cout << "Operations Cost Optimization" << endl;
        cout << "1 - Max number of trains with minimum cost for the company" << endl;
        cout << "2 - Back" << endl;
        cout << "3 - Exit" << endl;
        cout << "Option: ";
        cin >> this->option;

        if (this->option < 1 || this->option > 3) {
            cout << "Invalid Option!" << endl;
        }

        cin.clear(); // clear input buffer to restore cin to a usable state
        cin.ignore(1000, '\n'); // ignore last input

    } while (this->option < 1 || this->option > 3);

    switch (option) {
        case 1: {
            string station1, station2;

            do {
                cout << "Origin Station: ";
                getline(cin, station1);
                cout << "Destination Station: ";
                getline(cin, station2);

                if (!railway.stationExists(station1) || !railway.stationExists(station2)) {
                    cout << "Invalid Station!" << endl;
                }

            } while (!railway.stationExists(station1) || !railway.stationExists(station2));

            pair<int, double> result = railway.operationCost(station1, station2);
            cout << result.first << " trains can simultaneously travel between "<< station1 << " and " << station2 << " with a cost of " << result.second << endl;

            cout << "Press enter to continue..." << endl;
            std::cin.get(); // wait for user input
            break;
        }

        case 2:{
            //back
            menuState.pop();
            break;
        }

        case 3:{
            //exit
            clearStack();
            break;
        }
    }

    getMenu();
}

void Menu::reliabilityAndSensitivityToLineFailures() {
    do{
        cout << "Line Reliability and Sensitivity" << endl;
        cout << "1 - Max Trains on a subgraph" << endl;
        cout << "2 - Report of most affected stations" << endl;
        cout << "3 - Back" << endl;
        cout << "4 - Exit" << endl;
        cout << "Option: ";
        cin >> this->option;

        if (this->option < 1 || this->option > 4) {
            cout << "Invalid Option!" << endl;
        }

        cin.clear(); // clear input buffer to restore cin to a usable state
        cin.ignore(1000, '\n'); // ignore last input

    } while(this->option < 1 || this->option > 4);

    switch (option) {
        case 1:{
            menuState.push(SUBGRAPH_MAX_TRAINS);
            break;
        }
        case 2:{
            //carol
            break;
        }

        case 3:{
            //back
            menuState.pop();
            break;
        }

        case 4:{
            //exit
            clearStack();
            break;
        }
    }

    getMenu();

}

void Menu::subgraphMaxTrains() {
    do{
        cout << "Max Trains on a subgraph" << endl;
        cout << "1 - Disable a station on the subgraph" << endl;
        cout << "2 - Disable a line on the subgraph" << endl;
        cout << "3 - Calculate Max Number of Trains in Subgraph" << endl;
        cout << "3 - Back" << endl;
        cout << "4 - Exit" << endl;
        cout << "Option: ";
        cin >> this->option;

        if (this->option < 1 || this->option > 4) {
            cout << "Invalid Option!" << endl;
        }

        cin.clear(); // clear input buffer to restore cin to a usable state
        cin.ignore(1000, '\n'); // ignore last input
    } while(this->option < 1 || this->option > 4);

    switch(option){
        case 1:{
            string station;
            do {
                cout << "Station: ";
                getline(cin, station);

                if (!railway.stationExists(station)) {
                    cout << "Invalid Station!" << endl;
                }

            } while(!railway.stationExists(station));

            if(!railway.disableStation(station)){
                cout << "Station does not exist!" << endl;
            }

            break;
        }

        case 2:{
            string station1, station2;

            do {
                cout << "Origin Station: ";
                getline(cin, station1);
                cout << "Destination Station: ";
                getline(cin, station2);

                if (!railway.stationExists(station1) || !railway.stationExists(station2)) {
                    cout << "Invalid Station!" << endl;
                }

            } while (!railway.stationExists(station1) || !railway.stationExists(station2));

            if(!railway.disableLine(station1, station2)){
                cout << "Line does not exist! Please make sure the line is a direct connection between two Stations" << endl;
            }

            break;
        }
        case 3:{
            cout << "This may take a while :)" << endl;
            cout << "Should take around 1 minute" << endl;

            std::vector<pair<double, string>> result = railway.mostAmountOfTrains();

            for (int i = 0; i < 10; i++) {
                auto s = result.at(i);
                cout << "  " << s.first << " " << s.second <<'\n';
            }
            cout << "Press enter to continue..." << endl;
            std::cin.get(); // wait for user input
            railway.resetGraph();
            break;
        }
        case 4:
            menuState.pop();
            break;
        case 5:
            clearStack();
            break;
    }

    getMenu();
}

void Menu::clearStack() {
    while(!this->menuState.empty()){
        this->menuState.pop();
    }
}
