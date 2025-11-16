@echo off
chcp 65001 > nul
title Student Management System Compiler
echo ========================================
echo    Student Management System Compiler
echo ========================================

:: 检查g++是否可用
g++ --version > nul 2>&1
if %errorlevel% neq 0 (
    echo ERROR: g++ compiler not found!
    echo Please install MinGW or add g++ to your PATH
    pause
    exit /b 1
)

:: 创建build目录（如果不存在）
if not exist "build" mkdir build

echo.
echo Step 1: Cleaning previous build...
if exist "build\StudentManagementSystem.exe" del "build\StudentManagementSystem.exe"
if exist "build\*.o" del "build\*.o"

echo.
echo Step 2: Compiling source files...

:: 编译各个模块
echo Compiling entities...
g++ -c src/entities/Student.cpp -Iinclude -std=c++11 -o build/Student.o
if %errorlevel% neq 0 goto error

g++ -c src/entities/Grade.cpp -Iinclude -std=c++11 -o build/Grade.o
if %errorlevel% neq 0 goto error

echo Compiling services...
g++ -c src/services/StudentService.cpp -Iinclude -std=c++11 -o build/StudentService.o
if %errorlevel% neq 0 goto error

g++ -c src/services/GradeService.cpp -Iinclude -std=c++11 -o build/GradeService.o
if %errorlevel% neq 0 goto error

echo Compiling auth...
g++ -c src/auth/AuthService.cpp -Iinclude -std=c++11 -o build/AuthService.o
if %errorlevel% neq 0 goto error

echo Compiling main...
g++ -c src/main.cpp -Iinclude -std=c++11 -o build/main.o
if %errorlevel% neq 0 goto error

echo.
echo Step 3: Linking all object files...
g++ build/main.o build/Student.o build/Grade.o build/StudentService.o build/GradeService.o build/AuthService.o -o build/StudentManagementSystem.exe
if %errorlevel% neq 0 goto error

echo.
echo ========================================
echo    COMPILATION SUCCESSFUL!
echo ========================================
echo Executable: build\StudentManagementSystem.exe
echo.

:: 询问是否运行程序
choice /C YN /M "Do you want to run the program now"
if %errorlevel% equ 1 (
    echo.
    echo Starting Student Management System...
    timeout /t 2 /nobreak > nul
    build\StudentManagementSystem.exe
) else (
    echo.
    echo You can run the program manually: build\StudentManagementSystem.exe
)

pause
exit /b 0

:error
echo.
echo ========================================
echo    COMPILATION FAILED!
echo ========================================
echo Please check the errors above and fix your code.
pause
exit /b 1