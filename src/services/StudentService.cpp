#include "../../include/services/StudentService.h"
#include <iostream>

StudentService::StudentService(std::vector<Student>& studentList) 
    : students(studentList) {}

void StudentService::addStudent(const Student& newStudent) {
    students.push_back(newStudent);
    std::cout << "New student added successfully!" << std::endl;
}

bool StudentService::removeStudent(const std::string& id) {
    for (size_t i = 0; i < students.size(); i++) {
        if (students[i].id == id) {
            students.erase(students.begin() + i);
            std::cout << "Student removed successfully!" << std::endl;
            return true;
        }
    }
    std::cout << "Student with the given id not found!" << std::endl;
    return false;
}

Student* StudentService::findStudentById(const std::string& id) {
    for (size_t i = 0; i < students.size(); i++) {
        if (students[i].id == id) {
            return &students[i];
        }
    }
    return nullptr;
}

void StudentService::listAllStudents() const {
    system("cls");
    std::cout << "======= All Students =======" << std::endl;
    for (size_t i = 0; i < students.size(); i++) {
        std::cout << "Name: " << students[i].name 
                  << ", ID: " << students[i].id 
                  << ", Password: " << students[i].password << std::endl;
    }
}

void StudentService::changeStudentPassword(const std::string& id, const std::string& newPassword) {
    Student* student = findStudentById(id);
    if (student) {
        student->password = newPassword;
        std::cout << "Password changed successfully!" << std::endl;
    } else {
        std::cout << "Student with the given id not found!" << std::endl;
    }
}