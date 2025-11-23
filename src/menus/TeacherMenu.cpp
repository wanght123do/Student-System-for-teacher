#include <../../include/entities/Grade.h>
#include <../../include/services/GradeService.h>
#include <../../include/menus/teacherMenu.h>
#include <../../include/entities/Teacher.h>
#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
#include <../../include/entities/Student.h>
void showTeacherInforation(std::string teacherId){
    for(int i=0;i<teachers.size();i++){
        if(teachers[i].id==teacherId){
            printf("Name: %s",&teachers[i].name);
            printf("Password: %s",&teachers[i].password);
            printf("ID: %s",&teachers[i].id);
            printf("Subject: %s",&teachers[i].subject);
            break;
        }
    }
    printf("Enter any key to return to the previous menu...");
    std::string c;
    scanf("%s",&c);
    return;
}

void writeStudentGrade(std::string teacherId){
    for(int i=0;i<students.size();i++){
        std::cout<<"Student Name: "<<students[i].name<<", ID: "<<students[i].id<<std::endl;
    std::string examYrearForwrite;
    int chineseforwrite,mathforwrite,englishforwrite,biologyforwrite,historyforwrite,geographyforwrite,politicsforwrite,physicsforwrite;
    printf("Please enter the exam year: ");
    scanf("%s",&examYrearForwrite);
    printf("Please enter the Chinese grade: ");
    scanf("%d",&chineseforwrite);
    printf("Please enter the Math grade: ");
    scanf("%d",&mathforwrite);
    printf("Please enter the English grade: ");
    scanf("%d",&englishforwrite);
    printf("Please enter the Biology grade: ");
    scanf("%d",&biologyforwrite);
    printf("Please enter the History grade: ");
    scanf("%d",&historyforwrite);
    printf("Please enter the Geography grade: ");
    scanf("%d",&geographyforwrite);
    printf("Please enter the Politics grade: ");
    scanf("%d",&politicsforwrite);
    printf("Please enter the Physics grade: ");
    scanf("%d",&physicsforwrite);
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
    system("cls");
    }
    printf("All student grades have been entered. Press any key to return to the previous menu...");
    std::string c;
    std::cin>>c;
    return;
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
    return;
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
    return;
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
    return;
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
    return;
}

void showTeacherMenu(std::string teacherId){
    printf("================= Teacher Menu =================\n");
    printf("1.Show Teacher Information\n2.Write Student Grade\n3.Show Student Grade\n4.Add New Student\n5.Remove Student\n0.Exit");
    printf("\nPlease enter your choice: ");
    std::string choice;
    scanf("%s",&choice);
    if(choice=="1"){
        showTeacherInforation(teacherId);
    }else if(choice=="2"){
        writeStudentGrade(teacherId);
    }else if(choice=="3"){
        showStudentGrade(teacherId);
    }else if(choice=="4"){
        addStudent(teacherId);
    }else if(choice=="5"){
        removeStudent(teacherId);
    }else if(choice=="0"){
        return;
    }else{
        printf("Invalid choice. Please try again.\n");
    }
}

