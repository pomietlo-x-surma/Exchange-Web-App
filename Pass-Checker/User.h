#ifndef USER_H
#define USER_H

#include <string>
#include <unordered_map>

class User {
    std::string email;
    std::string login;
    std::unordered_map<std::string, double> balances;

public:
    User(const std::string& email, const std::string& login);
    std::string getEmail() const;
    std::string getLogin() const;
    double getBalance(const std::string& currency) const;
    void updateBalance(const std::string& currency, double amount, bool is_purchase);

    static User loadUser(const std::string& email, const std::string& login, const std::string& file_path);
    static bool saveUser(const User& user, const std::string& file_path);
};

#endif // USER_H
