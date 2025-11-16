#ifndef STUDENT_SERVICE_H
#define STUDENT_SERVICE_H

#include <vector>
#include "../entities/Student.h"

class StudentService {
private:
    std::vector<Student>& students;

public:
    StudentService(std::vector<Student>& studentList);
    
    // 学生管理方法
    void addStudent(const Student& newStudent);
    bool removeStudent(const std::string& id);
    Student* findStudentById(const std::string& id);
    void listAllStudents() const;
    void changeStudentPassword(const std::string& id, const std::string& newPassword);
};

#endif