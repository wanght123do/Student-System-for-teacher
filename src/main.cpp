#include <iostream>
#include <vector>
#include <windows.h>

#include "entities/Student.h"
#include "entities/Teacher.h"
#include "services/StudentService.h"
#include "services/GradeService.h"
#include "auth/AuthService.h"
#include "menus/TeacherMenu.h"
#include "menus/StudentMenu.h"
#include <fstream>

extern std::vector<Student> students;
extern std::vector<Teacher> teachers;

void showMainMenu();

int main(){
    system("cls");
    std::cout<<"Welcome to this system!"<<std::endl;
    Sleep(2000);
    showMainMenu();
    return 0;
}

void showMainMenu(){
    std::string choice;
    
    while(true){
        system("cls");
        std::cout<<"================================================="<<std::endl;
        std::cout<<"            Student Management System            "<<std::endl;
        std::cout<<"================================================="<<std::endl;
        std::cout<<"1. Sign In"<<std::endl;
        std::cout<<"2. Sign Up"<<std::endl;
        std::cout<<"0. Exit"<<std::endl;
        std::cout<<"Please enter your choice: ";
        std::cin>>choice;

        if(choice=="1"){
            system("cls");
            std::cout<<"Are you a teacher or student?"<<std::endl;
            std::string role;
            std::cin>>role;
            
            std::string id,password;
            std::cout<<"Your ID: ";
            std::cin>>id;
            std::cout<<"Your Password: ";
            std::cin>>password;
            
            if(role=="teacher"||role=="Teacher"){
                if(teacherSignIn(id,password)){
                    showTeacherMenu(id);
                }
            }
            else if(role=="student"||role=="Student"){
                if(studentSignIn(id,password)){
                    showStudentMenu(id);
                }
            }
            else{
                std::cout<<"Invalid role! Press any key to continue..."<<std::endl;
                std::string c;
                std::cin>>c;
            }
        }
        else if(choice=="2"){
            system("cls");
            std::cout<<"Do you want to be a teacher or student?"<<std::endl;
            std::string role;
            std::cin>>role;
            
            if(role=="teacher"||role=="Teacher"){
                teacherSignUp();
            }
            else if(role=="student"||role=="Student"){
                studentSignUp();
            }
            else{
                std::cout<<"Please enter right choice"<<std::endl;
                std::cout<<"Press any key to continue..."<<std::endl;
                std::string c;
                std::cin>>c;
            }
        }
        else if(choice=="0"){
            std::cout<<"Thank you for using! Goodbye!"<<std::endl;
            Sleep(2000);
            break;
        }
        else{
            std::cout<<"Error! Press any key to continue..."<<std::endl;
            std::string c;
            std::cin>>c;
        }
    }
}