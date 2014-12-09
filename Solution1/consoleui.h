#ifndef CONSOLEUI_H
#define CONSOLEUI_H
#include "scienceservice.h"
#include "Scientist.h"
#include "computer.h"
#include <iostream>
#include <iomanip>

// Display layer for the console application
class ConsoleUI {
public:
    ConsoleUI();
    ~ConsoleUI();
    int start();
private:
    ScienceService scienceService;
    void clear();
    void waitForPrompt();
    // waits until the user presses enter
    int respondToMessage();
    void toLower(std::string& str);
    bool dateTrue(std::string date);
    // Check if the date is on the right format
    bool yearTrue(std::string year);
    // Check if the year is on the right format
    int SCIENTIST();
    void ADD_SCIENTIST();
    void SEARCH_SCIENTIST();
    void ORDER_SCIENTIST();
    void ERROR(std::runtime_error);
    int COMPUTER();
    void ADD_COMPUTER();
    void SEARCH_COMPUTER();
    void ORDER_COMPUTER();
    void CONNECT();
    void firstToUpper(std::string& finding);
};
#endif // CONSOLEUI_H
