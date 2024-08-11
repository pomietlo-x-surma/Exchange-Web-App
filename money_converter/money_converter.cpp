#include <cstdio>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>
#include <iostream>
#include <unordered_map>
//#include "money_converter.h"
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

// Uruchomienie programu: Ctrl + F5 lub menu Debugowanie > Uruchom bez debugowania
// Debugowanie programu: F5 lub menu Debugowanie > Rozpocznij debugowanie

// Porady dotyczące rozpoczynania pracy:
//   1. Użyj okna Eksploratora rozwiązań, aby dodać pliki i zarządzać nimi
//   2. Użyj okna programu Team Explorer, aby nawiązać połączenie z kontrolą źródła
//   3. Użyj okna Dane wyjściowe, aby sprawdzić dane wyjściowe kompilacji i inne komunikaty
//   4. Użyj okna Lista błędów, aby zobaczyć błędy
//   5. Wybierz pozycję Projekt > Dodaj nowy element, aby utworzyć nowe pliki kodu, lub wybierz pozycję Projekt > Dodaj istniejący element, aby dodać istniejące pliku kodu do projektu
//   6. Aby w przyszłości ponownie otworzyć ten projekt, przejdź do pozycji Plik > Otwórz > Projekt i wybierz plik sln
