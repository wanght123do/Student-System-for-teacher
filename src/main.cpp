#include <iostream>
#include <vector>
#include <windows.h>

// 包含所有必要的头文件
#include "../include/entities/Student.h"
#include "../include/entities/Teacher.h"
#include "../include/services/StudentService.h"
#include "../include/services/GradeService.h"
#include "../include/auth/AuthService.h"
#include "../include/menus/TeacherMenu.h"
#include "../include/menus/StudentMenu.h"

// 全局数据
std::vector<Student> students;
std::vector<Teacher> teachers;

void showMainMenu() {
    std::cout << "=========== Student Management System ===========" << std::endl;
    std::cout << "1. Login" << std::endl;
    std::cout << "2. Sign Up" << std::endl;
    std::cout << "0. Exit" << std::endl;
    std::cout << "Please enter your choice: ";
}

void handleLogin(AuthService& authService, StudentService& studentService, GradeService& gradeService) {
    std::string id, password;
    std::cout << "Enter your ID: ";
    std::cin >> id;
    std::cout << "Enter your password: ";
    std::cin >> password;
    
    if (authService.login(id, password)) {
        // 登录成功后的菜单导航在AuthService中处理
    }
}

void handleSignUp(AuthService& authService) {
    authService.registerStudent(); // 或者 registerTeacher()
}

int main() {
    // 初始化服务
    StudentService studentService(students);
    GradeService gradeService(students);
    AuthService authService(students, teachers);
    
    std::string choice;
    
    while (true) {
        showMainMenu();
        std::cin >> choice;
        
        if (choice == "1") {
            handleLogin(authService, studentService, gradeService);
        } else if (choice == "2") {
            
            handleSignUp(authService);
        } else if (choice == "0") {
            std::cout << "Goodbye!" << std::endl;
            break;
        } else {
            std::cout << "Invalid choice. Please try again." << std::endl;
        }
    }
    
    return 0;
}