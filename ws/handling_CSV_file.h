#pragma once

#include <iostream>

//login, email, haslo -> Dane.csv
void WriteLogsToFile_Passes(const std::string& email, const std::string& login, const std::string& password, const std::string& file_path = "Dane.csv");

//info o walutach -> Users.csv
void WriteLogsToFile_Currencies(const std::string& login, const std::string& euro, const std::string& dolar, const std::string& zloty, const std::string& file_path = "Users.csv", bool reg = false);

std::string ReadLogs(const std::string& login, const std::string& file_path = "Users.csv");
bool correct_password_check(const std::string& input_email, const std::string& input_pass);
bool check_login_email_existence(const std::string& email, const std::string& login);
