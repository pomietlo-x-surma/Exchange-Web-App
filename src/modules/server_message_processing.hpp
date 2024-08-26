#pragma once
#include <iostream>

std::string to_string_with_precision(const long double& value, const char& precision = 2);
std::string process_message(const std::string& received_message);
std::string check_register(const std::string& email, const std::string& login, const std::string& pass, const std::string& pass_rep);
std::string check_logging(const std::string& email, const std::string& pass);
std::string login_user(const std::string& message);
std::string register_user(const std::string& message);
std::string exchange_rate(const std::string& message);
std::string account_balance(const std::string& message);
std::string exchange(const std::string& message);
std::string receive_text(const char& id, const std::string& message);
