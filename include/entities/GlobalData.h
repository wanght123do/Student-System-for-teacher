#ifndef GLOBALDATA_H
#define GLOBALDATA_H

#include <vector>

// 前向声明
class Database;
struct Student;
struct Teacher;
struct Exam;  // 修改这一行，从 exam 改为 Exam

// 全局变量声明
extern Database* globalDB;
extern std::vector<Student> students;
extern std::vector<Teacher> teachers;
extern std::vector<Exam> exams;  // 修改这一行，从 exam 改为 Exam

#endif // GLOBALDATA_H