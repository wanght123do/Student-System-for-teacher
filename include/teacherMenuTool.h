#include <string>
#include <iostream>
//#include <studentSystemTool.h>
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