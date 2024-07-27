#include <iostream>
#include <string>
#include "password_checker.h"
#include "handling_CSV_file.h"
#include "User.h"
#include "CurrencyTransaction.h"
#include "money_converter.h"

int main() {
    bool mode;
    std::cout << "Jeœli chcesz siê zalogowaæ, wpisz 0\n";
    std::cout << "Jeœli chcesz stworzyæ nowe konto, wpisz 1\n";
    std::cout << "Wybór: ";
    std::cin >> mode;

    if (mode) {
        // Rejestracja nowego u¿ytkownika
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
            std::cout << "Podaj nazwê u¿ytkownika: ";
            std::cin >> user;
            pass = user_check(user);
        } while (std::cin.fail() || !pass);

        // Has³o
        bool rep = true;
        do {
            pass = false;
            do {
                std::cin.clear();
                std::cin.ignore(1024, '\n');
                std::cout << "Podaj has³o: ";
                std::cin >> password;
                pass = pass_check(password);
            } while (std::cin.fail() || !pass);

            std::cout << "End!\n";
            pass = false;

            do {
                std::cin.clear();
                std::cin.ignore(1024, '\n');
                std::cout << "Powtórz has³o: ";
                std::cin >> password_repeat;
                if (password_repeat == "!rep") {
                    rep = true;
                    break;
                }
                else if (password == password_repeat) {
                    pass = true;
                }
                else {
                    std::cout << "Has³a s¹ ró¿ne!\n";
                    std::cout << "Jeœli chcesz poprawiæ has³o, wpisz '!rep'\n";
                }
            } while (std::cin.fail() || !pass);
        } while (rep);

        // Zapisz nowego u¿ytkownika do pliku
        if (WriteLogsToFile("users.csv", email, user, password)) {
            std::cout << "U¿ytkownik zosta³ pomyœlnie zarejestrowany." << std::endl;
        }
        else {
            std::cerr << "Nie uda³o siê zarejestrowaæ u¿ytkownika." << std::endl;
            return 1;
        }
    }

    // Logowanie istniej¹cego u¿ytkownika
    std::string email, login, password;
    std::string action, currency;
    double amount;
    std::string transaction_file = "transactions.csv";

    // Upewnij siê, ¿e plik z transakcjami istnieje
    if (!EnsureFileExists(transaction_file)) {
        std::cerr << "Nie uda³o siê utworzyæ pliku transakcji." << std::endl;
        return 1;
    }

    std::cout << "Podaj swój email: ";
    std::cin >> email;
    std::cout << "Podaj swój login: ";
    std::cin >> login;
    std::cout << "Podaj swoje has³o: ";
    std::cin >> password;

    // SprawdŸ poprawnoœæ logowania
    if (!correct_password_check("users.csv", email, login, password)) {
        std::cerr << "Logowanie nie powiod³o siê. Koñczenie programu..." << std::endl;
        return 1;
    }

    User user = User::loadUser(email, login, "users.csv");

    // Wykonywanie transakcji
    std::cout << "Wpisz akcjê (BUY/SELL): ";
    std::cin >> action;
    std::cout << "Wpisz walutê: ";
    std::cin >> currency;
    std::cout << "Wpisz kwotê: ";
    std::cin >> amount;

    if (action == "BUY") {
        if (CurrencyTransaction::BuyCurrency(user, currency, amount, transaction_file)) {
            std::cout << "Waluta zosta³a pomyœlnie zakupiona!" << std::endl;
        }
        else {
            std::cerr << "Nie uda³o siê kupiæ waluty." << std::endl;
        }
    }
    else if (action == "SELL") {
        if (CurrencyTransaction::SellCurrency(user, currency, amount, transaction_file)) {
            std::cout << "Waluta zosta³a pomyœlnie sprzedana!" << std::endl;
        }
        else {
            std::cerr << "Nie uda³o siê sprzedaæ waluty." << std::endl;
        }
    }
    else {
        std::cerr << "Nieprawid³owa akcja." << std::endl;
    }

    return 0;
}