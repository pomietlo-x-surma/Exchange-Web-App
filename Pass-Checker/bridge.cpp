#include <cstdio>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>
#include <iostream>
#include <unordered_map>


//std::unordered_map<std::string, std::string> waluty = {
//    {"zloty", "zl"},
//    {"dollar" , "$"},
//    {"euro" , "€"},
//    {"pound" , "£"},
//    {"hryvna","₴"},
//    {"dinar","DT"}
//};


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


//function saving currencies requested by user
std::string currency_comparison(int argc, char* argv[]) {
    if (argc < 3) {
        throw std::invalid_argument("Należy podać dwie waluty do porównania.");
    }

    std::string currency1 = argv[1];
    std::string currency2 = argv[2];

    std::string command = "MoneyExchange.exe " + currency1 + " " + currency2;
    std::string result = exec(command.c_str());

    return result;
}
