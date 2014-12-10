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
    std::list<Scientist> searchScientist(std::string searchTerm, std::string ShowComp);
    // Returns all scientists that match the searchTerm
    std::list<Computer>  searchComputer(std::string searchTerm, std::string ShowComp);
    // Returns all scientists that match the searchTerm
    std::list<Scientist> getAllScientists();
    // Returns a list of all the scientists
    std::list<Computer>  getAllComputers();
    // Returns a list of all the computers
    std::list<Scientist> getScientistsOrderedBy(std::string col,std::string mod);
    // Orders the list
    std::list<Computer> getComputersOrderedBy(std::string col , std::string mod);
    // Orders the list
    void connect(std::string sID, std::string cID);
    // Connentes a computer and a scientist
    void open();
    // Opens database
private:
    SqlScientist sqlscientist;
    SqlComputer sqlcomputer;
};
#endif // SCIENCESERVICE_H
