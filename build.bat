@echo off
chcp 65001 > nul
title Student Management System Compiler - Auto Fix

:: 备份并修复源文件
echo Backing up and fixing source files...

:: 修复 StudentMenu.cpp
if exist "src/menus/StudentMenu.cpp" (
    copy "src/menus/StudentMenu.cpp" "src/menus/StudentMenu.cpp.backup" >nul
    (
        echo #include "entities/Grade.h"
        echo #include "services/GradeService.h"
        echo #include "menus/teacherMenu.h"
        echo #include "entities/Teacher.h"
        echo #include "entities/Student.h"
        echo #include ^<iostream^>
        echo #include ^<string^>
        echo #include ^<vector^>
        echo #include ^<windows.h^>
        type "src/menus/StudentMenu.cpp" | findstr /v "#include"
    ) > "src/menus/StudentMenu.cpp.fixed"
    move "src/menus/StudentMenu.cpp.fixed" "src/menus/StudentMenu.cpp" >nul
)

:: 修复 TeacherMenu.cpp  
if exist "src/menus/TeacherMenu.cpp" (
    copy "src/menus/TeacherMenu.cpp" "src/menus/TeacherMenu.cpp.backup" >nul
    (
        echo #include "entities/Grade.h"
        echo #include "services/GradeService.h"
        echo #include "menus/teacherMenu.h"
        echo #include "entities/Teacher.h"
        echo #include ^<iostream^>
        echo #include ^<string^>
        echo #include ^<vector^>
        echo #include ^<windows.h^>
        echo #include "entities/Student.h"
        type "src/menus/TeacherMenu.cpp" | findstr /v "#include"
    ) > "src/menus/TeacherMenu.cpp.fixed"
    move "src/menus/TeacherMenu.cpp.fixed" "src/menus/TeacherMenu.cpp" >nul
)

:: 修复 AuthService.cpp
if exist "src/auth/AuthService.cpp" (
    copy "src/auth/AuthService.cpp" "src/auth/AuthService.cpp.backup" >nul
    (
        echo #include "auth/AuthService.h"
        echo #include ^<iostream^>
        echo #include ^<windows.h^>
        type "src/auth/AuthService.cpp" | findstr /v "#include"
    ) > "src/auth/AuthService.cpp.fixed"
    move "src/auth/AuthService.cpp.fixed" "src/auth/AuthService.cpp" >nul
)

echo Source files fixed successfully!
echo.

:: 现在编译
if not exist "build" mkdir build
if not exist "build\release" mkdir build\release

echo Compiling main.cpp...
g++ -c src/main.cpp -Iinclude -std=c++11 -static -o build/main.o
if %errorlevel% neq 0 goto restore

echo Compiling StudentMenu.cpp...
g++ -c src/menus/StudentMenu.cpp -Iinclude -std=c++11 -static -o build/StudentMenu.o
if %errorlevel% neq 0 goto restore

echo Compiling TeacherMenu.cpp...
g++ -c src/menus/TeacherMenu.cpp -Iinclude -std=c++11 -static -o build/TeacherMenu.o
if %errorlevel% neq 0 goto restore

echo Compiling AuthService.cpp...
g++ -c src/auth/AuthService.cpp -Iinclude -std=c++11 -static -o build/AuthService.o
if %errorlevel% neq 0 goto restore

echo Linking...
g++ build/main.o build/StudentMenu.o build/TeacherMenu.o build/AuthService.o -static -static-libgcc -static-libstdc++ -o build/release/StudentManagementSystem.exe
if %errorlevel% neq 0 (
    g++ build/main.o build/StudentMenu.o build/TeacherMenu.o build/AuthService.o -o build/release/StudentManagementSystem.exe
    if %errorlevel% neq 0 goto restore
)

echo.
echo ========================================
echo    BUILD SUCCESSFUL!
echo ========================================
echo Backup files created with .backup extension
echo Executable: build\release\StudentManagementSystem.exe
echo.

choice /C YN /M "Run the program now"
if %errorlevel% equ 1 (
    echo.
    build\release\StudentManagementSystem.exe
)

pause
exit /b 0

:restore
echo.
echo Restoring original files...
if exist "src/menus/StudentMenu.cpp.backup" move "src/menus/StudentMenu.cpp.backup" "src/menus/StudentMenu.cpp" >nul
if exist "src/menus/TeacherMenu.cpp.backup" move "src/menus/TeacherMenu.cpp.backup" "src/menus/TeacherMenu.cpp" >nul  
if exist "src/auth/AuthService.cpp.backup" move "src/auth/AuthService.cpp.backup" "src/auth/AuthService.cpp" >nul
echo Build failed! Original files restored.
pause
exit /b 1