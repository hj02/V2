#include "scienceservice.h"

ScienceService::ScienceService() {
    sqlscientist = SqlScientist();
    sqlcomputer = SqlComputer();
}

ScienceService::~ScienceService() {
}

void ScienceService::addScientist(Scientist scientist) {
    sqlscientist.addScientist(scientist);
}

std::list<Scientist> ScienceService::getAllScientists() {
    return sqlscientist.list();
}

std::list<Scientist> ScienceService::getScientistsOrderedBy(std::string col, std::string mod) {
    return sqlscientist.list(col,mod);
}

std::list<Scientist> ScienceService::searchScientist(std::string searchTerm) {
    return sqlscientist.searchScientist(searchTerm);
}

void ScienceService::addComputer(Computer computer) {
    sqlcomputer.addComputer(computer);
}


std::list<Computer> ScienceService::getAllComputers(){

    return sqlcomputer.list();

}
std::list<Computer> ScienceService::getComputersOrderedBy(std::string col, std::string mod){

    return sqlcomputer.list(col, mod);

}
Computer* ScienceService::searchComputer(std::string searchTerm){

    sqlcomputer.searchComputer(searchTerm);

}

