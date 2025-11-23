#include "../../include/services/GradeService.h"
#include <iostream>
#include <windows.h>

void countGradeTotal(std::vector<Student>& students){
    for(int i = 0; i < students.size(); ++i){
        for(int j = 0; j < students[i].grades.size(); ++j){
            students[i].grades[j].total = students[i].grades[j].chinese +
                                          students[i].grades[j].math +
                                          students[i].grades[j].english +
                                          students[i].grades[j].history +
                                          students[i].grades[j].geography +
                                          students[i].grades[j].biology +
                                          students[i].grades[j].physics +
                                          students[i].grades[j].politics;
        }
    }
}