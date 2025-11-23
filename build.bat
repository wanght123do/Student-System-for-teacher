@echo off
chcp 65001 > nul
title Student Management System Compiler

g++ --version > nul 2>&1
if %errorlevel% neq 0 (
    echo ERROR: g++ compiler not found!
    pause
    exit /b 1
)

if not exist "build" mkdir build
if not exist "build\release" mkdir build\release

echo.
echo ========================================
echo    Building Student Management System
echo ========================================
echo.

echo Compiling source files...
echo Please wait...
echo Around one minute may be needed for the first build...
g++ -c src/main.cpp -Iinclude -std=c++11 -static -o build/main.o
g++ -c src/entities/GlobalData.cpp -Iinclude -std=c++11 -static -o build/GlobalData.o
g++ -c src/auth/AuthService.cpp -Iinclude -std=c++11 -static -o build/AuthService.o
g++ -c src/menus/StudentMenu.cpp -Iinclude -std=c++11 -static -o build/StudentMenu.o
g++ -c src/menus/TeacherMenu.cpp -Iinclude -std=c++11 -static -o build/TeacherMenu.o
g++ -c src/services/GradeService.cpp -Iinclude -std=c++11 -static -o build/GradeService.o

echo Linking...
g++ build/main.o build/GlobalData.o build/AuthService.o build/StudentMenu.o build/TeacherMenu.o build/GradeService.o -static -static-libgcc -static-libstdc++ -o build/release/StudentManagementSystem.exe

if %errorlevel% equ 0 (
    echo.
    echo ========================================
    echo    BUILD SUCCESSFUL!
    echo ========================================
    echo Executable: build\release\StudentManagementSystem.exe
    echo.
    build\release\StudentManagementSystem.exe
) else (
    echo.
    echo ========================================
    echo    BUILD FAILED!
    echo ========================================
    pause
)