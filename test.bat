@echo off
chcp 65001 > nul
title Download JSON Library

echo.
echo ========================================
echo    Downloading nlohmann/json Library
echo ========================================
echo.

echo [1] Checking current directory...
if not exist third_party mkdir third_party

echo.
echo [2] Downloading json.hpp...
echo Downloading from GitHub...
echo.

REM 方法1: 使用curl
where curl >nul 2>&1
if %errorlevel% equ 0 (
    echo Using curl...
    curl -L -o third_party\json.hpp https://github.com/nlohmann/json/releases/latest/download/json.hpp
    goto :check_download
)

REM 方法2: 使用powershell
echo Trying PowerShell...
powershell -Command "Invoke-WebRequest -Uri 'https://github.com/nlohmann/json/releases/latest/download/json.hpp' -OutFile 'third_party\json.hpp'"
if %errorlevel% equ 0 goto :check_download

REM 方法3: 使用wget (如果存在)
where wget >nul 2>&1
if %errorlevel% equ 0 (
    echo Using wget...
    wget -O third_party\json.hpp https://github.com/nlohmann/json/releases/latest/download/json.hpp
    goto :check_download
)

REM 方法4: 创建最小版本
echo All download methods failed. Creating minimal version...
goto :create_minimal

:check_download
if exist third_party\json.hpp (
    echo.
    echo ✓ Successfully downloaded json.hpp
    echo File size: 
    for %%F in (third_party\json.hpp) do echo   %%~zF bytes
    echo.
    echo First few lines:
    echo =================
    head -10 third_party\json.hpp
    echo =================
    goto :end
) else (
    echo ❌ Download failed
    goto :create_minimal
)

:create_minimal
echo.
echo Creating minimal json.hpp for testing...
(
echo // nlohmann/json - Minimal version for Student Management System
echo // Full version available at: https://github.com/nlohmann/json
echo #ifndef NLOHMANN_JSON_HPP
echo #define NLOHMANN_JSON_HPP
echo.
echo #include <map>
echo #include <vector>
echo #include <string>
echo #include <fstream>
echo #include <sstream>
echo #include <iostream>
echo.
echo namespace nlohmann {
echo.
echo class json {
echo public:
echo     enum class value_t {
echo         null,
echo         object,
echo         array,
echo         string,
echo         boolean,
echo         number_integer,
echo         number_unsigned,
echo         number_float,
echo         discarded
echo     };
echo     
echo     // Basic constructors
echo     json() : m_type(value_t::null) {}
echo     json(std::nullptr_t) : m_type(value_t::null) {}
echo     json(const char* val) : m_type(value_t::string), m_string(val) {}
echo     json(const std::string& val) : m_type(value_t::string), m_string(val) {}
echo     json(bool val) : m_type(value_t::boolean), m_bool(val) {}
echo     json(int val) : m_type(value_t::number_integer), m_int(val) {}
echo     json(double val) : m_type(value_t::number_float), m_double(val) {}
echo     
echo     // Array constructor
echo     template<typename T>
echo     json(const std::vector<T>& arr) : m_type(value_t::array) {
echo         for (const auto& item : arr) {
echo             m_array.push_back(json(item));
echo         }
echo     }
echo     
echo     // Object constructor
echo     template<typename T>
echo     json(const std::map<std::string, T>& obj) : m_type(value_t::object) {
echo         for (const auto& pair : obj) {
echo             m_object[pair.first] = json(pair.second);
echo         }
echo     }
echo     
echo     // Check type
echo     bool is_null() const { return m_type == value_t::null; }
echo     bool is_object() const { return m_type == value_t::object; }
echo     bool is_array() const { return m_type == value_t::array; }
echo     bool is_string() const { return m_type == value_t::string; }
echo     bool is_boolean() const { return m_type == value_t::boolean; }
echo     bool is_number() const { return m_type == value_t::number_integer || m_type == value_t::number_float; }
echo     
echo     // Value access
echo     template<typename T>
echo     T value(const std::string& key, T default_value) const {
echo         if (m_type != value_t::object) return default_value;
echo         auto it = m_object.find(key);
echo         if (it == m_object.end()) return default_value;
echo         return static_cast<T>(it->second);
echo     }
echo     
echo     bool contains(const std::string& key) const {
echo         return m_type == value_t::object && m_object.find(key) != m_object.end();
echo     }
echo     
echo     // Array access
echo     json& operator[](size_t index) {
echo         if (m_type != value_t::array) {
echo             m_type = value_t::array;
echo         }
echo         if (index >= m_array.size()) {
echo             m_array.resize(index + 1);
echo         }
echo         return m_array[index];
echo     }
echo     
echo     // Object access
echo     json& operator[](const std::string& key) {
echo         if (m_type != value_t::object) {
echo             m_type = value_t::object;
echo         }
echo         return m_object[key];
echo     }
echo     
echo     const json& operator[](const std::string& key) const {
echo         static json null_json;
echo         if (m_type != value_t::object) return null_json;
echo         auto it = m_object.find(key);
echo         if (it == m_object.end()) return null_json;
echo         return it->second;
echo     }
echo     
echo     // Push back for arrays
echo     void push_back(const json& val) {
echo         if (m_type != value_t::array) {
echo             m_type = value_t::array;
echo         }
echo         m_array.push_back(val);
echo     }
echo     
echo     // Dump to string
echo     std::string dump(int indent = -1) const {
echo         std::ostringstream oss;
echo         dump(oss, 0, indent);
echo         return oss.str();
echo     }
echo     
echo private:
echo     void dump(std::ostringstream& oss, int depth, int indent) const {
echo         switch (m_type) {
echo             case value_t::null:
echo                 oss << "null";
echo                 break;
echo             case value_t::boolean:
echo                 oss << (m_bool ? "true" : "false");
echo                 break;
echo             case value_t::number_integer:
echo                 oss << m_int;
echo                 break;
echo             case value_t::number_float:
echo                 oss << m_double;
echo                 break;
echo             case value_t::string:
echo                 oss << '"' << escape_string(m_string) << '"';
echo                 break;
echo             case value_t::array:
echo                 oss << '[';
echo                 for (size_t i = 0; i < m_array.size(); ++i) {
echo                     if (i > 0) oss << ',';
echo                     if (indent >= 0) oss << '\n' << std::string(depth + indent, ' ');
echo                     m_array[i].dump(oss, depth + indent, indent);
echo                 }
echo                 if (indent >= 0 && !m_array.empty()) oss << '\n' << std::string(depth, ' ');
echo                 oss << ']';
echo                 break;
echo             case value_t::object:
echo                 oss << '{';
echo                 size_t i = 0;
echo                 for (const auto& pair : m_object) {
echo                     if (i++ > 0) oss << ',';
echo                     if (indent >= 0) oss << '\n' << std::string(depth + indent, ' ');
echo                     oss << '"' << escape_string(pair.first) << "\": ";
echo                     pair.second.dump(oss, depth + indent, indent);
echo                 }
echo                 if (indent >= 0 && !m_object.empty()) oss << '\n' << std::string(depth, ' ');
echo                 oss << '}';
echo                 break;
echo         }
echo     }
echo     
echo     std::string escape_string(const std::string& s) const {
echo         std::string result;
echo         for (char c : s) {
echo             switch (c) {
echo                 case '"':  result += "\\\""; break;
echo                 case '\\': result += "\\\\"; break;
echo                 case '\b': result += "\\b"; break;
echo                 case '\f': result += "\\f"; break;
echo                 case '\n': result += "\\n"; break;
echo                 case '\r': result += "\\r"; break;
echo                 case '\t': result += "\\t"; break;
echo                 default:   result += c; break;
echo             }
echo         }
echo         return result;
echo     }
echo     
echo private:
echo     value_t m_type = value_t::null;
echo     std::map<std::string, json> m_object;
echo     std::vector<json> m_array;
echo     std::string m_string;
echo     bool m_bool = false;
echo     int m_int = 0;
echo     double m_double = 0.0;
echo };
echo 
echo // Static functions
echo inline json array() { return json(std::vector<json>()); }
echo 
echo // Input/output operators
echo inline std::ostream& operator<<(std::ostream& os, const json& j) {
echo     os << j.dump(4);
echo     return os;
echo }
echo 
echo inline std::istream& operator>>(std::istream& is, json& j) {
echo     // Simplified - just read as string
echo     std::string str;
echo     is >> str;
echo     j = json(str);
echo     return is;
echo }
echo 
echo } // namespace nlohmann
echo 
echo #endif // NLOHMANN_JSON_HPP
) > third_party\json.hpp

echo ✓ Created minimal json.hpp for testing
echo ⚠ Note: This is a minimal implementation
echo    For full features, download from:
echo    https://github.com/nlohmann/json

:end
echo.
echo [3] Testing JSON library...
echo Creating simple test...
(
echo #include <iostream>
echo #include "third_party/json.hpp"
echo using json = nlohmann::json;
echo.
echo int main() {
echo     // Create a JSON object
echo     json j;
echo     j["name"] = "Student System";
echo     j["version"] = "1.0";
echo     j["students"] = 0;
echo     j["teachers"] = 0;
echo     
echo     // Add an array
echo     j["features"] = json::array();
echo     j["features"].push_back("JSON Storage");
echo     j["features"].push_back("Data Backup");
echo     j["features"].push_back("Easy Migration");
echo     
echo     // Print JSON
echo     std::cout << "Test JSON Output:" << std::endl;
echo     std::cout << "==================" << std::endl;
echo     std::cout << j.dump(4) << std::endl;
echo     
echo     // Save to file
echo     std::ofstream file("test_json_output.json");
echo     file << j.dump(4);
echo     file.close();
echo     
echo     std::cout << "\\n✓ JSON saved to test_json_output.json" << std::endl;
echo     
echo     // Load from file
echo     std::ifstream infile("test_json_output.json");
echo     json j2;
echo     infile >> j2;
echo     infile.close();
echo     
echo     std::cout << "\\nLoaded data:" << std::endl;
echo     std::cout << "Name: " << j2.value("name", "Unknown") << std::endl;
echo     std::cout << "Version: " << j2.value("version", "0.0") << std::endl;
echo     
echo     return 0;
echo }
) > test_json_lib.cpp

echo ✓ Test program created

echo.
echo [4] Compiling and running test...
g++ test_json_lib.cpp -std=c++11 -o test_json_lib.exe 2>nul

if exist test_json_lib.exe (
    echo ✓ Compiled successfully
    echo.
    echo Running test...
    echo ================
    test_json_lib.exe
    echo ================
    echo.
    if exist test_json_output.json (
        echo Generated JSON file:
        type test_json_output.json
    )
) else (
    echo ❌ Compilation failed
    echo Check the minimal json.hpp implementation
)

echo.
echo ========================================
echo    JSON Library Setup Complete
echo ========================================
echo.
echo Next steps:
echo 1. If test worked, proceed with JSON DataManager
echo 2. If not, manually download json.hpp from:
echo    https://github.com/nlohmann/json
echo    and place in third_party/json.hpp
echo.
pause