#ifndef GRADE_SERVICE_H
#define GRADE_SERVICE_H

#include <vector>
#include "../entities/Student.h"

class GradeService {
private:
    std::vector<Student>& students;

public:
    GradeService(std::vector<Student>& studentList);
    
    // 成绩管理方法
    void inputGradesForAll(const std::string& examYear);
    void analyzeGrades() const;
    void showStudentGrades(const std::string& studentId) const;
};

#endif