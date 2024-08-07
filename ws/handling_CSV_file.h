#pragma once

#include <iostream>

bool WriteLogsToFile(const std::string& email, const std::string& login, const std::string& password, const std::string& file_path = "Dane.csv");
bool correct_password_check(const std::string& input_email, const std::string& input_pass);
//bool EnsureFileExists(const std::string& file_path);
bool check_login_email_existence(const std::string email, const std::string& login);
bool WriteUser(const std::string& email, const std::string& login, const std::string& password,
	const std::string& euro, const std::string& euro_count, const std::string& dolar, const std::string& dolar_count,
	const std::string& zloty, const std::string& zloty_count, const std::string& file_path);
