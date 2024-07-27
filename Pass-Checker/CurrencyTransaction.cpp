#include "CurrencyTransaction.h"
#include <fstream>
#include <iostream>
#include <iomanip>

bool CurrencyTransaction::LogTransaction(const std::string& user_email, const std::string& action, const std::string& currency, double amount, const std::string& file_path) {
    std::ofstream file(file_path, std::ios_base::app);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << file_path << " for writing." << std::endl;
        return false;
    }

    file << user_email << ',' << action << ',' << currency << ',' << std::fixed << std::setprecision(2) << amount << std::endl;

    if (file.fail()) {
        std::cerr << "Error: Failed to write to file " << file_path << "." << std::endl;
        file.close();
        return false;
    }

    file.close();
    if (file.fail()) {
        std::cerr << "Error: Failed to close file " << file_path << "." << std::endl;
        return false;
    }

    return true;
}

bool CurrencyTransaction::BuyCurrency(User& user, const std::string& currency, double amount, const std::string& transaction_file) {
    user.updateBalance(currency, amount, true);
    if (User::saveUser(user, "users.csv")) {
        return LogTransaction(user.getEmail(), "BUY", currency, amount, transaction_file);
    }
    return false;
}

bool CurrencyTransaction::SellCurrency(User& user, const std::string& currency, double amount, const std::string& transaction_file) {
    if (user.getBalance(currency) >= amount) {
        user.updateBalance(currency, amount, false);
        if (User::saveUser(user, "users.csv")) {
            return LogTransaction(user.getEmail(), "SELL", currency, amount, transaction_file);
        }
    }
    else {
        std::cerr << "Insufficient balance to sell " << amount << " " << currency << std::endl;
    }
    return false;
}
