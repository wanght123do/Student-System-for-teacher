// include/entities/Exam.h
#ifndef EXAM_H
#define EXAM_H

#include <string>
#include <vector>

struct Exam {
    std::string subject;
    std::string date;
    std::string name;
    std::vector<char> answers;
};

#endif // EXAM_H