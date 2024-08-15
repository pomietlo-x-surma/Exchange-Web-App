#include "password_checker.h"
#include <regex>

using std::cout; using std::endl;

std::string pass_check(const std::string& password) {
    std::regex wzorzec_nalfa("[^a-zA-Z0-9\\s]"); // znak specjalny
    std::regex wzorzec_liczba("[0-9]");         // cyfra
    std::regex wzorzec_AZ("[A-Z]");             // duża litera
    std::regex wzorzec_az("[a-z]");             // mała litera
    std::regex wzorzec_rozmiar(".{8,50}");


    std::string nap = "";

    if (password.find('\\0') != std::string::npos) {
        return "Haslo nie moze zawierac znaku '\\0'!";
    }

    if (std::regex_search(password, wzorzec_nalfa) &&
        std::regex_search(password, wzorzec_liczba) &&
        std::regex_search(password, wzorzec_AZ) &&
        std::regex_search(password, wzorzec_az) &&
        std::regex_search(password, wzorzec_rozmiar)) {
        return nap;
    }
    nap = "Haslo musi zawierac: ";
    if (!std::regex_search(password, wzorzec_nalfa)) {
        nap = nap + "przynajmniej jeden znak specjalny (np. !,@,#,$,%,^)!\n";
    }
    if (!std::regex_search(password, wzorzec_liczba)) {
        nap = nap + "przynajmniej jedna liczbe!\n";
    }
    if (!std::regex_search(password, wzorzec_AZ)) {
        nap = nap + "przynajmniej\njedna wielka litere!\n";
    }
    if (!std::regex_search(password, wzorzec_az)) {
        nap = nap + "przynajmniej\njedna mala litere!\n";
    }
    if (!std::regex_search(password, wzorzec_rozmiar)) {
        if (password.length() < 8) {
            nap = nap + "Miec dlugosc przynajmniej 8 znakow!";
        }
        else {
            nap = nap + "Zbyt dlugie haslo!\n";
        }

    }
    return nap;
}

bool email_check(const std::string& email) {
    std::regex email_regex("[0-9a-zA-Z]+@[0-9a-z]+\\.[a-z]{2,3}");
    if (std::regex_match(email, email_regex)) {
        return true;
    }
    if (email.find('\\0') != std::string::npos) {
        std::cout << "Bledny adres E-mail!\nEmail nie moze zawierac znaku null (\\0)!\n";
        return false;
    }
    std::cout << "Bledny adres E-mail!\nEmail musi musi byc w postaci np. example123@gmail.pl!\n";
    return false;

}

bool login_check(const std::string& user) {
    std::regex user_regex("^[0-9a-zA-Z]{4,30}$");
    if (std::regex_match(user, user_regex)) {
        return true;
    }
    if (user.find('\\0') != std::string::npos) {
        std::cout << "Bledna nazwa uzytkownika!\nNazwa uzytkownika nie moze zawierac znaku null (\\0)!\n";
        return false;
    }

    std::cout << "Bledna nazwa uzytkownika!\nNazwa uzytkownika nie moze zawierac znakow specjalnych\ni miec dlugosc od 4 do 30 znakow!\n";
    return false;

}
