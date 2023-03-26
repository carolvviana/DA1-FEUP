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
        }
    } else exit(0);
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
        cout << "1 - Show all stations" << endl;
        cout << "2 - Show all lines" << endl;
        cout << "3 - Return" << endl;
        cout << "4 - Exit" << endl;
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
            string a = "Alferrarede";
            string b = "Fratel";
            std::vector<string> r = railway.mostAmountOfTrains();
            for (auto s: r){
                cout << "  " << s << "  |" <<'\n';
            }
            break;
        }
        case 2: {

            break;
        }
        case 3: {
            menuState.pop();
            break;
        }
        case 4: {
            exit(0);
        }
    }

    getMenu();
}