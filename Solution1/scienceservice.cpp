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

Scientist* ScienceService::search(std::string searchTerm) {
    return sqlscientist.search(searchTerm);
}

void ScienceService::addComputer(Computer computer) {
    sqlcomputer.addComputer(computer);
}
