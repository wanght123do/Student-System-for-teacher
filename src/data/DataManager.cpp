#include "data/DataManager.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <windows.h>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <algorithm>

// 包含JSON库
#include "../../third_party/json.hpp"
using json = nlohmann::json;

// 全局变量声明（在GlobalData.cpp中定义）
extern std::vector<Student> students;
extern std::vector<Teacher> teachers;
extern std::vector<Exam> exams;

// 静态成员初始化
std::string DataManager::dataFilePath = "data/students_data.json";
std::string DataManager::backupDir = "backups";
time_t DataManager::lastSaveTime = 0;
bool DataManager::unsavedChanges = false;

// 初始化DataManager
void DataManager::initialize() {
    std::cout << "========================================" << std::endl;
    std::cout << "   DataManager Initialization" << std::endl;
    std::cout << "========================================" << std::endl;
    
    // 创建必要目录
    if (!ensureDataDirectory()) {
        std::cerr << "Error: Failed to create data directories!" << std::endl;
        return;
    }
    
    std::cout << "✓ Data directory: data/" << std::endl;
    std::cout << "✓ Backup directory: backups/" << std::endl;
    std::cout << "✓ Data file: " << dataFilePath << std::endl;
    std::cout << "✓ JSON library: Available" << std::endl;
    
    // 检查数据文件是否存在
    if (std::filesystem::exists(dataFilePath)) {
        std::cout << "✓ Existing data file found" << std::endl;
    } else {
        std::cout << "○ No data file found, will create new" << std::endl;
    }
    
    std::cout << "========================================" << std::endl;
}

// 保存所有数据
bool DataManager::saveAllData() {
    std::cout << "\n[Data Save Process]" << std::endl;
    std::cout << "===================" << std::endl;
    
    // 创建备份
    if (std::filesystem::exists(dataFilePath)) {
        if (!createBackup()) {
            std::cout << "⚠ Warning: Failed to create backup" << std::endl;
        } else {
            std::cout << "✓ Backup created" << std::endl;
        }
    }
    
    // 保存到JSON
    std::cout << "Saving data to JSON file..." << std::endl;
    bool success = saveToJson();
    
    if (success) {
        lastSaveTime = time(nullptr);
        unsavedChanges = false;
        
        std::cout << "\n✓ Data saved successfully!" << std::endl;
        std::cout << "  File: " << dataFilePath << std::endl;
        std::cout << "  Students: " << students.size() << std::endl;
        std::cout << "  Teachers: " << teachers.size() << std::endl;
        std::cout << "  Exams: " << exams.size() << std::endl;
        
        // 计算总成绩记录数
        int totalGrades = 0;
        for (const auto& student : students) {
            totalGrades += student.grades.size();
        }
        std::cout << "  Grade records: " << totalGrades << std::endl;
        std::cout << "  Time: " << formatTime(lastSaveTime) << std::endl;
        
        // 同时创建文本备份
        backupToText();
    } else {
        std::cerr << "\n✗ Failed to save data!" << std::endl;
        std::cerr << "  Please check file permissions and disk space." << std::endl;
    }
    
    return success;
}

// 加载所有数据
bool DataManager::loadAllData() {
    std::cout << "\n[Data Load Process]" << std::endl;
    std::cout << "===================" << std::endl;
    
    // 检查JSON文件是否存在
    if (!std::filesystem::exists(dataFilePath)) {
        std::cout << "○ Data file not found: " << dataFilePath << std::endl;
        std::cout << "  Attempting to migrate from text files..." << std::endl;
        
        // 尝试从文本文件迁移
        if (migrateFromText()) {
            std::cout << "✓ Successfully migrated from text files" << std::endl;
            // 保存迁移后的数据为JSON
            saveAllData();
            return true;
        } else {
            std::cout << "○ Starting with empty database" << std::endl;
            // 创建空的JSON文件
            return saveAllData();
        }
    }
    
    std::cout << "Loading from JSON file: " << dataFilePath << std::endl;
    
    // 验证JSON文件
    if (!validateJsonFile(dataFilePath)) {
        std::cerr << "✗ JSON file validation failed!" << std::endl;
        std::cout << "  Trying to load from text backup..." << std::endl;
        return migrateFromText();
    }
    
    // 从JSON加载
    bool success = loadFromJson();
    
    if (success) {
        std::cout << "\n✓ Data loaded successfully!" << std::endl;
        std::cout << "  Students: " << students.size() << std::endl;
        std::cout << "  Teachers: " << teachers.size() << std::endl;
        std::cout << "  Exams: " << exams.size() << std::endl;
        unsavedChanges = false;
        
        // 计算总成绩记录数
        int totalGrades = 0;
        for (const auto& student : students) {
            totalGrades += student.grades.size();
        }
        std::cout << "  Grade records: " << totalGrades << std::endl;
        std::cout << "  File size: ";
        try {
            auto size = std::filesystem::file_size(dataFilePath);
            if (size < 1024) {
                std::cout << size << " bytes" << std::endl;
            } else if (size < 1024 * 1024) {
                std::cout << std::fixed << std::setprecision(2) << size / 1024.0 << " KB" << std::endl;
            } else {
                std::cout << std::fixed << std::setprecision(2) << size / (1024.0 * 1024.0) << " MB" << std::endl;
            }
        } catch (...) {
            std::cout << "Unknown" << std::endl;
        }
    } else {
        std::cerr << "\n✗ Failed to load data from JSON!" << std::endl;
        std::cout << "  Trying to load from text backup..." << std::endl;
        
        // 尝试从文本备份加载
        if (migrateFromText()) {
            std::cout << "✓ Loaded from text backup instead" << std::endl;
            // 重新保存为JSON
            saveAllData();
            return true;
        }
    }
    
    return success;
}

// 保存到JSON文件的具体实现
bool DataManager::saveToJson() {
    try {
        json data;
        
        // === 元数据 ===
        data["metadata"]["version"] = "1.0";
        data["metadata"]["created"] = getCurrentDateTime();
        data["metadata"]["last_modified"] = getCurrentDateTime();
        data["metadata"]["description"] = "Student Management System Data";
        data["metadata"]["generator"] = "DataManager JSON Module";
        
        // === 学生数据 ===
        data["students"] = json::array();
        for (const auto& student : students) {
            json studentJson;
            studentJson["id"] = student.id;
            studentJson["name"] = student.name;
            studentJson["gender"] = student.gender;
            studentJson["birthday"] = student.birthday;
            studentJson["password"] = student.password;
            studentJson["is_head_group"] = student.ifAHeadGroup;
            studentJson["group_info"] = student.Groupinformation;
            
            // 保存成绩
            studentJson["grades"] = json::array();
            for (const auto& grade : student.grades) {
                json gradeJson;
                gradeJson["exam_year"] = grade.examYear;
                gradeJson["chinese"] = grade.chinese;
                gradeJson["math"] = grade.math;
                gradeJson["english"] = grade.english;
                gradeJson["history"] = grade.history;
                gradeJson["geography"] = grade.geography;
                gradeJson["biology"] = grade.biology;
                gradeJson["physics"] = grade.physics;
                gradeJson["politics"] = grade.politics;
                gradeJson["total"] = grade.total;
                studentJson["grades"].push_back(gradeJson);
            }
            
            data["students"].push_back(studentJson);
        }
        
        // === 教师数据 ===
        data["teachers"] = json::array();
        for (const auto& teacher : teachers) {
            json teacherJson;
            teacherJson["id"] = teacher.id;
            teacherJson["name"] = teacher.name;
            teacherJson["password"] = teacher.password;
            teacherJson["subject"] = teacher.subject;
            data["teachers"].push_back(teacherJson);
        }
        
        // === 考试数据 ===
        data["exams"] = json::array();
        for (const auto& examItem : exams) {
            json examJson;
            examJson["subject"] = examItem.subject;
            examJson["date"] = examItem.date;
            examJson["name"] = examItem.name;
            
            // 将字符向量转换为字符串
            std::string answersStr;
            for (char c : examItem.answers) {
                answersStr += c;
            }
            examJson["answers"] = answersStr;
            
            data["exams"].push_back(examJson);
        }
        
        // === 统计信息 ===
        data["statistics"]["student_count"] = students.size();
        data["statistics"]["teacher_count"] = teachers.size();
        data["statistics"]["exam_count"] = exams.size();
        
        int totalGradeRecords = 0;
        for (const auto& student : students) {
            totalGradeRecords += student.grades.size();
        }
        data["statistics"]["total_grade_records"] = totalGradeRecords;
        data["statistics"]["last_update"] = getCurrentDateTime();
        
        // 写入文件
        std::ofstream file(dataFilePath);
        if (!file.is_open()) {
            std::cerr << "Error: Cannot open file for writing: " << dataFilePath << std::endl;
            return false;
        }
        
        file << data.dump(4);  // 缩进4个空格，方便阅读
        file.close();
        
        return true;
        
    } catch (const std::exception& e) {
        std::cerr << "JSON Save Error: " << e.what() << std::endl;
        return false;
    } catch (...) {
        std::cerr << "Unknown error during JSON save" << std::endl;
        return false;
    }
}

// 从JSON文件加载的具体实现
bool DataManager::loadFromJson() {
    try {
        // 清空现有数据
        students.clear();
        teachers.clear();
        exams.clear();
        
        // 读取文件
        std::ifstream file(dataFilePath);
        if (!file.is_open()) {
            std::cerr << "Error: Cannot open file: " << dataFilePath << std::endl;
            return false;
        }
        
        json data;
        file >> data;
        file.close();
        
        // 检查基本结构
        if (!data.is_object()) {
            std::cerr << "Error: Invalid JSON structure" << std::endl;
            return false;
        }
        
        // === 加载学生数据 ===
        if (data.contains("students") && data["students"].is_array()) {
            for (const auto& studentJson : data["students"]) {
                Student student;
                
                student.id = studentJson.value("id", "");
                student.name = studentJson.value("name", "");
                student.gender = studentJson.value("gender", "");
                student.birthday = studentJson.value("birthday", "");
                student.password = studentJson.value("password", "");
                student.ifAHeadGroup = studentJson.value("is_head_group", false);
                student.Groupinformation = studentJson.value("group_info", "");
                
                // 加载成绩
                if (studentJson.contains("grades") && studentJson["grades"].is_array()) {
                    for (const auto& gradeJson : studentJson["grades"]) {
                        Grade grade;
                        grade.examYear = gradeJson.value("exam_year", "");
                        grade.chinese = gradeJson.value("chinese", 0);
                        grade.math = gradeJson.value("math", 0);
                        grade.english = gradeJson.value("english", 0);
                        grade.history = gradeJson.value("history", 0);
                        grade.geography = gradeJson.value("geography", 0);
                        grade.biology = gradeJson.value("biology", 0);
                        grade.physics = gradeJson.value("physics", 0);
                        grade.politics = gradeJson.value("politics", 0);
                        grade.total = gradeJson.value("total", 0);
                        
                        student.grades.push_back(grade);
                    }
                }
                
                students.push_back(student);
            }
        }
        
        // === 加载教师数据 ===
        if (data.contains("teachers") && data["teachers"].is_array()) {
            for (const auto& teacherJson : data["teachers"]) {
                Teacher teacher;
                teacher.id = teacherJson.value("id", "");
                teacher.name = teacherJson.value("name", "");
                teacher.password = teacherJson.value("password", "");
                teacher.subject = teacherJson.value("subject", "");
                teachers.push_back(teacher);
            }
        }
        
        // === 加载考试数据 ===
        if (data.contains("exams") && data["exams"].is_array()) {
            for (const auto& examJson : data["exams"]) {
                Exam examItem;
                examItem.subject = examJson.value("subject", "");
                examItem.date = examJson.value("date", "");
                examItem.name = examJson.value("name", "");
                
                // 加载答案
                std::string answersStr = examJson.value("answers", "");
                for (char c : answersStr) {
                    examItem.answers.push_back(c);
                }
                
                exams.push_back(examItem);
            }
        }
        
        return true;
        
    } catch (const json::exception& e) {
        std::cerr << "JSON Parse Error: " << e.what() << std::endl;
        return false;
    } catch (const std::exception& e) {
        std::cerr << "Load Error: " << e.what() << std::endl;
        return false;
    } catch (...) {
        std::cerr << "Unknown error during JSON load" << std::endl;
        return false;
    }
}

// 备份到文本文件
bool DataManager::backupToText() {
    try {
        // 创建带时间戳的备份目录
        std::string timestamp = getTimestamp();
        std::string backupPath = backupDir + "/text_backup_" + timestamp;
        std::filesystem::create_directories(backupPath);
        
        std::cout << "\n[Creating Text Backup]" << std::endl;
        std::cout << "======================" << std::endl;
        
        // 备份学生数据
        std::string studentFile = backupPath + "/students.txt";
        std::ofstream studentOut(studentFile);
        if (!studentOut.is_open()) {
            std::cerr << "Error: Cannot create student backup file" << std::endl;
            return false;
        }
        
        for (const auto& student : students) {
            studentOut << student.name << " "
                      << student.id << " "
                      << student.gender << " "
                      << student.birthday << " "
                      << student.password << " "
                      << (student.ifAHeadGroup ? 1 : 0) << " "
                      << student.Groupinformation << "\n";
        }
        studentOut.close();
        std::cout << "✓ Students backup: " << studentFile << " (" << students.size() << " records)" << std::endl;
        
        // 备份教师数据
        std::string teacherFile = backupPath + "/teachers.txt";
        std::ofstream teacherOut(teacherFile);
        if (!teacherOut.is_open()) {
            std::cerr << "Error: Cannot create teacher backup file" << std::endl;
            return false;
        }
        
        for (const auto& teacher : teachers) {
            teacherOut << teacher.name << " "
                      << teacher.id << " "
                      << teacher.password << " "
                      << teacher.subject << "\n";
        }
        teacherOut.close();
        std::cout << "✓ Teachers backup: " << teacherFile << " (" << teachers.size() << " records)" << std::endl;
        
        // 创建备份信息文件
        std::string infoFile = backupPath + "/backup_info.txt";
        std::ofstream infoOut(infoFile);
        infoOut << "Text Backup Information\n";
        infoOut << "=======================\n";
        infoOut << "Backup time: " << getCurrentDateTime() << "\n";
        infoOut << "Students: " << students.size() << "\n";
        infoOut << "Teachers: " << teachers.size() << "\n";
        infoOut << "Exams: " << exams.size() << "\n";
        infoOut << "Original JSON: " << dataFilePath << "\n";
        infoOut << "Backup directory: " << backupPath << "\n";
        infoOut.close();
        
        std::cout << "✓ Backup info: " << infoFile << std::endl;
        std::cout << "✓ Text backup completed in: " << backupPath << std::endl;
        
        return true;
        
    } catch (const std::exception& e) {
        std::cerr << "Text Backup Error: " << e.what() << std::endl;
        return false;
    }
}

// 从文本文件迁移
bool DataManager::migrateFromText() {
    try {
        bool migrated = false;
        int studentCountBefore = students.size();
        int teacherCountBefore = teachers.size();
        
        std::cout << "\n[Text Migration]" << std::endl;
        std::cout << "================" << std::endl;
        
        // 迁移学生数据
        std::string studentFile = "build/students.txt";
        if (std::filesystem::exists(studentFile)) {
            std::ifstream studentIn(studentFile);
            if (studentIn.is_open()) {
                Student tempStudent;
                while (studentIn >> tempStudent.name >> tempStudent.id >> tempStudent.gender
                       >> tempStudent.birthday >> tempStudent.password >> tempStudent.ifAHeadGroup
                       >> tempStudent.Groupinformation) {
                    students.push_back(tempStudent);
                    migrated = true;
                }
                studentIn.close();
                std::cout << "✓ Students migrated: " << (students.size() - studentCountBefore) << " added" << std::endl;
            }
        } else {
            std::cout << "○ Students file not found: " << studentFile << std::endl;
        }
        
        // 迁移教师数据
        std::string teacherFile = "build/teachers.txt";
        if (std::filesystem::exists(teacherFile)) {
            std::ifstream teacherIn(teacherFile);
            if (teacherIn.is_open()) {
                Teacher tempTeacher;
                while (teacherIn >> tempTeacher.name >> tempTeacher.id >> tempTeacher.password
                       >> tempTeacher.subject) {
                    teachers.push_back(tempTeacher);
                    migrated = true;
                }
                teacherIn.close();
                std::cout << "✓ Teachers migrated: " << (teachers.size() - teacherCountBefore) << " added" << std::endl;
            }
        } else {
            std::cout << "○ Teachers file not found: " << teacherFile << std::endl;
        }
        
        if (migrated) {
            std::cout << "✓ Total migrated: " << students.size() << " students, " 
                     << teachers.size() << " teachers" << std::endl;
        } else {
            std::cout << "○ No data to migrate" << std::endl;
        }
        
        return migrated;
        
    } catch (const std::exception& e) {
        std::cerr << "Migration Error: " << e.what() << std::endl;
        return false;
    }
}

// 自动保存
void DataManager::autoSave() {
    static time_t lastAutoSave = 0;
    time_t now = time(nullptr);
    
    // 如果有未保存的更改且超过5分钟，自动保存
    if (unsavedChanges && (now - lastAutoSave > 300)) {  // 300秒 = 5分钟
        std::cout << "\n[Auto-saving data...]" << std::endl;
        saveAllData();
        lastAutoSave = now;
    }
}

// 手动保存
bool DataManager::manualSave() {
    return saveAllData();
}

// 获取数据统计
DataManager::DataStats DataManager::getStats() {
    DataStats stats;
    stats.studentCount = students.size();
    stats.teacherCount = teachers.size();
    stats.examCount = exams.size();
    stats.dataFilePath = dataFilePath;
    stats.lastSaveTime = formatTime(lastSaveTime);
    stats.storageMode = "JSON";
    
    stats.totalGradeRecords = 0;
    for (const auto& student : students) {
        stats.totalGradeRecords += student.grades.size();
    }
    
    return stats;
}

// 获取状态信息
std::string DataManager::getStatus() {
    DataStats stats = getStats();
    
    std::stringstream ss;
    ss << "\n[Data Status]" << std::endl;
    ss << "=============" << std::endl;
    ss << "Storage Mode: " << stats.storageMode << std::endl;
    ss << "Data File: " << stats.dataFilePath << std::endl;
    ss << "Students: " << stats.studentCount << std::endl;
    ss << "Teachers: " << stats.teacherCount << std::endl;
    ss << "Exams: " << stats.examCount << std::endl;
    ss << "Grade Records: " << stats.totalGradeRecords << std::endl;
    ss << "Last Save: " << stats.lastSaveTime << std::endl;
    ss << "Unsaved Changes: " << (unsavedChanges ? "Yes" : "No") << std::endl;
    
    // 添加文件信息
    try {
        if (std::filesystem::exists(dataFilePath)) {
            auto size = std::filesystem::file_size(dataFilePath);
            auto ftime = std::filesystem::last_write_time(dataFilePath);
            
            ss << "File Size: ";
            if (size < 1024) {
                ss << size << " bytes" << std::endl;
            } else if (size < 1024 * 1024) {
                ss << std::fixed << std::setprecision(2) << size / 1024.0 << " KB" << std::endl;
            } else {
                ss << std::fixed << std::setprecision(2) << size / (1024.0 * 1024.0) << " MB" << std::endl;
            }
        }
    } catch (...) {
        // 忽略文件信息错误
    }
    
    return ss.str();
}

// ========== 私有辅助方法 ==========

bool DataManager::ensureDataDirectory() {
    try {
        // 创建data目录
        if (!std::filesystem::exists("data")) {
            std::filesystem::create_directory("data");
        }
        
        // 创建backups目录
        if (!std::filesystem::exists(backupDir)) {
            std::filesystem::create_directory(backupDir);
        }
        
        // 创建每日备份子目录
        std::string today = getTimestamp().substr(0, 10);  // YYYY-MM-DD
        std::string dailyBackupDir = backupDir + "/" + today;
        if (!std::filesystem::exists(dailyBackupDir)) {
            std::filesystem::create_directory(dailyBackupDir);
        }
        
        return true;
    } catch (const std::exception& e) {
        std::cerr << "Directory Creation Error: " << e.what() << std::endl;
        return false;
    }
}

bool DataManager::createBackup() {
    try {
        if (!std::filesystem::exists(dataFilePath)) {
            return true;  // 没有文件需要备份
        }
        
        // 创建带时间戳的备份文件名
        std::string timestamp = getTimestamp();
        std::string today = timestamp.substr(0, 10);
        std::string backupFile = backupDir + "/" + today + "/backup_" + timestamp + ".json";
        
        // 复制文件
        std::filesystem::copy_file(dataFilePath, backupFile, 
                                  std::filesystem::copy_options::overwrite_existing);
        
        // 保持最近5个备份
        std::vector<std::string> backupFiles;
        std::string dailyDir = backupDir + "/" + today;
        
        if (std::filesystem::exists(dailyDir)) {
            for (const auto& entry : std::filesystem::directory_iterator(dailyDir)) {
                if (entry.path().extension() == ".json") {
                    backupFiles.push_back(entry.path().string());
                }
            }
            
            // 按修改时间排序
            std::sort(backupFiles.begin(), backupFiles.end(),
                     [](const std::string& a, const std::string& b) {
                         return std::filesystem::last_write_time(a) > 
                                std::filesystem::last_write_time(b);
                     });
            
            // 删除多余的备份
            while (backupFiles.size() > 5) {
                std::filesystem::remove(backupFiles.back());
                backupFiles.pop_back();
            }
        }
        
        return true;
    } catch (const std::exception& e) {
        std::cerr << "Backup Error: " << e.what() << std::endl;
        return false;
    }
}

std::string DataManager::getTimestamp() {
    time_t now = time(nullptr);
    struct tm* timeinfo = localtime(&now);
    
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d_%H-%M-%S", timeinfo);
    
    return std::string(buffer);
}

std::string DataManager::formatTime(time_t time) {
    if (time == 0) {
        return "Never";
    }
    
    struct tm* timeinfo = localtime(&time);
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);
    
    return std::string(buffer);
}

std::string DataManager::getCurrentDateTime() {
    time_t now = time(nullptr);
    struct tm* timeinfo = localtime(&now);
    
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);
    
    return std::string(buffer);
}

bool DataManager::validateJsonFile(const std::string& filepath) {
    try {
        std::ifstream file(filepath);
        if (!file.is_open()) {
            return false;
        }
        
        // 尝试解析JSON
        json data;
        file >> data;
        
        // 基本验证
        return data.is_object() && 
               data.contains("metadata") && 
               data.contains("students");
        
    } catch (...) {
        return false;
    }
}