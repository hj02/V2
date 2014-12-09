#include "consoleui.h"
#include "menus.h"

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
      return SCIENTIST();
    }
    if(computerVSscientist.find("computer") != std::string::npos){
      return COMPUTER();
    }
    if(computerVSscientist.find("connect") != std::string::npos){
        CONNECT();
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
    int SIZE = year.size();

    if(SIZE == 4)
    {
        int T=0;
        int s = year.size();
        for(int i=0; i<s; i++){
             if(isdigit(year[i]))
                    T=1;
             else {T=0;
             break;}
            }
        if(T==1) return true;
    }
    return false;
}

int ConsoleUI::SCIENTIST(){
    std::cout << MAIN_MENU1 << std::endl;
    std::string userRequest;
    std::cin >> userRequest;
    toLower(userRequest);
    try {
        // Handle all available commands and throw error on unknown ones
        if(userRequest.find("add") != std::string::npos) {
            ADD_SCIENTIST();
        } else if(userRequest.find("search") != std::string::npos) {
            SEARCH_SCIENTIST();
        } else if(userRequest.find("order") != std::string::npos) {
            ORDER_SCIENTIST();
        } else if (userRequest.find("exit") != std::string::npos) {
            return 0;
        } else {
            throw std::runtime_error( userRequest + " is not a valid command");
        }
    }  catch(std::runtime_error e) {
        ERROR(e);
    }
    return 1;
}

void ConsoleUI::ADD_SCIENTIST(){
    clear();
    std::string NAME,DOB, DOD, GENDER;
    int err=1;
    Scientist additionalScientist = Scientist();
    std::cout << "Enter the name of the scientist: ";
    std::cin.ignore();
    std::getline(std::cin,NAME);
    toLower(NAME);
    firstToUpper(NAME);
    additionalScientist.name = NAME;
    std::cout << "Enter the date of birth of the scientist:\n";
    do{
        std::cout << "The format must be yyyy-mm-dd: ";
        std::cin >> DOB;
    }while (!dateTrue(DOB));
    additionalScientist.dateOfBirth = DOB;
    std::cout << "Enter the date of death of the scientist:\n";
    do{
        std::cout << "The format must be yyyy-mm-dd: ";
        std::cin >> DOD;
    }while (!dateTrue(DOD));
    additionalScientist.dateOfDeath = DOD;
    std::cout << "Enter the gender of the scientist:\n";
    while(err==1){
        std::cout << "Enter 'female' or 'male': ";
        std::cin >> GENDER;
        toLower(GENDER);
        if(GENDER=="female" || GENDER=="male"){
            additionalScientist.gender=GENDER;
            err=0;
        }else{std::cout << "Error. You can't enter " + GENDER + "\n";
        }
    }
    scienceService.addScientist(additionalScientist);
    clear();
}

void ConsoleUI::SEARCH_SCIENTIST(){
    clear();
    std::string ShowComp = "";
    std::string searchTerm = "";
    std::cout << "Enter the search term: ";
    std::cin.ignore();
    std::getline(std::cin,searchTerm);
    clear();
    std::cout << "Do you want to see if the scientist is connected a computer?(y/n): ";
    std::cin >> ShowComp;
    std::list<Scientist> s = scienceService.searchScientist(searchTerm, ShowComp);
    if(s.size() > 0) {
        std::cout << "Scientist found!!" << std::endl;
        if(ShowComp == "N" || ShowComp == "n"){
            std::cout << std::left << std::setw(30) << "Name:" << std::left << std::setw(15)
                      <<"DateOfBirth:" << std::left << std::setw(15) << "DateOfDeath:"
                      << std::left << std::setw(15)<<  "Gender:"<< std::endl << std::endl;
            for(std::list<Scientist>::iterator iter = s.begin(); iter != s.end(); iter ++){
                std::cout << std::left << std::setw(30) <<  iter->name << std::left << std::setw(15)
                          << iter->dateOfBirth << std::left << std::setw(15)<< iter->dateOfDeath
                          << std::left << std::setw(15) <<  iter->gender  << std::endl;
            }
        }
        else {
                std::cout << std::left << std::setw(27) << "Name:" << std::left << std::setw(14)
                          <<"DateOfBirth:" << std::left << std::setw(14) << "DateOfDeath:" << std::left
                          << std::setw(12)<<  "Gender:"<< std::left << std::setw(9) << "Brand:"
                          << std::endl << std::endl;
                for(std::list<Scientist>::iterator iter = s.begin(); iter != s.end(); iter ++){
                    std::cout << std::left << std::setw(27) <<  iter->name << std::left << std::setw(14)
                              << iter->dateOfBirth << std::left << std::setw(14)<< iter->dateOfDeath
                              << std::left << std::setw(9) <<  iter->gender << std::left << std::setw(12)
                              << iter->brand << std::endl;
                }
             }
        }
        else{
            std::cout << "No results found for the term " << searchTerm << std::endl;
            }
        waitForPrompt();
        clear();
}

void ConsoleUI::ORDER_SCIENTIST(){
    clear();
    std::string filterCol = "";
    std::string filterMod = "";
    std::cout << FILTER_MENU1 << std::endl;
    std::cin >> filterCol >> filterMod;
    toLower(filterCol);
    toLower(filterMod);
    clear();
    std::list<Scientist> l = scienceService.getScientistsOrderedBy(filterCol,filterMod);
    std::cout << std::left << std::setw(30) << "Name:" << std::left << std::setw(15)
              <<"DateOfBirth:" << std::left << std::setw(15) << "DateOfDeath:"
              << std::left << std::setw(15)<<  "Gender:"<<std::endl<< std::endl;
    for(std::list<Scientist>::iterator iter = l.begin(); iter != l.end(); iter ++) {
        std::cout << std::left << std::setw(30) <<  iter->name << std::left << std::setw(15)
                  << iter->dateOfBirth << std::left << std::setw(15)<< iter->dateOfDeath
                  << std::left << std::setw(15) <<  iter->gender  << std::endl;
    }
    waitForPrompt();
    clear();
}

void ConsoleUI::ERROR(std::runtime_error e){
            clear();
            std::cout << "Command caused an error: " << e.what() << std::endl;
            std::cout << "Please try another command: " << std::endl;
            waitForPrompt();
            clear();
}

int ConsoleUI::COMPUTER(){
    std::cout << MAIN_MENU2 << std::endl;
    std::string userRequest;
    std::cin >> userRequest;
    toLower(userRequest);
    try {
        // Handle all available commands and throw error on unknown ones
        if(userRequest.find("add") != std::string::npos) {
            ADD_COMPUTER();
        } else if(userRequest.find("search") != std::string::npos) {
            SEARCH_COMPUTER();
        } else if(userRequest.find("order") != std::string::npos) {
           ORDER_COMPUTER();
        } else if (userRequest.find("exit") != std::string::npos) {
            return 0;
        } else {
            throw std::runtime_error( userRequest + " is not a valid command");
        }
    } catch(std::runtime_error e) {
       ERROR(e);
      }
    return 1;
}

void ConsoleUI::ADD_COMPUTER(){
    clear();
    std::string BRAND, YEAR, TYPE, BUILT;
    Computer additionalComputer = Computer();
    std::cout << "Enter the name of the computer: ";
    std::cin.ignore();
    std::getline(std::cin, BRAND);
    toLower(BRAND);
    firstToUpper(BRAND);
    additionalComputer.brand = BRAND;
    std::cout << "Enter the year of the computer: ";
    std::cin >> YEAR;
    while(!yearTrue(YEAR)){
        std::cout << std::endl << "ERROR! You must enter digits with the format 'yyyy'!\n";
        std::cout << "Example: 0019 or 1999"<< std::endl<< std::endl;
        std::cout << "Enter the year of the computer: ";
        std::cin >> YEAR;
    }
    additionalComputer.year = YEAR;
    std::cout << "Enter the type of the computer: ";
    std::cin.ignore();
    std::getline(std::cin, TYPE);
    toLower(TYPE);
    firstToUpper(TYPE);
    additionalComputer.type = TYPE;
    std::cout << "Was the computer built?(yes/no): ";
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
}

void ConsoleUI::SEARCH_COMPUTER(){
    clear();
    std::string searchTerm = "";
    std::string ShowComp = "";
    std::cout << "Enter the search term: ";
    std::cin.ignore();
    std::getline(std::cin,searchTerm);
    clear();
    std::cout << "Do you want to see if the computer is connected to a scientist?(y/n): ";
    std::cin >> ShowComp;
    std::list<Computer> co = scienceService.searchComputer(searchTerm, ShowComp);
    if(co.size() > 0) {
        std::cout << "Computer found!!" << std::endl;
        if(ShowComp == "N" || ShowComp == "n")
        {
            std::cout << std::left << std::setw(30) << "Brand:" << std::left << std::setw(8)
                      <<"Year:" << std::left << std::setw(30) << "Type:" << std::left << std::setw(8)
                      <<"Built?:" << std::endl << std::endl;
            for(std::list<Computer>::iterator iter = co.begin(); iter != co.end(); iter ++)
            {
            std::cout << std::left << std::setw(30) << iter->brand << std::left << std::setw(8)
                      << iter->year << std::left << std::setw(30)<< iter->type << std::left
                      << std::setw(8)<< iter->built << std::endl;
            }
        }
        else
        {
            std::cout << std::left << std::setw(15) << "Brand:" << std::left << std::setw(6)
                      <<"Year:" << std::left << std::setw(30) << "Type:" << std::left << std::setw(8)
                      <<"Built?" << std::left << std::setw(20) << "Name:" << std::endl << std::endl;
            for(std::list<Computer>::iterator iter = co.begin(); iter != co.end(); iter ++)
            {
                std::cout << std::left << std::setw(15) << iter->brand << std::left << std::setw(6)
                          << iter->year << std::left << std::setw(30)<< iter->type << std::left
                          << std::setw(8)<< iter->built << std::left << std::setw(20) << iter->name
                          << std::endl;
            }
        }
   }
    else {
         std::cout << "No results found for the term: " << searchTerm << std::endl;
    }
    waitForPrompt();
    clear();
}

void ConsoleUI::ORDER_COMPUTER(){
    clear();
    std::string filterCol = "";
    std::string filterMod = "";
    std::cout << FILTER_MENU2 << std::endl;
    std::cin >> filterCol >> filterMod;
    toLower(filterCol);
    toLower(filterMod);
    clear();
    std::list<Computer> l = scienceService.getComputersOrderedBy(filterCol,filterMod);
    std::cout << std::left << std::setw(30)<< "Brand:" << std::left << std::setw(8)
              << "Year:" << std::left << std::setw(30) << "Type:" << std::left
              << std::setw(8) << "Built?" << std::endl << std::endl;
    for(std::list<Computer>::iterator iter = l.begin(); iter != l.end(); iter ++) {
        std::cout << std::left << std::setw(30)<< iter->brand << std::left << std::setw(8)
                  << iter->year << std::left << std::setw(30) << iter->type << std::left
                  << std::setw(8) << iter->built << std::endl;
    }
    waitForPrompt();
    clear();
}

void ConsoleUI::CONNECT(){
    QSqlQuery query;
    std::string sconnect;
    std::string cconnect;
    std::string searchterm;
    std::string option;
    std::string option2;
    std::cout << "Do you want to search first for a scientist or a computer (y/n): ";
    std::cin >> option;
    toLower(option);
    while(option != "y" && option != "n"){
        std::cout << "ERROR Not a valid command" << std::endl;
        std::cout << "Please try again: " << std::endl;
        std::cin >> option;
        toLower(option);
    }
    if(option == "y"){
            clear();
            std::cout << "Dou you want to search for a scientist or a computer (scientist/computer): " << std::endl;
            std::cin >> option2;
            toLower(option2);
            while(option2 != "scientist" && option2 != "computer"){
                std::cout << "ERROR Not a valid command" << std::endl;
                std::cout << "Please try again: " << std::endl;
                std::cin >> option2;
                toLower(option2);
            }
            if(option2 == "scientist"){
                std::cout << "Please enter a serch therm for scientist: ";
                SEARCH_SCIENTIST();
            }else if(option2 == "computer"){
                std::cout << "Please enter a serch therm for computer: ";
                SEARCH_COMPUTER();
            }
     }
    std::cout << "Enter the ID of Scientist: " << std::endl;
    std::cin >> sconnect;
    query.prepare("SELECT :id in (SELECT ID FROM Scientist) AS RES");
    query.bindValue(":id", QString::fromStdString(sconnect));
    query.exec();
    query.next();
    std::string res = query.value("RES").toString().toStdString();
    int value = atoi(res.c_str());
    while(!value){
        std::cout << "This is scientist does not exist!" << std::endl;
        std::cout << "Enter the ID of Scientist: " << std::endl;
        std::cin >> sconnect;
        query.prepare("SELECT :id in (SELECT ID FROM Scientist)AS RES");
        query.bindValue(":id", QString::fromStdString(sconnect));
        query.exec();
        query.next();
        res = query.value("RES").toString().toStdString();
        value = atoi(res.c_str());
    }
    std::cout << "Enter the ID of Computer: " << std::endl;
    std::cin >> cconnect;
    query.prepare("SELECT :id2 in (SELECT ID FROM Computer) AS RES2");
    query.bindValue(":id2", QString::fromStdString(cconnect));
    query.exec();
    query.next();
    std::string res2 = query.value("RES2").toString().toStdString();
    int value2 = atoi(res2.c_str());
    while(!value2){
        std::cout << "This is computer does not exist!"<< std::endl;
        std::cout << "Enter the ID of Computer: " << std::endl;
        std::cin >> cconnect;
        query.prepare("SELECT :id2 in (SELECT ID FROM Computer) AS RES2");
        query.bindValue(":id2", QString::fromStdString(cconnect));
        query.exec();
        query.next();
        res2 = query.value("RES2").toString().toStdString();
        value2 = atoi(res2.c_str());
    }
    scienceService.connect(sconnect, cconnect);
    std::cout <<"Thank you, you have connected scientist with ID no. "
              << sconnect << " to computer with ID no. "
              << cconnect << std::endl;
    waitForPrompt();
    clear();
}

void ConsoleUI::firstToUpper(std::string& finding){
    int teljari = -1;
    int lengd = finding.length();
    finding[0] = toupper(finding[0]);
    for(int i = 0; i < lengd; i++)
    {
        if(isspace(finding[i]))
        {
          teljari = teljari -1;
        }
        if(teljari < -1)
        {
            finding[i+1] = toupper(finding[i+1]);
            teljari = -1;
        }
    }
}
