#ifndef AUTH_SERVICE_H
#define AUTH_SERVICE_H

#include <string>
#include "../entities/Student.h"
#include "../entities/Teacher.h"

class AuthService {
private:
    std::vector<Student>& students;
    std::vector<Teacher>& teachers;

public:
    AuthService(std::vector<Student>& studentList, std::vector<Teacher>& teacherList);
    
    bool login(const std::string& id, const std::string& password);
    void registerStudent();
    void registerTeacher();
    
private:
    bool confirmPassword(const std::string& password);
};

#endif