#ifndef MENUS_H
#define MENUS_H

// Long strings and ASCII art here below \/ \/

std::string INTRO = " Do you want to enter the computers' Database or the scientists' Database? \n\n\
        computer : Enter the computers' Database\n\
        scientist: Enter the scientists' Database\n\
        connect  : Connect scientist and computer\n\
        exit     : Exit the program.";


std::string MAIN_MENU1 = "Please use the following commands to interface with this AWESOME DATABASE\n\n\
        add     : Add a scientist to the database\n\
        order   : Order and dislay the scientists in the database\n\
        search  : Searches for a scientist\n\
        exit    : Exit the program";



std::string MAIN_MENU2 = "Please use the following commands to interface with this AWESOME DATABASE\n\n\
        add     : Add a computer to the database\n\
        order   : Order and dislay the computers in the database\n\
        search  : Searches for a Computer\n\
        exit    : Exit the program";

std::string FILTER_MENU1 = "Enter one of the following commands to order by the corresponding column\n\
along with an ascending(asc) or descending(desc) modifier\n\
        name    : Name\n\
        dob     : Date of birth\n\
        dod     : Date of death\n\
        gender  : Gender\n\n\
Example: \"name desc\"";

std::string FILTER_MENU2 = "Enter one of the following commands to order by the corresponding column\n\
along with an ascending(asc) or descending(desc) modifier\n\
        brand   : Brand\n\
        year    : Year\n\
        type    : Type\n\
        built   : Was the computer built?\n\n\
Example: \"brand desc\"";



#endif // MENUS_H
