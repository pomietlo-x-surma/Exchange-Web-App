#include <cstdio>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>
#include <iostream>
#include <unordered_map>
#include "money_converter.h"
#include <utility> // For std::pair

//std::unordered_map<std::string, std::string> waluty = {
//    {"zloty", "zl"},
//    {"dollar" , "$"},
//    {"euro" , "€"},
//    {"pound" , "£"},
//    {"hryvna","₴"},
//    {"dinar","DT"}
//};


// Function to execute a command and capture its output
std::string exec(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&_pclose)> pipe(_popen(cmd, "r"), _pclose);
    if (!pipe) {
        throw std::runtime_error("_popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

// Function to get currency input from the user
std::pair<std::string, std::string> currency_input() {
    std::string currency1, currency2;
    std::cout << "Enter first currency: ";
    std::cin >> currency1;
    std::cout << "Enter second currency: ";
    std::cin >> currency2;
    return { currency1, currency2 };
}

// Function to compare currencies using the MoneyExchange executable
std::string currency_comparison(const std::string& currency1, const std::string& currency2) {
    std::string command = "MoneyExchange.exe " + currency1 + " " + currency2;
    return exec(command.c_str());
}
//do poprawki i sprawdzenia
int main() {
    auto currencies = currency_input();
    std::string currency1 = currencies.first;
    std::string currency2 = currencies.second;
    std::string result = currency_comparison(currency1, currency2);
    std::cout << result << std::endl;
    return 0;
}