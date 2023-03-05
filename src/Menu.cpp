//
// Created by Sergio on 05/03/2023.
//

#include "Menu.h"

using namespace std;

Menu::Menu() {
    this->menuState.push(MAIN_MENU);

    getMenu();
}

void Menu::getMenu() {
    if(!this->menuState.empty()){
        switch(this->menuState.top()){
            case MAIN_MENU: mainMenu(); break;
        }
    } else exit(0);
}

void Menu::mainMenu() {

    do {
        /* EXEMPLO */
        cout << "1 - Option 1" << endl;
        cout << "2 - Option 2" << endl;
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
        case 1:
            // TODO push para o menu da opção 1
            break;
        case 2:
            // TODO push para o menu da opção 2
            break;
        case 3:
            menuState.pop();
            break;
    }

    getMenu();
}