#ifndef CURRENCY_TRANSACTION_H
#define CURRENCY_TRANSACTION_H

#include <string>
#include "User.h"

class CurrencyTransaction {
public:
    static bool BuyCurrency(User& user, const std::string& currency, double amount, const std::string& transaction_file);
    static bool SellCurrency(User& user, const std::string& currency, double amount, const std::string& transaction_file);
    static bool LogTransaction(const std::string& user_email, const std::string& action, const std::string& currency, double amount, const std::string& file_path);
};

#endif // CURRENCY_TRANSACTION_H
