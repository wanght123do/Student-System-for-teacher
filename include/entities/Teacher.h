#ifndef TEACHER_H
#define TEACHER_H

#include <string>

struct Teacher {
    std::string name;
    std::string id;
    std::string password;
    
    void displayInfo() const;
};

#endif