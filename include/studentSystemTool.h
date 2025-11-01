#include <iostream>
#include <vector>
#include <string>
#include <windows.h>

struct student {
    std::string name;
    std::string id;
    std::string gender;
    std::string birthday;
    std::string password;
    bool ifAHeadGroup;
    std::string Groupinformation;
};

std::vector<student> students;

struct teacher {
    std::string name;
    std::string id;
    std::string password;
};

std::vector<teacher> teachers;


void showAllUsers(){
    std::cout<<"=======All Users======="<<std::endl;
    std::cout<<"---Teacher---"<<std::endl;
    for(int i=0;i<teachers.size();i++){
        std::cout<<"mame:"<<teachers[i].name<<", id:"<<teachers[i].id<<std::endl;
    }
    std::cout<<"---Student---"<<std::endl;
    for(int i=0;i<students.size();i++){
        std::cout<<"mame:"<<students[i].name<<", id:"<<students[i].id<<std::endl;
    }
}

void addNewStudent(){
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
}


void teacherMenu(){
    std::cout << "===========Teacher Menu===========" << std::endl;
    std::cout<<"1.ShowAllUsers\n2.add New Student\n3.Exit"<<std::endl;
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
    if(choice=="2"){
        addNewStudent();
        std::cout<<"Press any key to return to the teacher menu..."<<std::endl;
        std::string keyWordForReturn;
        std::cin>>keyWordForReturn;
        system("cls");
        teacherMenu();
    }
    if(choice=="3"){
        std::cout<<"Exiting teacher menu..."<<std::endl;
        Sleep(2000);
        system("cls");
    }
}

void studentMenu(){
    std::cout << "===========Student Menu===========" << std::endl;
    std::cout<<"1.Exit"<<std::endl;
    std::string choice;
    std::cin>>choice;
    if(choice=="1"){
        std::cout<<"Exiting student menu..."<<std::endl;
        Sleep(2000);
        system("cls");
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
            studentMenu();
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

