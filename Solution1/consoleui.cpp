#include "consoleui.h"
#include "menus.h"

ConsoleUI::ConsoleUI(){
    scienceService = ScienceService();
}

ConsoleUI::~ConsoleUI() {

}

int ConsoleUI::start(){
    scienceService.open();
    // REPL
    while(true) {
        int response = respondToMessage();

        if( response == 0){
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

void ConsoleUI::firstToUpper(std::string& finding){

    int teljari = -1;
    int lengd = finding.length();
    finding[0] = toupper(finding[0]);

    for(int i = 0; i < lengd; i++){
        if(isspace(finding[i])){

            teljari = teljari -1;
        }
        if(teljari < -1){

            finding[i+1] = toupper(finding[i+1]);
            teljari = -1;
        }
    }
}

bool ConsoleUI::dateTrue(std::string date){
    int T=0;
    if(date.size()==10){ // the string must have exactly 10 characters

        for(int i=0; i<4; i++){ // the first four characters must be digits

            if(isdigit(date[i]))

                T=1;
            else{

                T=0;
                break;
            }
        }
        if(T==1){

            if(date[4]=='-' && date[7]=='-'){ // 5th and 8th character must be '-'

                if(isdigit(date[5]) && isdigit(date[6])){ // 6th and 7th character must be digits

                    if(isdigit(date[8]) && isdigit(date[9])){ // 9th and 10th characther must be digits

                        return true; //if every if statement is true then the date is in right format and function returns true
                    }
                }
            }
        }
    }
    return false; // if not every if statement is true then the function returns false
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

void ConsoleUI::error(std::runtime_error e){
    clear();

    std::cout << "Command caused an error: " << e.what() << std::endl;
    std::cout << "Please try another command: " << std::endl;

    waitForPrompt();
    clear();
}

void ConsoleUI::error2(std::string& input, std::string err){

    std::cout << std::endl<< "ERROR! Please enter " << err << ": ";
    std::cin >> input;
    toLower(input);


}

void ConsoleUI::search_intro(std::string& searchTerm, std::string& ShowComp){

    std::cout << "Enter the search term: ";
    std::cin.ignore();
    std::getline(std::cin,searchTerm);
    clear();

    std::cout << "Do you want to see if the computer is connected to a scientist?(y/n): ";
    std::cin >> ShowComp;
    toLower(ShowComp);

    while(ShowComp != "y" && ShowComp != "n"){

        error2(ShowComp, "'y' or 'n'");
    }

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
    } catch(std::runtime_error e) {

        error(e);
    }

    return 1;
}

void ConsoleUI::ADD_SCIENTIST(){
    clear();

    int err=1;
    Scientist additionalScientist = Scientist();

    std::cout << "Enter the name of the scientist: ";
    std::cin.ignore();
    std::string NAME = "";
    std::getline(std::cin,NAME);

    toLower(NAME);
    firstToUpper(NAME);
    additionalScientist.name = NAME;

    std::string DOB = "";
    std::cout << "Enter the date of birth of the scientist:\n";
    do{

        std::cout << "The format must be yyyy-mm-dd: ";
        std::cin >> DOB;

       }while (!dateTrue(DOB));

    additionalScientist.dateOfBirth = DOB;

    std::string DOD = "";
    std::cout << "Enter the date of death of the scientist:\n";
    do{

        std::cout << "The format must be yyyy-mm-dd: ";
        std::cin >> DOD;

      }while (!dateTrue(DOD));

    additionalScientist.dateOfDeath = DOD;
    std::cout << "Enter the gender of the scientist:\n";

    while(err==1){

        std::cout << "Enter 'female' or 'male': ";
        std::string GENDER;
        std::cin >> GENDER;
        toLower(GENDER);

        if(GENDER=="female" || GENDER=="male"){

            additionalScientist.gender=GENDER;
            err=0;

        }
        else{

            std::cout << "Error. You can't enter " + GENDER + "\n";

        }
    }

    scienceService.addScientist(additionalScientist);
    clear();
}

void ConsoleUI::SEARCH_SCIENTIST(){
    clear();

    std::string ShowComp = "";
    std::string searchTerm = "";

    search_intro(searchTerm, ShowComp);

    std::list<Scientist> s = scienceService.searchScientist(searchTerm, ShowComp);

    if(s.size() > 0) {
        std::cout << "Scientist found!!" << std::endl;
        if(ShowComp == "n"){

            std::cout << std::left << std::setw(30) << "Name:" << std::left << std::setw(15) <<"DateOfBirth:" ;
            std:: cout << std::left << std::setw(15) << "DateOfDeath:" << std::left << std::setw(15)<< "Gender:"<< std::endl << std::endl;

            for(std::list<Scientist>::iterator iter = s.begin(); iter != s.end(); iter ++){
                std::cout << std::left << std::setw(30) << iter->name << std::left << std::setw(15) << iter->dateOfBirth;
                std::cout << std::left << std::setw(15)<< iter->dateOfDeath << std::left << std::setw(15) << iter->gender << std::endl;
            }
        }
        else {

            std::cout << std::left << std::setw(27) << "Name:" << std::left << std::setw(14) <<"DateOfBirth:" << std::left << std::setw(14) << "DateOfDeath:";
            std::cout << std::left << std::setw(12)<< "Gender:"<< std::left << std::setw(9) << "Brand:" << std::endl << std::endl;

            for(std::list<Scientist>::iterator iter = s.begin(); iter != s.end(); iter ++){

                std::cout << std::left << std::setw(27) << iter->name << std::left << std::setw(14) << iter->dateOfBirth << std::left << std::setw(14)<< iter->dateOfDeath ;
                std::cout << std::left << std::setw(9) << iter->gender << std::left << std::setw(12) << iter->brand << std::endl;
               }
        }
   }
   else{

        std::cout << "No results found for the term " << searchTerm << std::endl;

    }
    waitForPrompt();
    clear();
}

void ConsoleUI::SearchWithID_SCIENTIST(){
    clear();

    std::string ShowComp = "";
    std::string searchTerm = "";

    search_intro(searchTerm, ShowComp);

    std::list<Scientist> s = scienceService.searchScientist(searchTerm, ShowComp);

    if(s.size() > 0) {
        std::cout << "Scientist found!!" << std::endl;
        if(ShowComp == "n"){

            std::cout << std::left << std::setw(4) << "ID: "<< std::left << std::setw(25) << "Name:" << std::left << std::setw(15) <<"DateOfBirth:" ;
            std::cout << std::left << std::setw(15) << "DateOfDeath:" << std::left << std::setw(15)<< "Gender:"<< std::endl << std::endl;

            for(std::list<Scientist>::iterator iter = s.begin(); iter != s.end(); iter ++){
                std::cout << std::left << std::setw(4) << iter->sID << std::left << std::setw(25) << iter->name << std::left << std::setw(15) << iter->dateOfBirth;
                std::cout << std::left << std::setw(15)<< iter->dateOfDeath << std::left << std::setw(15) << iter->gender << std::endl;
            }
        }
        else {

            std::cout << std::left << std::setw(4) << "ID: " << std::left << std::setw(24) << "Name:" << std::left << std::setw(14) <<"DateOfBirth:" ;
            std::cout << std::left << std::setw(30) << "Brand:" << std::endl << std::endl;

            for(std::list<Scientist>::iterator iter = s.begin(); iter != s.end(); iter ++){

                std::cout << std::left << std::setw(4) << iter->sID << std::left << std::setw(24) << iter->name << std::left << std::setw(14)<< iter->dateOfBirth ;
                std::cout << std::left << std::setw(20) << iter->brand << std::endl;
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

    while((filterCol != "name" && filterCol != "dob" && filterCol != "dod") || (filterCol != "gender" && filterMod != "desc" && filterMod != "asc" )){


         std::cout << std::endl<< "ERROR! Please enter 'name', 'gender', 'dob' or 'dod' for column, and 'asc' or 'desc' for modifier: ";
         std::cin >> filterCol >> filterMod;

         toLower(filterCol);
         toLower(filterMod);


    }

    clear();

    std::list<Scientist> l = scienceService.getScientistsOrderedBy(filterCol,filterMod);

    std::cout << std::left << std::setw(30) << "Name:" << std::left << std::setw(15) <<"DateOfBirth:";
    std::cout << std::left << std::setw(15) << "DateOfDeath:" << std::left << std::setw(15)<< "Gender:"<<std::endl<< std::endl;

    for(std::list<Scientist>::iterator iter = l.begin(); iter != l.end(); iter ++) {

        std::cout << std::left << std::setw(30) << iter->name << std::left << std::setw(15) << iter->dateOfBirth ;
        std::cout << std::left << std::setw(15)<< iter->dateOfDeath << std::left << std::setw(15) << iter->gender << std::endl;
    }

    waitForPrompt();
    clear();
}

bool ConsoleUI::EXISTENCE_SCIENTIST(std::string sID){

    QSqlQuery query;

    query.prepare("SELECT :id2 in (SELECT ID FROM Scientist) AS RES2");
    query.bindValue(":id2", QString::fromStdString(sID));
    query.exec();
    query.next();

    std::string res2 = query.value("RES2").toString().toStdString();
    int value = atoi(res2.c_str());

    return value;

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
            }
            else if(userRequest.find("search") != std::string::npos) {

                SEARCH_COMPUTER();

            }
            else if(userRequest.find("order") != std::string::npos) {

                ORDER_COMPUTER();

            }
            else if (userRequest.find("exit") != std::string::npos) {

                return 0;

            }
            else {

                throw std::runtime_error( userRequest + " is not a valid command");

            }
    } catch(std::runtime_error e) {

        error(e);

    }

    return 1;

}

void ConsoleUI::ADD_COMPUTER(){

    clear();
    Computer additionalComputer = Computer();

    std::cout << "Enter the name of the computer: ";
    std::string BRAND = "";
    std::cin.ignore();
    std::getline(std::cin, BRAND);
    toLower(BRAND);
    firstToUpper(BRAND);
    additionalComputer.brand = BRAND;

    std::cout << "Enter the year of the computer: ";
    std::string YEAR = "";
    std::cin >> YEAR;

    while(!yearTrue(YEAR)){

        std::cout << std::endl << "ERROR! You must enter digits with the format 'yyyy'!\n";
        std::cout << "Example: 0019 or 1999"<< std::endl<< std::endl;
        std::cout << "Enter the year of the computer: ";
        std::cin >> YEAR;
    }

    additionalComputer.year = YEAR;

    std::cout << "Enter the type of the computer: ";
    std::string TYPE = "";
    std::cin.ignore();
    std::getline(std::cin, TYPE);
    toLower(TYPE);
    firstToUpper(TYPE);
    additionalComputer.type = TYPE;

    std::cout << "Was the computer built?(yes/no): ";
    std::string BUILT = "";
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


    search_intro(searchTerm, ShowComp);

    std::list<Computer> co = scienceService.searchComputer(searchTerm, ShowComp);

    if(co.size() > 0) {

        std::cout << "Computer found!!" << std::endl;

        if(ShowComp == "n")
        {
            std::cout << std::left << std::setw(30) << "Brand:" << std::left << std::setw(8) <<"Year:" << std::left << std::setw(30) << "Type:" ;
            std::cout << std::left << std::setw(8) <<"Built?:" << std::endl << std::endl;

            for(std::list<Computer>::iterator iter = co.begin(); iter != co.end(); iter ++)
            {
                std::cout << std::left << std::setw(30) << iter->brand << std::left << std::setw(8) << iter->year ;
                std::cout << std::left << std::setw(30)<< iter->type << std::left << std::setw(8)<< iter->built << std::endl;
            }
        }

        else
        {
            std::cout << std::left << std::setw(15) << "Brand:" << std::left << std::setw(6) <<"Year:" << std::left << std::setw(30) << "Type:";
            std::cout << std::left << std::setw(8) <<"Built?" << std::left << std::setw(20) << "Name:" << std::endl << std::endl;

            for(std::list<Computer>::iterator iter = co.begin(); iter != co.end(); iter ++)
            {
                std::cout << std::left << std::setw(15) << iter->brand << std::left << std::setw(6) << iter->year;
                std::cout << std::left << std::setw(30)<< iter->type << std::left << std::setw(8)<< iter->built << std::left << std::setw(20) << iter->name << std::endl;
            }
        }
    }
    else {

        std::cout << "No results found for the term: " << searchTerm << std::endl;
      }

    waitForPrompt();
    clear();
}

void ConsoleUI::SearchWithID_COMPUTER(){
    clear();

    std::string ShowComp = "";
    std::string searchTerm = "";

    search_intro(searchTerm, ShowComp);

    std::list<Computer> co = scienceService.searchComputer(searchTerm, ShowComp);

    if(co.size() > 0) {

        std::cout << "Computer found!!" << std::endl;

        if(ShowComp == "n")
        {
            std::cout << std::left << std::setw(4) << "ID: " << std::left << std::setw(25) << "Brand:" << std::left << std::setw(8) <<"Year:" << std::left << std::setw(30) << "Type:" ;
            std::cout << std::left << std::setw(8) <<"Built?:" << std::endl << std::endl;

            for(std::list<Computer>::iterator iter = co.begin(); iter != co.end(); iter ++)
            {
                std::cout << std::left << std::setw(4) << iter->cID << std::left << std::setw(25) << iter->brand << std::left << std::setw(8) << iter->year ;
                std::cout << std::left << std::setw(30)<< iter->type << std::left << std::setw(8)<< iter->built << std::endl;
            }
        }

        else
        {
            std::cout << std::left << std::setw(4) << "ID: "  << std::left << std::setw(25) << "Brand:" << std::left << std::setw(6) <<"Year:";
            std::cout << std::left << std::setw(8) <<"Built?" << std::left << std::setw(20) << "Name:" << std::endl << std::endl;

            for(std::list<Computer>::iterator iter = co.begin(); iter != co.end(); iter ++)
            {
                std::cout << std::left << std::setw(4) << iter->cID << std::left << std::setw(25) << iter->brand << std::left << std::setw(6) << iter->year;
                std::cout << std::left << std::setw(8)<< iter->built << std::left << std::setw(20) << iter->name << std::endl;
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

    while((filterCol != "brand" && filterCol != "year" && filterCol != "type") || (filterCol != "built" && filterMod != "desc" && filterMod != "asc" )){


         std::cout << std::endl<< "ERROR! Please enter 'brand', 'year', 'type' or 'built' for column, and 'asc' or 'desc' for modifier: ";
         std::cin >> filterCol >> filterMod;

         toLower(filterCol);
         toLower(filterMod);


    }



    clear();

    std::list<Computer> l = scienceService.getComputersOrderedBy(filterCol,filterMod);
    std::cout << std::left << std::setw(30)<< "Brand:" << std::left << std::setw(8) << "Year:";
    std::cout << std::left << std::setw(30) << "Type:" << std::left << std::setw(8) << "Built?" << std::endl << std::endl;

    for(std::list<Computer>::iterator iter = l.begin(); iter != l.end(); iter ++) {

        std::cout << std::left << std::setw(30)<< iter->brand << std::left << std::setw(8) << iter->year << std::left << std::setw(30) << iter->type ;
        std::cout << std::left << std::setw(8) << iter->built << std::endl;
    }

    waitForPrompt();
    clear();
}

bool ConsoleUI::EXISTENCE_COMPUTER(std::string cID){

    QSqlQuery query;

    query.prepare("SELECT :id in (SELECT ID FROM Computer) AS RES");
    query.bindValue(":id", QString::fromStdString(cID));
    query.exec();
    query.next();

    std::string res = query.value("RES").toString().toStdString();
    int value = atoi(res.c_str());

    return value;

}


void ConsoleUI::CONNECT(){

    std::cout << "Do you want to search first for a scientist or a computer (y/n): ";
    std::string option;
    std::cin >> option;
    toLower(option);

    while(option != "y" && option != "n"){

        error2(option, "'y' or 'n'");
    }

    if(option == "y"){

        clear();

        std::cout << "Do you want to search for a scientist or a computer (scientist/computer): " << std::endl;
        std::string option2;
        std::cin >> option2;
        toLower(option2);

        while(option2 != "scientist" && option2 != "computer"){

            error2(option2, "'scientist' or 'computer'");
          }
        if(option2 == "scientist"){

            std::cout << "Please enter a serch therm for a scientist: ";
            SearchWithID_SCIENTIST();

            std::cout << "Do you also want to search for a computer? (y/n): ";
            std::string yesOrNo;
            std::cin >> yesOrNo;
            toLower(yesOrNo);

            if(yesOrNo!="y" && yesOrNo!="n"){

               error2(yesOrNo, "'y' or 'n'");
            }
            if(yesOrNo=="y"){

                SearchWithID_COMPUTER();
            }
        }
        else if(option2 == "computer"){

            std::cout << "Please enter a serch therm for a computer: ";
            SearchWithID_COMPUTER();

            std::cout << "Do you also want to search for a scientist? (y/n): ";
            std::string yesOrNo2;
            std::cin >> yesOrNo2;
            toLower(yesOrNo2);

            if(yesOrNo2!="y" && yesOrNo2!="n"){

               error2(yesOrNo2, "'y' or 'n'");
            }
            if(yesOrNo2=="y"){

               SearchWithID_SCIENTIST();

            }
        }
    }

    std::cout << "Enter the ID of Scientist: " << std::endl;
    std::string sconnect;
    std::cin >> sconnect;

    while(!EXISTENCE_SCIENTIST(sconnect)){
        std::cout << "This scientist does not exist!" << std::endl;
        std::cout << "Enter the ID of Scientist: " << std::endl;
        std::cin >> sconnect;
    }

    std::cout << "Enter the ID of Computer: " << std::endl;
    std::string cconnect;
    std::cin >> cconnect;

    while(!EXISTENCE_COMPUTER(cconnect)){

        std::cout << "This computer does not exist!"<< std::endl;
        std::cout << "Enter the ID of Computer: " << std::endl;
        std::cin >> cconnect;
    }

    scienceService.connect(sconnect, cconnect);
    std::cout <<"You have connected scientist with ID no. " << sconnect << " to computer with ID no. " << cconnect << std::endl;

    waitForPrompt();
    clear();
}

