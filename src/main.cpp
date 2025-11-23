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





void showMainMenu() {
    std::cout << "=========== Student Management System ===========" << std::endl;
    std::cout << "1. Sign In" << std::endl;
    std::cout << "2. Sign Up" << std::endl;
    std::cout << "0. Exit" << std::endl;
    std::cout << "Please enter your choice: ";
    std::string choice;
    std::cin>>choice;
    if(choice=="2"){
        system("cls");
        std::cout<<"Do you want to be a teacher or student?"<<std::endl;
        std::string s;
        std::cin>>s;
        if(s=="teacher"||s=="Teacher"){
            void teacherSignUp();
        }
        if(s=="student"||s=="Student"){
            void studentSignUp();
        }
        else{
            std::cout<<"Please enter right choice"<<std::endl;
        }
    }
    else if(choice=="1"){
        system("cls");
        std::cout<<"Are you a teacher or student?"<<std::endl;
        std::string s;
        std::cin>>s;
        std::string id,password;
        std::cout<<"Your ID:";
        std::cin>>id;
        std::cout<<"Your Password:";
        std::cin>>password;
        if(s=="teacher"||s=="Teacher"){
            teacherSignIn(id,password);
        }
        if(s=="student"||s=="Student"){
            studentSignIn(id,password);
        }
    }
    else if(choice=="0"){
        std::cout<<"Thank you for using!Goodbye!"<<std::endl;
        return ;
    }
    else{
        std::cout<<"Error!"<<std::endl;
    }
}

int main(){
    system("cls");
    std::cout<<"Welcome to this system!"<<std::endl;
    Sleep(2000);
    showMainMenu();
    return 0;
}