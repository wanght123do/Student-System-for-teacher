#include "../../include/auth/AuthService.h"
#include <iostream>
#include <windows.h>

AuthService::AuthService(std::vector<Student>& studentList, std::vector<Teacher>& teacherList)
    : students(studentList), teachers(teacherList) {}

bool AuthService::login(const std::string& id, const std::string& password) {
    // 检查学生
    for (size_t i = 0; i < students.size(); i++) {
        if (students[i].id == id && students[i].password == password) {
            std::cout << "Student login successful: " << students[i].name << std::endl;
            Sleep(2000);
            system("cls");
            // 这里需要返回学生信息或调用学生菜单
            return true;
        }
    }
    
    // 检查教师
    for (size_t i = 0; i < teachers.size(); i++) {
        if (teachers[i].id == id && teachers[i].password == password) {
            std::cout << "Teacher login successful: " << teachers[i].name << std::endl;
            Sleep(2000);
            system("cls");
            // 这里需要调用教师菜单
            return true;
        }
    }
    
    std::cout << "Login failed: Invalid ID or password.\n";
    Sleep(2000);
    system("cls");
    return false;
}

bool AuthService::confirmPassword(const std::string& password) {
    std::string passwordConfirm;
    std::cout << "Confirm your password: ";
    std::cin >> passwordConfirm;
    return password == passwordConfirm;
}

void AuthService::registerStudent() {
    Student newStudent;
    std::cout << "Your name: ";
    std::cin >> newStudent.name;
    std::cout << "Your id: ";
    std::cin >> newStudent.id;
    std::cout << "Are you a boy or a girl? ";
    std::cin >> newStudent.gender;
    std::cout << "Your birthday: ";
    std::cin >> newStudent.birthday;
    
    std::cout << "Your password: ";
    std::cin >> newStudent.password;
    
    while (!confirmPassword(newStudent.password)) {
        std::cout << "Passwords do not match. Please try again.\n";
    }
    
    std::cout << "Are you a head group?(y/n) ";
    char headGroupChoice;
    std::cin >> headGroupChoice;
    newStudent.ifAHeadGroup = (headGroupChoice == 'Y' || headGroupChoice == 'y');
    
    std::cout << "Enter your group information:(G1/G2/G3/G4/G5/G6) ";
    std::cin >> newStudent.Groupinformation;
    
    students.push_back(newStudent);
    std::cout << "Student registration successful!\n";
    Sleep(2000);
    system("cls");
}

void AuthService::registerTeacher() {
    Teacher newTeacher;
    std::cout << "Your name: ";
    std::cin >> newTeacher.name;
    std::cout << "Your id: ";
    std::cin >> newTeacher.id;
    
    std::cout << "Your password: ";
    std::cin >> newTeacher.password;
    
    while (!confirmPassword(newTeacher.password)) {
        std::cout << "Passwords do not match. Please try again.\n";
    }
    
    teachers.push_back(newTeacher);
    std::cout << "Teacher registration successful!\n";
    Sleep(2000);
    system("cls");
}