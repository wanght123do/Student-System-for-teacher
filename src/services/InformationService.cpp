#include "services/InformationService.h"
#include <iostream>
#include <fstream>
#include "entities/Student.h"
#include "entities/Teacher.h"

void readStudentsInformation(){
    std::ifstream studentin("build/students.txt");
    if(!studentin.is_open()){
        std::cout<<"Failed to open students.txt"<<std::endl;
        return;
    }
    Student tempStudent;
    while(studentin >> tempStudent.name >> tempStudent.id >> tempStudent.gender
          >> tempStudent.birthday >> tempStudent.password >> tempStudent.ifAHeadGroup
          >> tempStudent.Groupinformation){
        students.push_back(tempStudent);
    }
    studentin.close();
}
void readTeachersInformation(){
    std::ifstream teacherin("build/teachers.txt");
    if(!teacherin.is_open()){
        std::cout<<"Failed to open teachers.txt"<<std::endl;
        return;
    }
    Teacher tempTeacher;
    while(teacherin >> tempTeacher.name >> tempTeacher.id >> tempTeacher.password
          >> tempTeacher.subject){
        teachers.push_back(tempTeacher);
    }
    teacherin.close();
}