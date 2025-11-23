#include "auth/AuthService.h"
#include <iostream>
#include <windows.h>

bool studentSignIn(const std::string& id, const std::string& password){
    for(int i=0;i<students.size();i++){
        if(students[i].id==id && students[i].password==password){
            std::cout<<"student login successful!  Name:"<<students[i].name<<std::endl;
            Sleep(1000);
            return true;
        }
    }
    std::cout<<"student login failed!"<<std::endl;
    Sleep(1000);
    return false;
}

bool teacherSignIn(const std::string& id, const std::string& password){
    for(int i=0;i<teachers.size();i++){
        if(teachers[i].id==id && teachers[i].password==password){
            std::cout<<"teacher login successful!  Name:"<<teachers[i].name<<std::endl;
            Sleep(1000);
            return true;
        }
    }
    std::cout<<"teacher login failed!"<<std::endl;
    Sleep(1000);
    return false;
}

void teacherSignUp(){
    std::string name,id,password,subject;
    std::cout<<"Enter teacher name: ";
    std::cin>>name;
    std::cout<<"Enter teacher id: ";
    std::cin>>id;
    std::cout<<"Enter teacher password: ";
    std::cin>>password;
    std::cout<<"Enter teacher subject: ";
    std::cin>>subject;
    Teacher newTeacher={name,id,password,subject};
    teachers.push_back(newTeacher);
    std::cout<<"Teacher sign up successful!"<<std::endl;
    Sleep(1000);
}

void studentSignUp(){
    std::string name,id,gender,birthday,password;
    std::cout<<"Enter student name: ";
    std::cin>>name;
    std::cout<<"Enter student id: ";
    std::cin>>id;
    std::cout<<"Enter student gender: ";
    std::cin>>gender;
    std::cout<<"Enter student birthday: ";
    std::cin>>birthday;
    std::cout<<"Enter student password: ";
    std::cin>>password;
    while(1){
        std::string passwordConfirm;
        std::cout<<"Confirm student password: ";
        std::cin>>passwordConfirm;
        if(passwordConfirm==password){
            break;
        }else{
            std::cout<<"Passwords do not match. Please try again."<<std::endl;
        }
    }
    bool ifAHeadGroup=false;
    std::cout<<"Is the student a head group member? (1 for yes, 0 for no): ";
    int headGroupInput;
    std::cin>>headGroupInput;
    if(headGroupInput==1){
        ifAHeadGroup=true;
    }
    std::string Groupinformation;
    std::cout<<"Enter student group information: ";
    std::cin>>Groupinformation;
    Student newStudent={name,id,gender,birthday,password,ifAHeadGroup,Groupinformation,{}};
    students.push_back(newStudent);
    std::cout<<"Student sign up successful!"<<std::endl;
    Sleep(1000);
}