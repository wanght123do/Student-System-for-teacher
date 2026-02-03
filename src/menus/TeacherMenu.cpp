#include "entities/Grade.h"
#include "services/GradeService.h"
#include "menus/teacherMenu.h"
#include "entities/Teacher.h"
#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
#include "entities/Student.h"
#include <stdlib.h>  // 用于 rand(), srand()  
#include <time.h>    // 用于 time()
#include "../include/services/ExamService.h"

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
    std::cout<<"\n";
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
    std::cout<<"All student grades have been entered. Press any key to return to the previous menu...\n";
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
    std::cout<<"Enter any key to return to the previous menu...\n";
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
    std::cout<<"Student added successfully. Press any key to return to the previous menu...\n";
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
            std::cout<<"Student removed successfully. Press any key to return to the previous menu...\n";
            std::string c;
            std::cin>>c;
            return;
        }
    }
    std::cout<<"Student ID not found. Press any key to return to the previous menu...\n";
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
            std::cout<<"Student password changed successfully. Press any key to return to the previous menu...\n";
            std::string c;
            std::cin>>c;
            return;
        }
    }
    std::cout<<"Student ID not found. Press any key to return to the previous menu...\n";
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
    std::cout<<"Enter any key to return to the previous menu...\n";
    std::string c;
    std::cin>>c;
}
void giveAStudent(std::string teacherId){
    srand(time(0));  
    int positiveNum = 0 + (rand() % (int(1e7) - 0 + 1));  // A 到 B 
    std::cout<<"The Student is: "<<students[positiveNum % students.size()].name<<", ID: "<<students[positiveNum % students.size()].id<<std::endl;
    std::cout<<"Enter any key to return to the previous menu...\n";
    std::string c;
    std::cin>>c;
}

void checkStudentWithoutHomework(std::string teacherId){
    std::vector<std::string>CheckStudentsHomework;
    for(int i=0;i<students.size();i++){
        if(students[i].grades.empty()){
            CheckStudentsHomework.push_back(students[i].id);
        }
    }
    std::cout<<"Please enter today not arrive to class student ID(enter 000 to break):"<<std::endl;
    std::string notArriveStudentId;
    while(true){
        std::cin>>notArriveStudentId;
        for(int i=0;i<CheckStudentsHomework.size();i++){
            if(CheckStudentsHomework[i]==notArriveStudentId){
                CheckStudentsHomework.erase(CheckStudentsHomework.begin()+i);
            }
        }
        if(notArriveStudentId=="000"){
            break;
        }
    }
    std::cout<<"Please enter today give you his(her) homework student ID(enter 000 to break):"<<std::endl;
    std::string giveHomeworkStudentId;  
    while(true){
        std::cin>>giveHomeworkStudentId;
        for(int i=0;i<CheckStudentsHomework.size();i++){
            if(CheckStudentsHomework[i]==giveHomeworkStudentId){
                CheckStudentsHomework.erase(CheckStudentsHomework.begin()+i);
            }
        }
        if(giveHomeworkStudentId=="000"){
            break;
        }
    }
    if(CheckStudentsHomework.empty()){
        std::cout<<"All students have submitted their homework today!"<<std::endl;
    }
    else{
        std::cout<<"The following students have not submitted their homework today:"<<std::endl;
        for(int i=0;i<CheckStudentsHomework.size();i++){
            for(int j=0;j<students.size();j++){
                if(students[j].id==CheckStudentsHomework[i]){
                    std::cout<<"Name: "<<students[j].name<<", ID: "<<students[j].id<<std::endl;
                    break;
                }
            }
        }
    }
    std::cout<<"\n";
    std::cout<<"Enter any key to return to the previous menu...\n";
    std::string c;
    std::cin>>c;
}

void writeExamInformation(std::string teacherId) {
    std::string subject, date, name;
    
   
    for (int i = 0; i < teachers.size(); i++) {
        if (teachers[i].id == teacherId) {
            subject = teachers[i].subject;
            break;
        }
    }
    
    
    std::cout << "Please enter the exam date: ";
    std::cin >> date;
    std::cout << "Please enter the exam name: ";
    std::cin >> name;
    
   
    std::vector<char> answers;
    std::string answerLine;
    
    std::cout << "Please enter the exam answers (enter 'end' on a new line to finish): " << std::endl;
    std::cin.ignore(); 
    while (true) {
        std::getline(std::cin, answerLine);
        
       
        if (answerLine == "end" || answerLine == "END") {
            break;
        }
        
       
        for (char c : answerLine) {
            answers.push_back(c);
        }
        
       
        answers.push_back('\n');
    }
    
    
    if (!answers.empty() && answers.back() == '\n') {
        answers.pop_back();
    }
    
    
    Exam newExam;
    newExam.subject = subject;
    newExam.date = date;
    newExam.name = name;
    newExam.answers = answers;
    
    exams.push_back(newExam);
    
    std::cout << "Exam information written successfully. Press any key to return to the previous menu...\n";
    std::cin.ignore(); 
    std::cin.get();   
}

void showStudentInfoForTeacher(std::string teacherId){
    std::cout<<"Please enter the student name:";
    std::string studentNameForCheck;
    std::cin>>studentNameForCheck;
    for(int i=0;i<students.size();i++){
        if(students[i].name==studentNameForCheck){
            std::cout<<"Name:"<<students[i].name<<std::endl;
            std::cout<<"ID:"<<students[i].id<<std::endl;
            std::cout<<"Password:";
            for(int i=1;i<=students[i].password.size();i++){
                std::cout<<"*";
            }
            std::cout<<std::endl;
            std::cout<<"Birthday:"<<students[i].birthday<<std::endl;
            std::cout<<"Group:"<<students[i].Groupinformation<<std::endl;
            std::cout<<"Enter any key to return to the previous menu...\n";
            std::string c;
            std::cin>>c;
            return ;
        }
    }
    std::cout<<"Student \""<<studentNameForCheck<<"\" not found!"<<std::endl;
    std::cout<<"Enter any key to return to the previous menu...\n";
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
        std::cout<<"8. Give A Student"<<std::endl;
        std::cout<<"9. Check Students Without Homework"<<std::endl;
        std::cout<<"10. Write Exam Information"<<std::endl;
        std::cout<<"11. Show Student Information"<<std::endl;
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
        else if(choice=="8"){
            system("cls");
            giveAStudent(teacherId);
        }
        else if(choice=="9"){
            system("cls");
            checkStudentWithoutHomework(teacherId);
        }
        else if(choice=="10"){
            system("cls");
            writeExamInformation(teacherId);
        }
        else if(choice=="11"){
            system("cls");
            showStudentInfoForTeacher(teacherId);
        }
        else if(choice=="0"){
            system("cls");
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