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