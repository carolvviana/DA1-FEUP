//
// Created by Sergio on 05/03/2023.
//

#ifndef PROJETO_DA_1_MENU_H
#define PROJETO_DA_1_MENU_H

#include <stack>
#include <iostream>

/*
 * Menu's states
 */
enum MenuState{
    MAIN_MENU // Para adicionar mais menus, basta adicionar aqui
};

/*
 * Menu class to manage interface
 */
class Menu {
private:

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
