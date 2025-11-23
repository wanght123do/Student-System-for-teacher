#include "entities/Grade.h"
#include "services/GradeService.h"
#include "menus/teacherMenu.h"
#include "entities/Teacher.h"
#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
#include "entities/Student.h"

void showTeacherInforation(std::string teacherId){
    for(int i=0;i<teachers.size();i++){
        if(teachers[i].id==teacherId){
            std::cout<<"Name: "<<teachers[i].name<<std::endl;
            std::cout<<"Password: "<<teachers[i].password<<std::endl;
            std::cout<<"ID: "<<teachers[i].id<<std::endl;
            std::cout<<"Subject: "<<teachers[i].subject<<std::endl;
            break;
        }
    }
    std::cout<<"Enter any key to return to the previous menu...";
    std::string c;
    std::cin>>c;
}

void writeStudentGrade(std::string teacherId){
    for(int i=0;i<students.size();i++){
        std::cout<<"Student Name: "<<students[i].name<<", ID: "<<students[i].id<<std::endl;
    }
    std::string examYrearForwrite;
    int chineseforwrite,mathforwrite,englishforwrite,biologyforwrite,historyforwrite,geographyforwrite,politicsforwrite,physicsforwrite;
    std::cout<<"Please enter the exam year: ";
    std::cin>>examYrearForwrite;
    std::cout<<"Please enter the Chinese grade: ";
    std::cin>>chineseforwrite;
    std::cout<<"Please enter the Math grade: ";
    std::cin>>mathforwrite;
    std::cout<<"Please enter the English grade: ";
    std::cin>>englishforwrite;
    std::cout<<"Please enter the Biology grade: ";
    std::cin>>biologyforwrite;
    std::cout<<"Please enter the History grade: ";
    std::cin>>historyforwrite;
    std::cout<<"Please enter the Geography grade: ";
    std::cin>>geographyforwrite;
    std::cout<<"Please enter the Politics grade: ";
    std::cin>>politicsforwrite;
    std::cout<<"Please enter the Physics grade: ";
    std::cin>>physicsforwrite;
    
    for(int i=0;i<students.size();i++){
        Grade newGrade;
        newGrade.examYear=examYrearForwrite;
        newGrade.chinese=chineseforwrite;
        newGrade.math=mathforwrite;
        newGrade.english=englishforwrite;
        newGrade.biology=biologyforwrite;
        newGrade.history=historyforwrite;
        newGrade.geography=geographyforwrite;
        newGrade.politics=politicsforwrite;
        newGrade.physics=physicsforwrite;
        newGrade.total=chineseforwrite+mathforwrite+englishforwrite+biologyforwrite+historyforwrite+geographyforwrite+politicsforwrite+physicsforwrite;
        students[i].grades.push_back(newGrade);
    }
    
    system("cls");
    std::cout<<"All student grades have been entered. Press any key to return to the previous menu...";
    std::string c;
    std::cin>>c;
}

void showStudentGrade(std::string teacherId){
    std::string studentId;
    std::cout<<"Please enter the student ID: ";
    std::cin>>studentId;
    for(int i=0;i<students.size();i++){
        if(students[i].id==studentId){
            std::cout<<"Student Name: "<<students[i].name<<", ID: "<<students[i].id<<std::endl;
            std::cout<<"------- Grades -------"<<std::endl;
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
                std::cout<<"-----------------------------------"<<std::endl;
            }
            break;
        }
    }
    std::cout<<"Enter any key to return to the previous menu...";
    std::string c;
    std::cin>>c;
}

void addStudent(std::string teacherId){
    std::string studentId,studentName,studentGender,studentBirthday,studentPassword,studentGroupinformation;
    bool studentIfAHeadGroup;
    std::cout<<"Please enter the student ID: ";
    std::cin>>studentId;
    std::cout<<"Please enter the student Name: ";
    std::cin>>studentName;
    std::cout<<"Please enter the student Gender: ";
    std::cin>>studentGender;
    std::cout<<"Please enter the student Birthday: ";
    std::cin>>studentBirthday;
    std::cout<<"Please enter the student Password: ";
    std::cin>>studentPassword;
    std::cout<<"Is the student a head of group? (1 for yes, 0 for no): ";
    std::cin>>studentIfAHeadGroup;
    std::cout<<"Please enter the student Group information: ";
    std::cin>>studentGroupinformation;
    Student newStudent;
    newStudent.id=studentId;
    newStudent.name=studentName;
    newStudent.gender=studentGender;
    newStudent.birthday=studentBirthday;
    newStudent.password=studentPassword;
    newStudent.ifAHeadGroup=studentIfAHeadGroup;
    newStudent.Groupinformation=studentGroupinformation;
    students.push_back(newStudent);
    std::cout<<"Student added successfully. Press any key to return to the previous menu...";
    std::string c;
    std::cin>>c;
}

void removeStudent(std::string teacherId){
    std::string studentId;
    std::cout<<"Please enter the student ID to remove: ";
    std::cin>>studentId;
    for(int i=0;i<students.size();i++){
        if(students[i].id==studentId){
            students.erase(students.begin()+i);
            std::cout<<"Student removed successfully. Press any key to return to the previous menu...";
            std::string c;
            std::cin>>c;
            return;
        }
    }
    std::cout<<"Student ID not found. Press any key to return to the previous menu...";
    std::string c;
    std::cin>>c;
}

void exchangeStudentPassword(std::string teacherId){
    std::string studentId,newPassword;
    std::cout<<"Please enter the student ID to change password: ";
    std::cin>>studentId;
    std::cout<<"Please enter the new password: ";
    std::cin>>newPassword;
    for(int i=0;i<students.size();i++){
        if(students[i].id==studentId){
            students[i].password=newPassword;
            std::cout<<"Student password changed successfully. Press any key to return to the previous menu...";
            std::string c;
            std::cin>>c;
            return;
        }
    }
    std::cout<<"Student ID not found. Press any key to return to the previous menu...";
    std::string c;
    std::cin>>c;
}
void showAllUsers(std::string teacherId){
    std::cout<<"--------All Users--------"<<std::endl;
    std::cout<<"---Teachers---"<<std::endl;
    for(int i=0;i<teachers.size();i++){
        std::cout<<"Name: "<<teachers[i].name<<", ID: "<<teachers[i].id<<", Subject: "<<teachers[i].subject<<std::endl;
    }
    std::cout<<"---Students---"<<std::endl;
    for(int i=0;i<students.size();i++){
        std::cout<<"Name: "<<students[i].name<<", ID: "<<students[i].id<<", Group: "<<students[i].Groupinformation<<std::endl;
    }
    std::cout<<"Enter any key to return to the previous menu...";
    std::string c;
    std::cin>>c;
}
void showTeacherMenu(std::string teacherId){
    std::string choice;
    
    while(true){
        system("cls");
        std::cout<<"================= Teacher Menu ================="<<std::endl;
        std::cout<<"1. Show Teacher Information"<<std::endl;
        std::cout<<"2. Write Student Grade"<<std::endl;
        std::cout<<"3. Show Student Grade"<<std::endl;
        std::cout<<"4. Add New Student"<<std::endl;
        std::cout<<"5. Remove Student"<<std::endl;
        std::cout<<"6. Change Student Password"<<std::endl;
        std::cout<<"7. Show All Users"<<std::endl;
        std::cout<<"0. Exit"<<std::endl;
        std::cout<<"Please enter your choice: ";
        std::cin>>choice;

        if(choice=="1"){
            system("cls");
            showTeacherInforation(teacherId);
        }
        else if(choice=="2"){
            system("cls");
            writeStudentGrade(teacherId);
        }
        else if(choice=="3"){
            system("cls");
            showStudentGrade(teacherId);
        }
        else if(choice=="4"){
            system("cls");
            addStudent(teacherId);
        }
        else if(choice=="5"){
            system("cls");
            removeStudent(teacherId);
        }
        else if(choice=="6"){
            system("cls");
            exchangeStudentPassword(teacherId);
        }
        else if (choice=="7")
        {
            system("cls");
            showAllUsers(teacherId);
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