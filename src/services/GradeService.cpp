#include "../../include/services/GradeService.h"
#include <iostream>
#include <windows.h>

GradeService::GradeService(std::vector<Student>& studentList) 
    : students(studentList) {}

void GradeService::inputGradesForAll(const std::string& examYear) {
    system("cls");
    int chinese, math, english, history, geography, biology, physics, politics;
    
    for (size_t i = 0; i < students.size(); i++) {
        std::cout << "Please enter the grades for student " << students[i].name 
                  << " (ID: " << students[i].id << "):" << std::endl;
        
        std::cout << "Chinese: "; std::cin >> chinese;
        std::cout << "Math: "; std::cin >> math;
        std::cout << "English: "; std::cin >> english;
        std::cout << "History: "; std::cin >> history;
        std::cout << "Geography: "; std::cin >> geography;
        std::cout << "Biology: "; std::cin >> biology;
        std::cout << "Physics: "; std::cin >> physics;
        std::cout << "Politics: "; std::cin >> politics;
        
        Grade newGrade;
        newGrade.examYear = examYear;
        newGrade.chinese = chinese;
        newGrade.math = math;
        newGrade.english = english;
        newGrade.history = history;
        newGrade.geography = geography;
        newGrade.biology = biology;
        newGrade.physics = physics;
        newGrade.politics = politics;
        newGrade.total = chinese + math + english + history + geography + biology + physics + politics;
        
        students[i].grades.push_back(newGrade);
        system("cls");
    }
    std::cout << "Grades written successfully!" << std::endl;
}

void GradeService::showStudentGrades(const std::string& studentId) const {
    for (size_t i = 0; i < students.size(); i++) {
        if (students[i].id == studentId) {
            system("cls");
            std::cout << "====== Your Grades ======" << std::endl;
            for (size_t j = 0; j < students[i].grades.size(); j++) {
                std::cout << "--- Exam Year: " << students[i].grades[j].examYear << " ---" << std::endl;
                std::cout << "Chinese: " << students[i].grades[j].chinese << std::endl;
                std::cout << "Math: " << students[i].grades[j].math << std::endl;
                std::cout << "English: " << students[i].grades[j].english << std::endl;
                std::cout << "History: " << students[i].grades[j].history << std::endl;
                std::cout << "Geography: " << students[i].grades[j].geography << std::endl;
                std::cout << "Biology: " << students[i].grades[j].biology << std::endl;
                std::cout << "Physics: " << students[i].grades[j].physics << std::endl;
                std::cout << "Politics: " << students[i].grades[j].politics << std::endl;
                std::cout << "Total: " << students[i].grades[j].total << std::endl;
                std::cout << "\n" << std::endl;
            }
            return;
        }
    }
    std::cout << "Student with the given id not found!" << std::endl;
}

void GradeService::analyzeGrades() const {
    system("cls");
    
    if (students.empty()) {
        std::cout << "No students found for analysis!" << std::endl;
        return;
    }

    int totalStudentsWithGrades = 0;
    double sumChinese = 0, sumMath = 0, sumEnglish = 0, sumHistory = 0;
    double sumGeography = 0, sumBiology = 0, sumPhysics = 0, sumPolitics = 0;
    double sumTotal = 0;

    for (size_t i = 0; i < students.size(); i++) {
        if (!students[i].grades.empty()) {
            totalStudentsWithGrades++;
            for (size_t j = 0; j < students[i].grades.size(); j++) {
                sumChinese += students[i].grades[j].chinese;
                sumMath += students[i].grades[j].math;
                sumEnglish += students[i].grades[j].english;
                sumHistory += students[i].grades[j].history;
                sumGeography += students[i].grades[j].geography;
                sumBiology += students[i].grades[j].biology;
                sumPhysics += students[i].grades[j].physics;
                sumPolitics += students[i].grades[j].politics;
                sumTotal += students[i].grades[j].total;
            }
        }
    }

    if (totalStudentsWithGrades == 0) {
        std::cout << "No grades available for analysis!" << std::endl;
        return;
    }

    double avgChinese = sumChinese / totalStudentsWithGrades;
    double avgMath = sumMath / totalStudentsWithGrades;
    double avgEnglish = sumEnglish / totalStudentsWithGrades;
    double avgHistory = sumHistory / totalStudentsWithGrades;
    double avgGeography = sumGeography / totalStudentsWithGrades;
    double avgBiology = sumBiology / totalStudentsWithGrades;
    double avgPhysics = sumPhysics / totalStudentsWithGrades;
    double avgPolitics = sumPolitics / totalStudentsWithGrades;
    double avgTotal = sumTotal / totalStudentsWithGrades;

    std::cout << "====== All Students Average Grades ======" << std::endl;
    std::cout << "Students with grades: " << totalStudentsWithGrades << std::endl;
    std::cout << "Chinese: " << avgChinese << std::endl;
    std::cout << "Math: " << avgMath << std::endl;
    std::cout << "English: " << avgEnglish << std::endl;
    std::cout << "History: " << avgHistory << std::endl;
    std::cout << "Geography: " << avgGeography << std::endl;
    std::cout << "Biology: " << avgBiology << std::endl;
    std::cout << "Physics: " << avgPhysics << std::endl;
    std::cout << "Politics: " << avgPolitics << std::endl;
    std::cout << "Total Average: " << avgTotal << std::endl;
}