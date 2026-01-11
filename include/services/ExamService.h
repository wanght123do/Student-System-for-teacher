#ifndef EXAM_SERVICE_H
#define EXAM_SERVICE_H

#include <vector>
#include "../entities/Student.h"

struct exam{
    std::string subject;
    std::string date;
    std::string name;
    std::vector<char> answers;
};
extern std::vector<exam> exams;

#endif