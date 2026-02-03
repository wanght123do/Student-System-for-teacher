#ifndef EXAM_SERVICE_H
#define EXAM_SERVICE_H

#include <vector>
#include "../entities/Exam.h"  // 使用统一的Exam定义

// 现在使用Exam（大写E）而不是exam
extern std::vector<Exam> exams;

// 函数声明
void loadExamsFromDatabase();
void initializeExams();

#endif