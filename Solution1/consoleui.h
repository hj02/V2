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
};

#endif // CONSOLEUI_H
