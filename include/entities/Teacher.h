#ifndef TEACHER_H
#define TEACHER_H

#include <string>
#include <vector>

struct Teacher {
    std::string name;
    std::string id;
    std::string password;
    std::string subject;
};

extern std::vector<Teacher> teachers;

#endif