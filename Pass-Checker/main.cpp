#include <iostream>
#include <string>
#include "password_checker.h"
#include "handling_CSV_file.h"
#include "User.h"
#include "CurrencyTransaction.h"
#include "money_converter.h"

int main() {
    bool mode;
    std::cout << "Je�li chcesz si� zalogowa�, wpisz 0\n";
    std::cout << "Je�li chcesz stworzy� nowe konto, wpisz 1\n";
    std::cout << "Wyb�r: ";
    std::cin >> mode;

    if (mode) {
        // Rejestracja nowego u�ytkownika
        std::string email, user, password, password_repeat;
        bool pass = false;

        std::cout << "Tworzenie nowego konta\n";

        // Email
        do {
            std::cin.clear();
            std::cin.ignore(1024, '\n');
            std::cout << "Podaj E-mail: ";
            std::cin >> email;
            pass = email_check(email);
        } while (std::cin.fail() || !pass);

        // Login
        pass = false;
        do {
            std::cin.clear();
            std::cin.ignore(1024, '\n');
            std::cout << "Podaj nazw� u�ytkownika: ";
            std::cin >> user;
            pass = user_check(user);
        } while (std::cin.fail() || !pass);

        // Has�o
        bool rep = true;
        do {
            pass = false;
            do {
                std::cin.clear();
                std::cin.ignore(1024, '\n');
                std::cout << "Podaj has�o: ";
                std::cin >> password;
                pass = pass_check(password);
            } while (std::cin.fail() || !pass);

            std::cout << "End!\n";
            pass = false;

            do {
                std::cin.clear();
                std::cin.ignore(1024, '\n');
                std::cout << "Powt�rz has�o: ";
                std::cin >> password_repeat;
                if (password_repeat == "!rep") {
                    rep = true;
                    break;
                }
                else if (password == password_repeat) {
                    pass = true;
                }
                else {
                    std::cout << "Has�a s� r�ne!\n";
                    std::cout << "Je�li chcesz poprawi� has�o, wpisz '!rep'\n";
                }
            } while (std::cin.fail() || !pass);
        } while (rep);

        // Zapisz nowego u�ytkownika do pliku
        if (WriteLogsToFile("users.csv", email, user, password)) {
            std::cout << "U�ytkownik zosta� pomy�lnie zarejestrowany." << std::endl;
        }
        else {
            std::cerr << "Nie uda�o si� zarejestrowa� u�ytkownika." << std::endl;
            return 1;
        }
    }

    // Logowanie istniej�cego u�ytkownika
    std::string email, login, password;
    std::string action, currency;
    double amount;
    std::string transaction_file = "transactions.csv";

    // Upewnij si�, �e plik z transakcjami istnieje
    if (!EnsureFileExists(transaction_file)) {
        std::cerr << "Nie uda�o si� utworzy� pliku transakcji." << std::endl;
        return 1;
    }

    std::cout << "Podaj sw�j email: ";
    std::cin >> email;
    std::cout << "Podaj sw�j login: ";
    std::cin >> login;
    std::cout << "Podaj swoje has�o: ";
    std::cin >> password;

    // Sprawd� poprawno�� logowania
    if (!correct_password_check("users.csv", email, login, password)) {
        std::cerr << "Logowanie nie powiod�o si�. Ko�czenie programu..." << std::endl;
        return 1;
    }

    User user = User::loadUser(email, login, "users.csv");

    // Wykonywanie transakcji
    std::cout << "Wpisz akcj� (BUY/SELL): ";
    std::cin >> action;
    std::cout << "Wpisz walut�: ";
    std::cin >> currency;
    std::cout << "Wpisz kwot�: ";
    std::cin >> amount;

    if (action == "BUY") {
        if (CurrencyTransaction::BuyCurrency(user, currency, amount, transaction_file)) {
            std::cout << "Waluta zosta�a pomy�lnie zakupiona!" << std::endl;
        }
        else {
            std::cerr << "Nie uda�o si� kupi� waluty." << std::endl;
        }
    }
    else if (action == "SELL") {
        if (CurrencyTransaction::SellCurrency(user, currency, amount, transaction_file)) {
            std::cout << "Waluta zosta�a pomy�lnie sprzedana!" << std::endl;
        }
        else {
            std::cerr << "Nie uda�o si� sprzeda� waluty." << std::endl;
        }
    }
    else {
        std::cerr << "Nieprawid�owa akcja." << std::endl;
    }

    return 0;
}