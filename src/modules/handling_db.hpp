#pragma once
#include <iostream>
constexpr auto path_to_database_db = R"(../database/database.db)";


void write_logs_to_file_user_auth(const std::string& email, const std::string& login, const std::string& password);
void updating_user_balance(const std::string& login, const std::string& dollar, const std::string& euro, const std::string& zloty);
void appending_user_balance(const std::string& login, const std::string& dollar, const std::string& euro, const std::string& zloty);
std::string read_logs_currencies(const std::string& logs);
std::string read_logs_user_balance(const std::string& logs);
std::string correct_password_check(const std::string& input_email, const std::string& input_pass);
bool check_login_email_existence(const std::string& email, const std::string& login);
void currency_generation();
void currency_update();
