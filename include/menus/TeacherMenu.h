#ifndef TEACHER_MENU_H
#define TEACHER_MENU_H

#include "../services/StudentService.h"
#include "../services/GradeService.h"

class TeacherMenu {
private:
    StudentService& studentService;
    GradeService& gradeService;

public:
    TeacherMenu(StudentService& ss, GradeService& gs);
    void showMenu();
    
private:
    void handleShowAllUsers();
    void handleAddStudent();
    void handleRemoveStudent();
    void handleChangePassword();
    void handleWriteGrades();
    void handleShowStudentGrades();
    void handleAnalyzeGrades();
};

#endif