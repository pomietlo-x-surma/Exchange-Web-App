#include <iostream>
#include <string>
#include "password_checker.h"
#include "handling_CSV_file.h"


int main() {
    std::string napis = "^8A2aaaaaaaaa";
    std::cout << pass_check(napis) << std::endl;

        // Example 
    if (WriteLogsToFile("dataset.csv", "user@gmail.com", "user", "password")) {
        std::cout << "Log entry written successfully." << std::endl;
    }
    else {
        std::cout << "Failed to write log entry." << std::endl;
    }

    return 0;
    return 0;
}