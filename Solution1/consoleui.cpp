#include "consoleui.h"
#include <iostream>
#include <string>
#include "menus.h"
#include <stdexcept>
#include <sstream>
#include <iomanip>

ConsoleUI::ConsoleUI() {
    scienceService = ScienceService();
}

ConsoleUI::~ConsoleUI() {
}

int ConsoleUI::start() {
    // REPL
    scienceService.OPEN();
    while(true) {
        int response = respondToMessage();
        if( response == 0)
        {
            return 0;
        }
    }

    return 1;
}

void ConsoleUI::clear() {
    // Not pretty, but it is platform independant
    std::cout << std::string( 100, '\n' );
}

void ConsoleUI::waitForPrompt() {
    std::cout << "\nPress enter to continue..." << std::endl;
    std::cin.ignore();
    std::cin.get();
}

int ConsoleUI::respondToMessage() {

    std::cout << INTRO << std::endl;
    std::string computerVSscientist;
    std::cin >> computerVSscientist;
    toLower(computerVSscientist);
    clear();

    if(computerVSscientist.find("scientist") != std::string::npos){

    std::cout << MAIN_MENU1 << std::endl;

    std::string userRequest;
    std::cin >> userRequest;
    toLower(userRequest);


    try {
        // Handle all available commands and throw error on unknown ones
        if(userRequest.find("add") != std::string::npos) {
            clear();
            std::string DOB, DOD, GENDER;
            int err=1;
            Scientist additionalScientist = Scientist();
            std::cout << "Enter the name of the scientist: ";
            std::cin.ignore();
            std::getline(std::cin, additionalScientist.name);
            //clear();
            std::cout << "Enter the date of birth of the scientist.\n";
            do{
            std::cout << "The format must be yyyy-mm-dd: ";
            std::cin >> DOB;
            }while (!dateTrue(DOB));
            DOB = additionalScientist.dateOfBirth;
            //clear();
            std::cout << "Enter the date of death of the scientist.\n";
            do{
            std::cout << "The format must be yyyy-mm-dd: ";
            std::cin >> DOD;
            }while (!dateTrue(DOD));

            DOD= additionalScientist.dateOfDeath;
            //clear();
            std::cout << "Enter the gender of the scientist.\n";

            while(err==1){
            std::cout << "Enter 'female' or 'male': ";
            std::cin >> GENDER;
            toLower(GENDER);
            if(GENDER=="female" || GENDER=="male"){
            additionalScientist.gender=GENDER;
            err=0;
            }else{std::cout << "Error. You can't enter " + GENDER + ".\n";
             }
            }
            scienceService.addScientist(additionalScientist);
            clear();
        } else if(userRequest.find("search") != std::string::npos) {
            clear();
            std::string searchTerm = "";
            std::cout << "Enter the search term: ";
            std::cin.ignore();
            std::getline(std::cin,searchTerm);
            clear();
            std::list<Scientist> s = scienceService.searchScientist(searchTerm);
            if(s.size() > 0) {
                std::cout << "Scientist found!!" << std::endl;
                std::cout << std::left << std::setw(30) << "Name" << std::left << std::setw(15)  <<"DateOfBirth:" << std::left << std::setw(15) << "DateOfDeath:" << std::left << std::setw(15)<<  "Gender:"<< std::endl << std::endl;
                for(std::list<Scientist>::iterator iter = s.begin(); iter != s.end(); iter ++) {
                std::cout << std::left << std::setw(30) <<  iter->name << std::left << std::setw(15) << iter->dateOfBirth << std::left << std::setw(15)<< iter->dateOfDeath << std::left << std::setw(15) <<  iter->gender  << std::endl;
                }
            }
            else {
                 std::cout << "No results found for the term: " << searchTerm << std::endl;
            }
            waitForPrompt();
            clear();
        } else if(userRequest.find("order") != std::string::npos) {
            clear();
            std::string filterCol = "";
            std::string filterMod = "";
            std::cout << FILTER_MENU1 << std::endl;
            std::cin >> filterCol >> filterMod;
            toLower(filterCol);
            toLower(filterMod);
            clear();
            std::list<Scientist> l = scienceService.getScientistsOrderedBy(filterCol,filterMod);
            std::cout << std::left << std::setw(30) << "Name:" << std::left << std::setw(15)  <<"DateOfBirth:" << std::left << std::setw(15) << "DateOfDeath:" << std::left << std::setw(15)<<  "Gender:"<<std::endl<< std::endl;
            for(std::list<Scientist>::iterator iter = l.begin(); iter != l.end(); iter ++) {
              std::cout << std::left << std::setw(30) <<  iter->name << std::left << std::setw(15) << iter->dateOfBirth << std::left << std::setw(15)<< iter->dateOfDeath << std::left << std::setw(15) <<  iter->gender  << std::endl;
            }
            waitForPrompt();
            clear();
        } else if (userRequest.find("exit") != std::string::npos) {
            return 0;
        } else {
            throw std::runtime_error( userRequest + " is not a valid command.");
        }
    } catch(std::runtime_error e) {
        clear();
        std::cout << "Command caused an error: " << e.what() << std::endl;
        std::cout << "Please try another command" << std::endl;
        waitForPrompt();
        clear();
    }

    }

    if(computerVSscientist.find("computer") != std::string::npos){

    std::cout << MAIN_MENU2 << std::endl;

    std::string userRequest;
    std::cin >> userRequest;
    toLower(userRequest);

    try {
        // Handle all available commands and throw error on unknown ones
        if(userRequest.find("add") != std::string::npos) {
            clear();
            std::string YEAR, BUILT;
            Computer additionalComputer = Computer();
            std::cout << "Enter the name of the computer: ";
            std::cin.ignore();
            std::getline(std::cin, additionalComputer.brand);
            //clear();
            std::cout << "Enter the year of the computer: ";
            std::cin >> YEAR;
            while(!yearTrue(YEAR)){
            std::cout << "ERROR! You must enter digits!\n";
            std::cout << "Enter the year of the computer: ";
            std::cin >> YEAR;
            }
            YEAR =additionalComputer.year;
            //clear();
            std::cout << "Enter the type of the computer: ";
            std::cin.ignore();
            std::getline(std::cin, additionalComputer.type);
            //clear();
            std::cout << "Was the computer built? ";
            std::cin >> BUILT;
            toLower(BUILT);
            while(BUILT!="yes" && BUILT!="no" ){
            std::cout << "Please choose between 'yes' or 'no': ";
            std::cin >> BUILT;
            toLower(BUILT);
            }
            additionalComputer.built=BUILT;
            scienceService.addComputer(additionalComputer);
            clear();
        } else if(userRequest.find("search") != std::string::npos) {
            clear();
            std::string searchTerm = "";
            std::cout << "Enter the search term: ";
            std::cin.ignore();
            std::getline(std::cin,searchTerm);
            clear();
            std::list<Computer> co = scienceService.searchComputer(searchTerm);
            if(co.size() > 0) {
                std::cout << "Computer found!!" << std::endl;
                std::cout << std::left << std::setw(30) << "Brand:" << std::left << std::setw(8)  <<"Year:" << std::left << std::setw(30) << "Type:" << std::left << std::setw(8)<<  "Built?" << std::endl << std::endl;
                for(std::list<Computer>::iterator iter = co.begin(); iter != co.end(); iter ++) {
                std::cout << std::left << std::setw(30) << iter->brand << std::left << std::setw(8) << iter->year << std::left << std::setw(30)<< iter->type << std::left << std::setw(8)<< iter->built << std::endl;
                }
            }
            else {
                 std::cout << "No results found for the term: " << searchTerm << std::endl;
            }
            waitForPrompt();
            clear();

        } else if(userRequest.find("order") != std::string::npos) {
            clear();
            std::string filterCol = "";
            std::string filterMod = "";
            std::cout << FILTER_MENU2 << std::endl;
            std::cin >> filterCol >> filterMod;
            toLower(filterCol);
            toLower(filterMod);
            clear();
            std::list<Computer> l = scienceService.getComputersOrderedBy(filterCol,filterMod);
            std::cout << std::left << std::setw(30)<< "Brand:" << std::left << std::setw(8) << "Year:" << std::left << std::setw(30) << "Type:" << std::left << std::setw(8) << "Built?" << std::endl << std::endl;
            for(std::list<Computer>::iterator iter = l.begin(); iter != l.end(); iter ++) {
                std::cout << std::left << std::setw(30)<< iter->brand << std::left << std::setw(8) << iter->year << std::left << std::setw(30) << iter->type << std::left << std::setw(8) << iter->built << std::endl;
            }
            waitForPrompt();
            clear();
        } else if (userRequest.find("exit") != std::string::npos) {
            return 0;
        } else {
            throw std::runtime_error( userRequest + " is not a valid command.");
        }
    } catch(std::runtime_error e) {
        clear();
        std::cout << "Command caused an error: " << e.what() << std::endl;
        std::cout << "Please try another command" << std::endl;
        waitForPrompt();
        clear();
      }
    }
    if (computerVSscientist.find("exit") != std::string::npos) {
               return 0;

    }

    return 1;
}


void ConsoleUI::toLower(std::string& str){

    int a = str.size();
    for(int i=0; i<a; i++){

        str[i]=tolower(str[i]);

    }


}
bool ConsoleUI::dateTrue(std::string date){
    int T=0;

    if(date.size()==10){
        for(int i=0; i<4; i++){
           if(isdigit(date[i]))
               T=1;
           else{
               T=0;
               break;
           }
        }
        if(T==1){
            if(date[4]=='-' && date[7]=='-'){
                if(isdigit(date[5]) && isdigit(date[6])){
                    if(isdigit(date[8]) && isdigit(date[9])){
                        return true;
                    }
                }
            }
        }
    }
  return false;
}

bool ConsoleUI::yearTrue(std::string year){

    int T=0;
    int s = year.size();
    for(int i=0; i<s; i++){
         if(isdigit(year[i]))
                T=1;
         else {T=0;
         break;}
        }

    if(T==1) return true;

    return false;
}

