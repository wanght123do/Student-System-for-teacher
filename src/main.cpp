#include <iostream>
#include <vector>
#include <windows.h>
#include <fstream>
#include <string>
#include <filesystem>  // 添加这个头文件

#include "entities/Student.h"
#include "entities/Teacher.h"
#include "entities/Exam.h"
#include "services/StudentService.h"
#include "services/GradeService.h"
#include "auth/AuthService.h"
#include "menus/TeacherMenu.h"
#include "menus/StudentMenu.h"
#include "services/InformationService.h"
#include "services/ExamService.h"
#include "data/DataManager.h"

// 声明全局变量（这些应该在GlobalData.cpp中定义）
extern std::vector<Student> students;
extern std::vector<Teacher> teachers;
extern std::vector<Exam> exams;

// 声明函数
void showMainMenu();
void ensureDataDirectories();
void showDataStatus();

// 将窄字符串转换为宽字符串
std::wstring stringToWString(const std::string& str) {
    int size_needed = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0);
    std::wstring wstrTo(size_needed, 0);
    MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &wstrTo[0], size_needed);
    return wstrTo;
}

// 确保数据目录存在
void ensureDataDirectories() {
    // 检查并创建必要的目录
    std::vector<std::string> dirs = {"data", "backups", "build", "build/release"};
    
    for (const auto& dir : dirs) {
        if (!std::filesystem::exists(dir)) {
            std::filesystem::create_directories(dir);
            std::cout << "Created directory: " << dir << std::endl;
        }
    }
}

// 显示数据状态
void showDataStatus() {
    std::cout << "\n[System Information]" << std::endl;
    std::cout << "====================" << std::endl;
    std::cout << "Students: " << students.size() << std::endl;
    std::cout << "Teachers: " << teachers.size() << std::endl;
    std::cout << "Exams: " << exams.size() << std::endl;
    
    // 计算总成绩记录数
    int totalGrades = 0;
    for (const auto& student : students) {
        totalGrades += student.grades.size();
    }
    std::cout << "Grade records: " << totalGrades << std::endl;
    std::cout << "====================" << std::endl;
}

// 确保文本文件存在（兼容性）
void ensureTextFiles() {
    // 检查学生文件
    std::ofstream studentTest("build/students.txt", std::ios::app);
    if (studentTest.is_open()) {
        studentTest.close();
    } else {
        std::cout << "Warning: Cannot ensure students.txt file" << std::endl;
    }
    
    // 检查教师文件
    std::ofstream teacherTest("build/teachers.txt", std::ios::app);
    if (teacherTest.is_open()) {
        teacherTest.close();
    } else {
        std::cout << "Warning: Cannot ensure teachers.txt file" << std::endl;
    }
}

int main() {
    system("cls");
    system("title Student Management System with JSON Support");
    
    std::cout << "=================================================" << std::endl;
    std::cout << "     Student Management System (JSON Edition)    " << std::endl;
    std::cout << "=================================================" << std::endl;
    
    // 1. 确保目录存在
    ensureDataDirectories();
    
    // 2. 初始化DataManager
    DataManager::initialize();
    
    // 3. 加载数据（优先从JSON加载）
    std::cout << "\n[Loading Data]" << std::endl;
    std::cout << "==============" << std::endl;
    
    if (!DataManager::loadAllData()) {
        std::cout << "\n⚠ Warning: Failed to load data from JSON!" << std::endl;
        std::cout << "  Falling back to text files..." << std::endl;
        
        // 确保文本文件存在
        ensureTextFiles();
        
        // 从文本文件加载（兼容模式）
        readStudentsInformation();
        readTeachersInformation();
        
        // 保存为JSON格式
        DataManager::saveAllData();
        std::cout << "✓ Data migrated to JSON format" << std::endl;
    } else {
        std::cout << "✓ Data loaded from JSON successfully" << std::endl;
    }
    
    // 显示数据状态
    showDataStatus();
    
    std::cout << "\nPress any key to continue..." << std::endl;
    std::cin.ignore();
    std::cin.get();
    
    // 显示欢迎信息
    system("cls");
    std::cout << "=================================================" << std::endl;
    std::cout << "     Welcome to Student Management System!       " << std::endl;
    std::cout << "=================================================" << std::endl;
    std::cout << "Version: JSON Edition 1.0" << std::endl;
    std::cout << "Data Storage: JSON with automatic backups" << std::endl;
    std::cout << "=================================================" << std::endl;
    Sleep(2000);
    
    // 进入主菜单
    showMainMenu();
    
    // 程序退出前自动保存
    std::cout << "\n[Saving Data Before Exit]" << std::endl;
    std::cout << "=========================" << std::endl;
    if (DataManager::hasUnsavedChanges()) {
        DataManager::saveAllData();
        std::cout << "✓ All changes saved" << std::endl;
    } else {
        std::cout << "○ No changes to save" << std::endl;
    }
    
    std::cout << "\nThank you for using! Goodbye!" << std::endl;
    Sleep(2000);
    
    return 0;
}

void showMainMenu() {
    std::string choice;
    
    while(true) {
        system("cls");
        std::cout << "=================================================" << std::endl;
        std::cout << "            Student Management System            " << std::endl;
        std::cout << "=================================================" << std::endl;
        std::cout << "1. Sign In" << std::endl;
        std::cout << "2. Sign Up" << std::endl;
        std::cout << "3. Data Status" << std::endl;
        std::cout << "4. Save Data Now" << std::endl;
        std::cout << "0. Exit" << std::endl;
        std::cout << "=================================================" << std::endl;
        std::cout << "Please enter your choice: ";
        std::cin >> choice;

        if (choice == "1") {
            system("cls");
            std::cout << "Are you a teacher or student?" << std::endl;
            std::string role;
            std::cin >> role;
            
            std::string id, password;
            std::cout << "Your ID: ";
            std::cin >> id;
            std::cout << "Your Password: ";
            std::cin >> password;
            
            if (role == "teacher" || role == "Teacher") {
                if (teacherSignIn(id, password)) {
                    DataManager::markDataChanged();
                    showTeacherMenu(id);
                }
            } else if (role == "student" || role == "Student") {
                if (studentSignIn(id, password)) {
                    DataManager::markDataChanged();
                    showStudentMenu(id);
                }
            } else {
                std::cout << "Invalid role! Press any key to continue..." << std::endl;
                std::cin.ignore();
                std::cin.get();
            }
        } else if (choice == "2") {
            system("cls");
            std::cout << "Do you want to be a teacher or student?" << std::endl;
            std::string role;
            std::cin >> role;
            
            if (role == "teacher" || role == "Teacher") {
                teacherSignUp();
                DataManager::markDataChanged();
            } else if (role == "student" || role == "Student") {
                studentSignUp();
                DataManager::markDataChanged();
            } else {
                std::cout << "Please enter right choice" << std::endl;
                std::cout << "Press any key to continue..." << std::endl;
                std::cin.ignore();
                std::cin.get();
            }
        } else if (choice == "3") {
            system("cls");
            std::cout << DataManager::getStatus() << std::endl;
            showDataStatus();
            std::cout << "\nPress any key to return to main menu..." << std::endl;
            std::cin.ignore();
            std::cin.get();
        } else if (choice == "4") {
            system("cls");
            std::cout << "[Manual Save]" << std::endl;
            std::cout << "=============" << std::endl;
            if (DataManager::manualSave()) {
                std::cout << "✓ Data saved successfully!" << std::endl;
            } else {
                std::cout << "✗ Failed to save data!" << std::endl;
            }
            std::cout << "\nPress any key to return to main menu..." << std::endl;
            std::cin.ignore();
            std::cin.get();
        } else if (choice == "0") {
            break;
        } else {
            std::cout << "Invalid choice! Press any key to continue..." << std::endl;
            std::cin.ignore();
            std::cin.get();
        }
        
        // 每循环一次自动保存检查
        DataManager::autoSave();
    }
}