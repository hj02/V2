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
    void waitForPrompt(); // waits until the user presses enter
    int respondToMessage();
    void toLower(std::string& str);
    void firstToUpper(std::string& finding);
    bool dateTrue(std::string date);// Check if the date is on the right format
    bool yearTrue(std::string year);// Check if the year is on the right format
    void search_intro(std::string& searchTerm, std::string& ShowComp);
    void error(std::runtime_error);
    void error2(std::string& input, std::string err);

    int SCIENTIST();
    void ADD_SCIENTIST();
    void SEARCH_SCIENTIST();
    void SearchWithID_SCIENTIST();
    void ORDER_SCIENTIST();
    bool EXISTENCE_SCIENTIST(std::string sID);


    int COMPUTER();
    void ADD_COMPUTER();
    void SEARCH_COMPUTER();
    void SearchWithID_COMPUTER();
    void ORDER_COMPUTER();
    bool EXISTENCE_COMPUTER(std::string cID);

    void CONNECT();



};
#endif // CONSOLEUI_H
