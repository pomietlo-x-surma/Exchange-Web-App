#include <iostream>
#include <string>
#include "password_checker.h"
#include "handling_CSV_file.h"


int main() {
    //std::string napis = "^8A2aaaaaaaaa";
    //std::cout << pass_check(napis) << std::endl;
    bool mode = true;
    std::cout << "Jesli chcesz sie zalogowac wpisz 0\n";
    std::cout << "Jesli chcesz stworzyc nowe konto wpisz 1\n";
    std::cout << "Wybor: ";
    std::cin >> mode;
    if (mode) {
        std::string email, user, password, password_repeat;
        bool pass = false;
        std::cout << "Tworzenie nowego konta\n";
        do {
            std::cin.clear();
            std::cin.ignore(1024, '\n');
            std::cout << "Podaj E-mail: ";
            std::cin >> email;
            pass = email_check(email);
        } while (std::cin.fail() || !pass);

    }
    //if (WriteLogsToFile("dataset.csv", "user@gmail.com", "user", "password")) {
    //    std::cout << "Log entry written successfully." << std::endl;
    //}
    //else {
    //    std::cout << "Failed to write log entry." << std::endl;
    //}

    //return 0;

}