#ifndef STUDENT_MENU_H
#define STUDENT_MENU_H

#include "../entities/Student.h"
#include "../services/StudentService.h"
#include "../services/GradeService.h"

void showStudentMenu(std::string studentId);
void viewGrades(std::string studentId);
void showStudentInfo(std::string studentId);
void changeStudentPassword(std::string studentId);

#endif