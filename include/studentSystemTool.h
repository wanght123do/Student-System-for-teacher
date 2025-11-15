#include <iostream>
#include <vector>
#include <string>
#include <windows.h>

struct grade {
    std::string examYear;
    int chinese;
    int math;
    int english;
    int history;
    int geography;
    int biology;
    int physics;
    int politics;
};
struct student {
    std::string name;
    std::string id;
    std::string gender;
    std::string birthday;
    std::string password;
    bool ifAHeadGroup;
    std::string Groupinformation;
    std::vector<grade> grades;
};

std::vector<student> students;

struct teacher {
    std::string name;
    std::string id;
    std::string password;
};

std::vector<teacher> teachers;


void showAllUsers(){
    system("cls");
    std::cout<<"=======All Users======="<<std::endl;
    std::cout<<"---Teacher---"<<std::endl;
    for(int i=0;i<teachers.size();i++){
        std::cout<<"mame:"<<teachers[i].name<<", id:"<<teachers[i].id<<std::endl;
    }
    std::cout<<"\n";
    std::cout<<"---Student---"<<std::endl;
    for(int i=0;i<students.size();i++){
        std::cout<<"mame:"<<students[i].name<<", id:"<<students[i].id<<", password:"<<students[i].password<<std::endl;
    }
}
void removeStudent(){
    system("cls");
    std::string id;
    std::cout<<"Please enter the id of the student to be removed:"<<std::endl;
    std::cin>>id;
    for(int i=0;i<students.size();i++){
        if(students[i].id==id){
            students.erase(students.begin()+i);
            std::cout<<"Student removed successfully!"<<std::endl;
            return;
        }
    }
    std::cout<<"Student with the given id not found!"<<std::endl;
}

void addNewStudent(){
    system("cls");
    std::string name;
    std::string id;
    std::cout<<"Please enter the name of the new student:"<<std::endl;
    std::cin>>name;
    std::cout<<"Please enter the id of the new student:"<<std::endl;
    std::cin>>id;
    std::string password;
    std::cout<<"Please enter the password of the new student:"<<std::endl;
    std::cin>>password;
    student newStudent;
    newStudent.name=name;
    newStudent.id=id;
    newStudent.password=password;
    students.push_back(newStudent);
    std::cout<<"New student added successfully!"<<std::endl;
    return;
}

void exchangeStudentPassword(std::string studentId){
    system("cls");
    std::string newPassword;
    std::cout<<"Please enter the new password:"<<std::endl;
    std::cin>>newPassword;
    for(int i=0;i<students.size();i++){
        if(students[i].id==studentId){
            students[i].password=newPassword;
            std::cout<<"Password changed successfully!"<<std::endl;
            return;
        }
    }
    std::cout<<"Student with the given id not found!"<<std::endl;
}

void writerStudentGrede(){
    system("cls");
    std::string examYearForWrite;
    std::cout<<"Please enter the exam year of the grade you want to write:"<<std::endl;
    std::cin>>examYearForWrite;
    int chineseForWrite;
    int mathForWrite;
    int englishForWrite;
    int historyForWrite;
    int geographyForWrite;
    int biologyForWrite;
    int physicsForWrite;
    int politicsForWrite;
    for(int i=0;i<students.size();i++){
        std::cout<<"Please enter the grades for student "<<students[i].name<<" (ID: "<<students[i].id<<"):"<<std::endl;
        std::cout<<"Chinese: ";
        std::cin>>chineseForWrite;
        std::cout<<"Math: ";
        std::cin>>mathForWrite;
        std::cout<<"English: ";
        std::cin>>englishForWrite;
        std::cout<<"History: ";
        std::cin>>historyForWrite;
        std::cout<<"Geography: ";
        std::cin>>geographyForWrite;
        std::cout<<"Biology: ";
        std::cin>>biologyForWrite;
        std::cout<<"Physics: ";
        std::cin>>physicsForWrite;
        std::cout<<"Politics: ";
        std::cin>>politicsForWrite;
        grade newGrade;
        newGrade.examYear=examYearForWrite;
        newGrade.chinese=chineseForWrite;
        newGrade.math=mathForWrite;
        newGrade.english=englishForWrite;
        newGrade.history=historyForWrite;
        newGrade.geography=geographyForWrite;
        newGrade.biology=biologyForWrite;
        newGrade.physics=physicsForWrite;
        newGrade.politics=politicsForWrite;
        students[i].grades.push_back(newGrade);
        system("cls");
    }
    std::cout<<"Grades written successfully!"<<std::endl;
    system("cls");
}

void showstudentgrade(std::string studentId){
    for(int i=0;i<students.size();i++){
        if(students[i].id==studentId){
            system("cls");
            std::cout<<"======Your Grades======"<<std::endl;
            for(int j=0;j<students[i].grades.size();j++){
                std::cout<<"---Exam Year: "<<students[i].grades[j].examYear<<"---"<<std::endl;
                std::cout<<"Chinese: "<<students[i].grades[j].chinese<<std::endl;
                std::cout<<"Math: "<<students[i].grades[j].math<<std::endl;
                std::cout<<"English: "<<students[i].grades[j].english<<std::endl;
                std::cout<<"History: "<<students[i].grades[j].history<<std::endl;
                std::cout<<"Geography: "<<students[i].grades[j].geography<<std::endl;
                std::cout<<"Biology: "<<students[i].grades[j].biology<<std::endl;
                std::cout<<"Physics: "<<students[i].grades[j].physics<<std::endl;
                std::cout<<"Politics: "<<students[i].grades[j].politics<<std::endl;
                std::cout<<"\n"<<std::endl;
            }
            return;
        }
    }
    std::cout<<"Student with the given id not found!"<<std::endl;
    return;
}
void teacherMenu(){
    std::cout << "===========Teacher Menu===========" << std::endl;
    std::cout<<"1.ShowAllUsers\n2.add New Student\n3.Remove Student\n4.Exchange Student Password\n5.Write Student Grade\n6.Show student Grade\n0.Exit"<<std::endl;
    std::string choice;
    std::cin>>choice;
    if(choice=="1"){
        showAllUsers();
        std::cout<<"Press any key to return to the teacher menu..."<<std::endl;
        std::string keyWordForReturn;
        std::cin>>keyWordForReturn;
        system("cls");
        teacherMenu();
    }
    else if(choice=="2"){
        addNewStudent();
        std::cout<<"Press any key to return to the teacher menu..."<<std::endl;
        std::string keyWordForReturn;
        std::cin>>keyWordForReturn;
        system("cls");
        teacherMenu();
    }
    else if(choice=="3"){
        removeStudent();
        std::cout<<"Press any key to return to the teacher menu..."<<std::endl;
        std::string keyWordForReturn;
        std::cin>>keyWordForReturn;
        system("cls");
        teacherMenu();
    }
    else if(choice=="4"){
        system("cls");
        std::string studentId;
        std::cout<<"Please enter the id of the student whose password you want to change:"<<std::endl;
        std::cin>>studentId;
        exchangeStudentPassword(studentId);
        std::cout<<"Press any key to return to the teacher menu..."<<std::endl;
        std::string keyWordForReturn;
        std::cin>>keyWordForReturn;
        system("cls");
        teacherMenu();
    }
    else if(choice=="5"){
        writerStudentGrede();
        std::cout<<"Press any key to return to the teacher menu..."<<std::endl;
        std::string keyWordForReturn;
        std::cin>>keyWordForReturn;
        system("cls");
        teacherMenu();
    }
    else if(choice=="6"){
        system("cls");
        std::string studentId;
        std::cout<<"Please enter the id of the student whose grades you want to see:"<<std::endl;
        std::cin>>studentId;
        showstudentgrade(studentId);
        std::cout<<"Press any key to return to the teacher menu..."<<std::endl;
        std::string keyWordForReturn;
        std::cin>>keyWordForReturn;
        system("cls");
        teacherMenu();
    }
    else if(choice=="0"){
        system("cls");
        std::cout<<"Exiting teacher menu..."<<std::endl;
        Sleep(2000);
        system("cls");
    }
    else{
        std::cout<<"Invalid choice. Please try again."<<std::endl;
        Sleep(2000);
        system("cls");
        teacherMenu();
    }
}



void showStudentInformation(std::string studentId) {
    for(int i=0;i<students.size();i++){
        if(students[i].id==studentId){
            system("cls");
            std::cout<<"======Your Information======"<<std::endl;
            std::cout<<"---About Your Account---"<<std::endl;
            std::cout<<"Name: "<<students[i].name<<std::endl;
            std::cout<<"ID: "<<students[i].id<<std::endl;
            std::cout<<"Passcord: "<<students[i].password<<std::endl;
            std::cout<<"\n"<<std::endl;
            std::cout<<"---Personal Information---"<<std::endl;
            std::cout<<"Gender: "<<students[i].gender<<std::endl;
            std::cout<<"Birthday: "<<students[i].birthday<<std::endl;
            std::cout<<"Head Group: "<<(students[i].ifAHeadGroup ? "Yes" : "No")<<std::endl;
            std::cout<<"Group Information: "<<students[i].Groupinformation<<std::endl;
            return;
        }
    }
    std::cout<<"Student with the given id not found!"<<std::endl;
    return;
}
void studentMenu(std::string studentId){
    std::string studentIdLocal=studentId;
    std::cout << "===========Student Menu===========" << std::endl;
    std::cout<<"1.Your Information\n2.Show Your Grade\n0.Exit"<<std::endl;
    std::string choice;
    std::cin>>choice;
    if(choice=="1"){
        showStudentInformation(studentIdLocal);
        std::cout<<"Press any key to return to the student menu..."<<std::endl;
        std::string keyWordForReturn;
        std::cin>>keyWordForReturn;
        system("cls");
        studentMenu(studentIdLocal);
    }
    else if(choice=="2"){
        showstudentgrade(studentIdLocal);
        std::cout<<"Press any key to return to the student menu..."<<std::endl;
        std::string keyWordForReturn;
        std::cin>>keyWordForReturn;
        system("cls");
        studentMenu(studentIdLocal);
    }
    else if(choice=="0"){
        system("cls");
        std::cout<<"Exiting student menu..."<<std::endl;
        Sleep(2000);
        system("cls");
    }
    else{
        std::cout<<"Invalid choice. Please try again."<<std::endl;
        Sleep(2000);
        system("cls");
        studentMenu(studentIdLocal);
    }
}

bool confirmPassword(const std::string& password) {
    std::string passwordConfirm;
    std::cout << "Confirm your password: \n";
    std::cin >> passwordConfirm;
    return password == passwordConfirm;
}

void signIn(const std::string& id, const std::string& password) {
    // 检查学生
    for (size_t i = 0; i < students.size(); i++) {
        if (students[i].id == id && students[i].password == password) {
            std::cout << "Student login successful: " << students[i].name << std::endl;
            Sleep(2000);
            system("cls");
            studentMenu(students[i].id);
            return;
        }
    }
    
    // 检查教师
    for (size_t i = 0; i < teachers.size(); i++) {
        if (teachers[i].id == id && teachers[i].password == password) {
            std::cout << "Teacher login successful: " << teachers[i].name << std::endl;
            Sleep(2000);
            system("cls");
            teacherMenu();
            return;
        }
    }
    
    std::cout << "Login failed: Invalid ID or password.\n";
    Sleep(2000);
    system("cls");
}

void signUpStudent() {
    student newStudent;
    std::cout << "Your name: \n";
    std::cin >> newStudent.name;
    std::cout << "Your id: \n";
    std::cin >> newStudent.id;
    std::cout << "Are you a boy or a girl? \n";
    std::cin >> newStudent.gender;
    std::cout << "Your birthday: \n";
    std::cin >> newStudent.birthday;
    
    std::cout << "Your password: \n";
    std::cin >> newStudent.password;
    
    while (!confirmPassword(newStudent.password)) {
        std::cout << "Passwords do not match. Please try again.\n";
    }
    
    std::cout << "Are you a head group?(y/n) \n";
    char headGroupChoice;
    std::cin >> headGroupChoice;
    newStudent.ifAHeadGroup = (headGroupChoice == 'Y' || headGroupChoice == 'y');
    
    std::cout << "Enter your group information:(G1/G2/G3/G4/G5/G6) \n";
    std::cin >> newStudent.Groupinformation;
    
    students.push_back(newStudent);
    std::cout << "Student registration successful!\n";
    Sleep(2000);
    system("cls");
}

void signUpTeacher() {
    teacher newTeacher;
    std::cout << "Your name: \n";
    std::cin >> newTeacher.name;
    std::cout << "Your id: \n";
    std::cin >> newTeacher.id;
    
    std::cout << "Your password: \n";
    std::cin >> newTeacher.password;
    
    while (!confirmPassword(newTeacher.password)) {
        std::cout << "Passwords do not match. Please try again.\n";
    }
    
    teachers.push_back(newTeacher);
    std::cout << "Teacher registration successful!\n";
    Sleep(2000);
    system("cls");
}

void signUp() {
    std::string level;
    std::cout << "Do you want to be a student or a teacher? \n";
    std::cin >> level;
    
    if (level == "student") {
        signUpStudent();
        system("cls");
    } else if (level == "teacher") {
        signUpTeacher();
        system("cls");
    } else {
        std::cout << "Invalid choice. Please enter 'student' or 'teacher'.\n";
        system("cls");
    }
}

