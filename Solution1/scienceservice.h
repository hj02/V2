#ifndef SCIENCESERVICE_H
#define SCIENCESERVICE_H
#include "sqlscientist.h"
#include "sqlcomputer.h"

// Domain layer, services the presentation layer
class ScienceService {
public:
    ScienceService();
    ~ScienceService();
    void addScientist(Scientist scientist);
    void addComputer(Computer computer);
    // Returns the first scientist that matches the searchTerm
    std::list<Scientist> searchScientist(std::string searchTerm, std::string ShowComp);
    std::list<Computer>  searchComputer(std::string searchTerm, std::string ShowComp);
    std::list<Scientist> getAllScientists();
    std::list<Computer>  getAllComputers();
    std::list<Scientist> getScientistsOrderedBy(std::string col,std::string mod);
    std::list<Computer> getComputersOrderedBy(std::string col , std::string mod);
    void connect(std::string sID, std::string cID);
    void OPEN();
private:
    SqlScientist sqlscientist;
    SqlComputer sqlcomputer;
};
#endif // SCIENCESERVICE_H
