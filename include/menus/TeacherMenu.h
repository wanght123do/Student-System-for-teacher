#ifndef TEACHER_MENU_H
#define TEACHER_MENU_H

#include <string>

void showTeacherMenu(std::string teacherId);
void showTeacherInforation(std::string teacherId);
void writeStudentGrade(std::string teacherId);
void showStudentGrade(std::string teacherId);
void addStudent(std::string teacherId);
void removeStudent(std::string teacherId);
void exchangeStudentPassword(std::string teacherId);
void showAllUsers(std::string teacherId);
#endif