#pragma once

#include <iostream>

void WriteLogsToFile(const std::string& file_path, const std::string& email, const std::string& login, const std::string& password = "",
	const std::string& euro = "", const std::string& dolar = "", const std::string& zloty = "");
bool correct_password_check(const std::string& input_email, const std::string& input_pass);
bool check_login_email_existence(const std::string email, const std::string& login);
