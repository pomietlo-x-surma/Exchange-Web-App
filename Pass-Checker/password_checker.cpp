#include "password_checker.h"
#include <regex>

using std::cout; using std::endl;

bool pass_check(std::string& password) {
    std::regex wzorzec_nalfa("[^a-zA-Z0-9\\s]"); // znak specjalny
    std::regex wzorzec_liczba("[0-9]");         // cyfra
    std::regex wzorzec_AZ("[A-Z]");             // du¿a litera
    std::regex wzorzec_az("[a-z]");             // ma³a litera
    std::regex wzorzec_rozmiar(".{8,50}");



    if (std::regex_search(password, wzorzec_nalfa) &&
        std::regex_search(password, wzorzec_liczba) &&
        std::regex_search(password, wzorzec_AZ) &&
        std::regex_search(password, wzorzec_az) &&
        std::regex_search(password, wzorzec_rozmiar)) {
        std::cout << "Haslo jest poprawne!" << std::endl;
        return true;
    }
    if (!std::regex_search(password, wzorzec_nalfa)) {
        std::cout << "Haslo musi zawierac przynajmniej jeden znak specjalny (np. !,@,#,$,%,^)!" << std::endl;
    }
    if (!std::regex_search(password, wzorzec_liczba)) {
        std::cout << "Haslo musi zawierac przynajmniej jedna liczbe!" << std::endl;
    }
    if (!std::regex_search(password, wzorzec_AZ)) {
        std::cout << "Haslo musi zawierac przynajmniej jedna wielka litere!" << std::endl;
    }
    if (!std::regex_search(password, wzorzec_az)) {
        std::cout << "Haslo musi zawierac przynajmniej jedna mala litere!" << std::endl;
    }
    if (!std::regex_search(password, wzorzec_rozmiar)) {
        if (password.length() < 8) {
            std::cout << "Haslo musi miec dlugosc przynajmniej 8 znakow!" << std::endl;
        }
        else {
            std::cout << "Zbyt dlugie haslo!" << std::endl;
        }

    }
    return false;
}

bool email_check(std::string email) {
    std::regex email_regex("([0-9a-zA-Z]+@[0-9a-z]+\\.[a-z]{2})");
    if (std::regex_search(email, email_regex)) {
        return true;
    }
    std::cout << "Bledny adres E-mail!\n";
    return false;
	
} 