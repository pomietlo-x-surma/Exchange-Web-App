#pragma once
#include <iostream>
constexpr auto path_to_user_auth_csv = R"(../database/user_auth.csv)";
constexpr auto path_to_user_balance_csv = R"(../database/user_balance.csv)";
constexpr auto path_to_currencies_csv = R"(../database/currencies.csv)";
constexpr auto path_to_database_db = R"(../database/database.db)";


void write_logs_to_file_user_auth(const std::string& email, const std::string& login, const std::string& password, const std::string& file_path = path_to_user_auth_csv);
void updating_user_balance(const std::string& login, const std::string& dollar, const std::string& euro, const std::string& zloty);
void appending_user_balance(const std::string& login, const std::string& dollar, const std::string& euro, const std::string& zloty);
std::string read_logs_currencies(const std::string& logs);
std::string read_logs_user_balance(const std::string& logs);
std::string correct_password_check(const std::string& input_email, const std::string& input_pass, const std::string& file_path = path_to_user_auth_csv);
bool check_login_email_existence(const std::string& email, const std::string& login, const std::string& file_path = path_to_user_auth_csv);
void currency_generation();
void currency_update();
