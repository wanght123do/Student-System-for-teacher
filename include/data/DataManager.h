#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <string>
#include <vector>
#include "../entities/Student.h"
#include "../entities/Teacher.h"
#include "../entities/Exam.h"  // 包含Exam定义

class DataManager {
public:
    // 初始化
    static void initialize();
    
    // 保存所有数据到JSON文件
    static bool saveAllData();
    
    // 从JSON文件加载所有数据
    static bool loadAllData();
    
    // 自动保存（可定时调用）
    static void autoSave();
    
    // 备份数据到文本文件（兼容性）
    static bool backupToText();
    
    // 从文本文件迁移数据
    static bool migrateFromText();
    
    // 获取数据状态信息
    static std::string getStatus();
    
    // 手动触发保存
    static bool manualSave();
    
    // 检查是否有未保存的更改
    static bool hasUnsavedChanges() { return unsavedChanges; }
    
    // 标记数据已更改
    static void markDataChanged() { unsavedChanges = true; }
    
    // 数据统计结构
    struct DataStats {
        int studentCount;
        int teacherCount;
        int examCount;
        int totalGradeRecords;
        std::string lastSaveTime;
        std::string dataFilePath;
        std::string storageMode;
    };
    
    // 获取统计数据
    static DataStats getStats();
    
    // 获取JSON文件路径
    static std::string getDataFilePath() { return dataFilePath; }
    
    // 设置JSON文件路径
    static void setDataFilePath(const std::string& path) { dataFilePath = path; }

private:
    static std::string dataFilePath;
    static std::string backupDir;
    static time_t lastSaveTime;
    static bool unsavedChanges;
    
    // 具体保存/加载方法
    static bool saveToJson();
    static bool loadFromJson();
    
    // 内部辅助方法
    static bool ensureDataDirectory();
    static std::string getTimestamp();
    static bool createBackup();
    static std::string formatTime(time_t time);
    static std::string getCurrentDateTime();
    static bool validateJsonFile(const std::string& filepath);
};

#endif // DATAMANAGER_H