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

int main(int argc, char* argv[]) {
    std::string currency1 = "zloty";
    std::string currency2 = "euro";

    std::string command = "MoneyExchange.exe " + currency1 + " " + currency2;
    std::string result = exec(command.c_str());

    std::cout << result << '\n';
    return 0;
}
