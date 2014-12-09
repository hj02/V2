#ifndef CONSOLEUI_H
#define CONSOLEUI_H

#include "Scientist.h"
#include "computer.h"
#include <stack>
#include <list>
#include "scienceservice.h"

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
    int respondToMessage();
    void toLower(std::string& str);
    bool dateTrue(std::string date);
    bool yearTrue(std::string year);
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
};

#endif // CONSOLEUI_H
