@echo off
chcp 65001 > nul
title Student Management System Compiler

set "MINGW_URL=https://github.com/niXman/mingw-builds-binaries/releases/download/13.2.0-rt_v11-rev2/x86_64-13.2.0-release-win32-seh-msvcrt-rt_v11-rev2.7z"
set "MINGW_ARCHIVE=mingw64.7z"
set "MINGW_DIR=mingw64"

echo.
echo ========================================
echo    Student Management System Compiler
echo ========================================
echo.

:CHECK_COMPILER
echo Checking for g++ compiler...
g++ --version > nul 2>&1
if %errorlevel% equ 0 (
    echo ✓ g++ compiler found.
    goto :COMPILE
)

echo ✗ g++ compiler not found!

:DOWNLOAD_MENU
echo.
echo [1] Download MinGW-w64 automatically (Recommended)
echo [2] Manually specify g++ path
echo [3] Exit
echo.
set /p choice="Choose option (1-3): "

if "%choice%"=="1" goto :DOWNLOAD_MINGW
if "%choice%"=="2" goto :MANUAL_PATH
if "%choice%"=="3" exit /b 0
echo Invalid choice!
goto :DOWNLOAD_MENU

:DOWNLOAD_MINGW
echo.
echo Downloading MinGW-w64...

REM Check if curl is available
where curl > nul 2>&1
if %errorlevel% neq 0 (
    echo curl not found. Checking for PowerShell...
    powershell -Command "Get-Command curl" > nul 2>&1
    if %errorlevel% neq 0 (
        echo Installing curl via PowerShell...
        powershell -Command "Invoke-WebRequest -Uri 'https://curl.se/windows/dl-8.8.0_4/curl-8.8.0_4-win64-mingw.zip' -OutFile 'curl.zip'" > nul 2>&1
        if exist curl.zip (
            powershell -Command "Expand-Archive -Path 'curl.zip' -DestinationPath 'curl_temp' -Force" > nul 2>&1
            copy curl_temp\curl-8.8.0_4-win64-mingw\bin\curl.exe . > nul 2>&1
            rmdir /s /q curl_temp > nul 2>&1
            del curl.zip > nul 2>&1
        )
    )
)

echo Downloading MinGW-w64 (this may take a few minutes)...
if exist curl.exe (
    curl -L -o "%MINGW_ARCHIVE%" "%MINGW_URL%" --progress-bar
) else (
    powershell -Command "Invoke-WebRequest -Uri '%MINGW_URL%' -OutFile '%MINGW_ARCHIVE%'" > nul 2>&1
)

if not exist "%MINGW_ARCHIVE%" (
    echo Failed to download MinGW-w64!
    goto :DOWNLOAD_MENU
)

echo.
echo Extracting MinGW-w64...

REM Check for 7-Zip
where 7z > nul 2>&1
if %errorlevel% neq 0 (
    echo 7-Zip not found. Using built-in PowerShell...
    powershell -Command "Expand-Archive -Path '%MINGW_ARCHIVE%' -DestinationPath '.' -Force" > nul 2>&1
) else (
    7z x "%MINGW_ARCHIVE%" -y > nul
)

if not exist "%MINGW_DIR%\bin\g++.exe" (
    echo Extraction failed or directory structure changed.
    echo Please check the downloaded archive.
    goto :DOWNLOAD_MENU
)

REM Add MinGW to PATH temporarily
set "PATH=%cd%\%MINGW_DIR%\bin;%PATH%"
echo ✓ MinGW-w64 installed successfully!
echo Added to PATH for this session.
goto :CHECK_COMPILER

:MANUAL_PATH
echo.
set /p mingw_path="Enter path to MinGW bin directory (e.g., C:\mingw64\bin): "
if not exist "%mingw_path%\g++.exe" (
    echo g++.exe not found in the specified path!
    goto :MANUAL_PATH
)

set "PATH=%mingw_path%;%PATH%"
echo ✓ g++ added to PATH.
goto :CHECK_COMPILER

:COMPILE
echo.
echo ========================================
echo    Building Student Management System
echo ========================================
echo.

REM Clean build directory first to avoid duplicate files
if exist build\obj (
    echo Cleaning previous object files...
    del build\obj\*.o 2>nul
)

REM Create build directories
if not exist "build" mkdir build
if not exist "build\release" mkdir build\release
if not exist "build\obj" mkdir build\obj

echo Compiling source files...
echo Please wait...

setlocal enabledelayedexpansion
set "compile_success=1"

echo.
echo Finding all C++ source files...
set file_count=0

REM 查找所有cpp文件
for /r src %%f in (*.cpp) do (
    echo Found: %%f
    set /a file_count+=1
)

echo.
echo Total source files: !file_count!
echo.

REM 编译所有文件
echo [1/2] Compiling all source files...
set compiled_count=0

for /r src %%f in (*.cpp) do (
    echo Compiling: %%~nxf
    for %%i in ("%%f") do set "filename=%%~ni"
    g++ -c "%%f" -Iinclude -std=c++11 -static -static-libgcc -static-libstdc++ -o "build\obj\!filename!.o" 2>&1
    if !errorlevel! neq 0 (
        echo Error compiling %%~nxf
        set "compile_success=0"
    ) else (
        set /a compiled_count+=1
    )
)

echo.
echo Compiled: !compiled_count! files
echo.

if !compile_success! equ 0 (
    echo ========================================
    echo    COMPILATION FAILED!
    echo ========================================
    pause
    exit /b 1
)

echo [2/2] Linking object files...
echo.

REM 链接所有对象文件
g++ build\obj\*.o -static -static-libgcc -static-libstdc++ -o build\release\StudentManagementSystem.exe

if !errorlevel! equ 0 (
    echo.
    echo ========================================
    echo    BUILD SUCCESSFUL!
    echo ========================================
    echo Executable created: build\release\StudentManagementSystem.exe
    echo.
    
    REM 自动运行程序
    echo Auto-running the program...
    echo ========================================
    echo.
    timeout /t 2 /nobreak >nul
    
    REM 运行程序
    cd build\release
    StudentManagementSystem.exe
    cd ..\..
    
    echo.
    echo ========================================
    echo    Program execution completed
    echo ========================================
    echo.
    REM 询问是否清理
    echo.
    set /p cleanup="Clean up object files? (Y/N): "
    if /i "!cleanup!"=="Y" (
        if exist build\obj del build\obj\*.o
        echo Object files cleaned.
    )
) else (
    echo.
    echo ========================================
    echo    LINKING FAILED!
    echo ========================================
    echo.
    echo Object files in build\obj\:
    dir /b build\obj\*.o
    echo.
    pause
    exit /b 1
)

echo.
echo ========================================
echo    Build process completed!
echo ========================================
echo.
pause