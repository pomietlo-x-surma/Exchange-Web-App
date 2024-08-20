#pragma once

#include <iostream>

void WriteLogsToFile_Passes(const std::string& email, const std::string& login, const std::string& password, const std::string& file_path = "Dane.csv");
void WriteLogsToFile_Currencies(const std::string& login, const std::string& dolar, const std::string& euro, const std::string& zloty, const std::string& file_path = "Users.csv", bool reg = false);
std::string ReadLogs(const std::string& login, const std::string& file_path = "Users.csv");
std::string correct_password_check(const std::string& input_email, const std::string& input_pass, const std::string& file_path = "Dane.csv");
bool check_login_email_existence(const std::string& email, const std::string& login, const std::string& file_path = "Dane.csv");
void Currency_gen();
void Currency_update();
