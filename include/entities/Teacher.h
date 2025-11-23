#ifndef TEACHER_H
#define TEACHER_H

#include <string>

struct Teacher {
    std::string name;
    std::string id;
    std::string password;
    std::string subject;
};
std::vector<Teacher> teachers;
#endif