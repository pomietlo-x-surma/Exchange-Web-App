#pragma once
#include <iostream>

extern std::function<std::string(const char* cmd)> exec_func;
std::string exec(const char* cmd);
std::string currency_comparison(const std::string& currency1, const std::string& currency2, bool chart = false);
