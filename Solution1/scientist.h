#ifndef SCIENTIST_H
#define SCIENTIST_H

#include <string>

// DTO for scientists
class Scientist {
public:
    Scientist();
    // This is required for the remove functionality
    bool operator==(const Scientist &rhs);
    int sID;
    std::string name;
    std::string dateOfBirth;
    std::string dateOfDeath;
    std::string gender;
    std::string brand;
};
#endif // SCIENTIST_H
