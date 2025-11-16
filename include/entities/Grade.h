#ifndef GRADE_H
#define GRADE_H

#include <string>

struct Grade {
    std::string examYear;
    int chinese;
    int math;
    int english;
    int history;
    int geography;
    int biology;
    int physics;
    int politics;
    int total;
    
    // 计算总分的方法
    void calculateTotal();
};

#endif