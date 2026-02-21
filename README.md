# Student System For Teacher
A student system for teacher,we use cpp 14 to build is project.We provide student and teacher information service,geade information service and exam service.

## Contents
Teacher Management: View teacher information  

Student Management: View and add student information

## Core Function
### Teacher Function
Show Teacher Information

Write Student Grade

Show Student Grade

Add New Student

Remove Student

Change Student Password

Show All Users

Give A Student

Check Students Without Homework

Write Exam Information

Show Student Information
### Student Function
View Grade

Show Your Information

Change Your Password

View Exam Information

### Data Management
JSON file save data

Automatic backup

Persistent storage data

## System Architecture
```text
StudentSystem/
├── include/          
│   ├── auth/        
│   ├── entities/    
│   ├── menus/      
│   └── services/    
├── src/             
│   ├── auth/        
│   ├── entities/    
│   ├── menus/       
│   └── services/    
├── third_party/     
│   └── json.hpp    
├── build/          
├── backups/        
└── data/          
```
## Quick Start
### Environment
Just windows(windows 7/8/8.1/10/11 all right)
### run choice 
#### first
```bush
g++ -std=c++17 -Iinclude src/*.cpp src/*/*.cpp -o StudentManagementSystem.exe
```
#### second
``` bush
.\build.bat
```
## Version
We follow the semantic versioning specification
### Official version
vx.x.x
### Pre-releases 
vx.x.x-beta.x - Beta Release  

vx.x.x-alpha.x - Alpha Release  

vx.x.x-rc.x - Release Candidate  

vx.x.x-dev - Development Build  

## Detailed Project Structure
```text
D:\CODING\STUDENTSYSTEM
│
├── .gitignore          
├── build.bat            
├── test.bat             
├── README.md            
├── UpdateLog.md         
├── LICENSE              
├── version.txt          
│
├── include/             
│   ├── auth/
│   │   └── AuthService.h
│   ├── entities/
│   │   ├── Student.h
│   │   ├── Teacher.h
│   │   ├── Grade.h
│   │   ├── Exam.h
│   │   └── GlobalData.h
│   ├── menus/
│   │   ├── StudentMenu.h
│   │   └── TeacherMenu.h
│   └── services/
│       ├── StudentService.h
│       ├── GradeService.h
│       ├── ExamService.h
│       └── InformationService.h
│
└── src/                 
    ├── main.cpp
    ├── auth/
    ├── entities/
    ├── menus/
    └── services/
```

## Develop Team
member:wanght123do  

email:wanghaotang123@hotmail.com  

## License
This project is licensed under the MIT License - see the LICENSE file for details
```text
MIT License

Copyright (c) 2026 Wang Haotang(@wanght123do)

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

```
## Support Project
if you like this project,welcome give a star!⭐

## THANK YOU FOR USE STUDENT SYSTEM!
