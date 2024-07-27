#include <iostream>

bool WriteLogsToFile(const std::string& file_path, const std::string& email, const std::string& login, const std::string& password);
bool correct_password_check(const std::string& file_path, const std::string& email, const std::string& input_login, const std::string& input_pass);
bool EnsureFileExists(const std::string& file_path);