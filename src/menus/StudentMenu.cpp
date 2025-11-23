#include "entities/Grade.h"
#include "services/GradeService.h"
#include "menus/TeacherMenu.h"
#include "entities/Teacher.h"
#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
#include "entities/Student.h"

void viewGrades(std::string studentId){
    for(int i=0;i<students.size();i++){
        if(students[i].id==studentId){
            std::cout<<"Grades for Student: "<<students[i].name<<", ID: "<<students[i].id<<std::endl;
            for(int j=0;j<students[i].grades.size();j++){
                std::cout<<"Exam Year: "<<students[i].grades[j].examYear<<std::endl;
                std::cout<<"Chinese: "<<students[i].grades[j].chinese<<std::endl;
                std::cout<<"Math: "<<students[i].grades[j].math<<std::endl;
                std::cout<<"English: "<<students[i].grades[j].english<<std::endl;
                std::cout<<"Biology: "<<students[i].grades[j].biology<<std::endl;
                std::cout<<"History: "<<students[i].grades[j].history<<std::endl;
                std::cout<<"Geography: "<<students[i].grades[j].geography<<std::endl;
                std::cout<<"Politics: "<<students[i].grades[j].politics<<std::endl;
                std::cout<<"Physics: "<<students[i].grades[j].physics<<std::endl;
                std::cout<<"Total: "<<students[i].grades[j].total<<std::endl;
                std::cout<<"-----------------------------"<<std::endl;
            }
            break;
        }
    }
    std::cout<<"Press any key to return to the previous menu...";
    std::string c;
    std::cin>>c;
}

void showStudentInfo(std::string studentId){
    for(int i=0;i<students.size();i++){
        if(students[i].id==studentId){
            std::cout<<"Name: "<<students[i].name<<std::endl;
            std::cout<<"ID: "<<students[i].id<<std::endl;
            std::cout<<"Gender: "<<students[i].gender<<std::endl;
            std::cout<<"Birthday: "<<students[i].birthday<<std::endl;
            std::cout<<"If A Head Group: "<<(students[i].ifAHeadGroup ? "Yes" : "No")<<std::endl;
            std::cout<<"Group Information: "<<students[i].Groupinformation<<std::endl;
            break;
        }
    }
    std::cout<<"Press any key to return to the previous menu...";
    std::string c;
    std::cin>>c;
}

void changeStudentPassword(std::string studentId){
    std::string newPassword;
    std::cout<<"Please enter your new password: ";
    std::cin>>newPassword;
    for(int i=0;i<students.size();i++){
        if(students[i].id==studentId){
            students[i].password=newPassword;
            std::cout<<"Password changed successfully.";
            break;
        }
    }
    std::cout<<" Press any key to return to the previous menu...";
    std::string c;
    std::cin>>c;
}

void showStudentMenu(std::string studentId){
    std::string choice;
    
    while(true){
        system("cls");
        std::cout<<"============== Student Menu =============="<<std::endl;
        std::cout<<"1. View Grade"<<std::endl;
        std::cout<<"2. Show Your Information"<<std::endl;
        std::cout<<"3. Change Your Password"<<std::endl;
        std::cout<<"0. Exit"<<std::endl;
        std::cout<<"Please choose: ";
        std::cin>>choice;

        if(choice=="1"){
            system("cls");
            viewGrades(studentId);
        }
        else if(choice=="2"){
            system("cls");
            showStudentInfo(studentId);
        }
        else if(choice=="3"){
            system("cls");
            changeStudentPassword(studentId);
        }
        else if(choice=="0"){
            std::cout<<"Returning to main menu..."<<std::endl;
            Sleep(1000);
            break;
        }
        else{
            std::cout<<"Invalid choice. Press any key to try again."<<std::endl;
            std::string c;
            std::cin>>c;
        }
    }
}