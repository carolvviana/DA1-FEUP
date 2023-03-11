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
    MAIN_MENU // To add more menus, just add here
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

public:
    /**
     * Constructor of Menu class
     */
    Menu();
};


#endif //PROJETO_DA_1_MENU_H
