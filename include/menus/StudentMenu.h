#ifndef STUDENT_MENU_H
#define STUDENT_MENU_H

#include "../entities/Student.h"
#include "../services/StudentService.h"
#include "../services/GradeService.h"

class StudentMenu {
private:
    StudentService& studentService;
    GradeService& gradeService;
    std::string currentStudentId;

public:
    StudentMenu(StudentService& ss, GradeService& gs, const std::string& studentId);
    void showMenu();
    
private:
    void handleShowInfo();
    void handleShowGrades();
};

#endif