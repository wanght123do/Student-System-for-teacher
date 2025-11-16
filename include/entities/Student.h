#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <vector>
#include "Grade.h"

struct Student {
    std::string name;
    std::string id;
    std::string gender;
    std::string birthday;
    std::string password;
    bool ifAHeadGroup;
    std::string Groupinformation;
    std::vector<Grade> grades;
    
    // 学生相关方法
    void displayInfo() const;
    void displayGrades() const;
};

#endif