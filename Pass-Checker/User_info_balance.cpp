#include "User.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>

User::User(const std::string& email, const std::string& login) : email(email), login(login) {}

std::string User::getEmail() const {
    return email;
}

std::string User::getLogin() const {
    return login;
}

double User::getBalance(const std::string& currency) const {
    auto it = balances.find(currency);
    if (it != balances.end()) {
        return it->second;
    }
    return 0.0;
}

void User::updateBalance(const std::string& currency, double amount, bool is_purchase) {
    if (is_purchase) {
        balances[currency] += amount;
    }
    else {
        if (balances[currency] >= amount) {
            balances[currency] -= amount;
        }
        else {
            std::cerr << "Insufficient balance to sell " << amount << " " << currency << std::endl;
        }
    }
}

User User::loadUser(const std::string& email, const std::string& login, const std::string& file_path) {
    User user(email, login);
    std::ifstream file(file_path);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string stored_email, stored_login, currency;
            double balance;

            std::getline(ss, stored_email, ',');
            std::getline(ss, stored_login, ',');
            if (stored_email == email && stored_login == login) {
                while (std::getline(ss, currency, ',')) {
                    ss >> balance;
                    user.balances[currency] = balance;
                }
                break;
            }
        }
        file.close();
    }
    return user;
}

bool User::saveUser(const User& user, const std::string& file_path) {
    std::ifstream file(file_path);
    std::ofstream temp("temp.csv");
    bool user_found = false;

    if (file.is_open() && temp.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string stored_email, stored_login;

            std::getline(ss, stored_email, ',');
            std::getline(ss, stored_login, ',');
            if (stored_email == user.email && stored_login == user.login) {
                user_found = true;
                temp << user.email << ',' << user.login;
                for (const auto& balance : user.balances) {
                    temp << ',' << balance.first << ',' << balance.second;
                }
                temp << std::endl;
            }
            else {
                temp << line << std::endl;
            }
        }
        file.close();
        temp.close();

        if (!user_found) {
            std::ofstream temp_out("temp.csv", std::ios_base::app);
            temp_out << user.email << ',' << user.login;
            for (const auto& balance : user.balances) {
                temp_out << ',' << balance.first << ',' << balance.second;
            }
            temp_out << std::endl;
            temp_out.close();
        }

        remove(file_path.c_str());
        rename("temp.csv", file_path.c_str());
        return true;
    }

    return false;
}
