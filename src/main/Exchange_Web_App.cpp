#include <fstream>
#include <iostream>
#include <sstream>
#include "../modules/server_file.hpp"
#include <thread>
#include "../modules/handling_CSV_file.hpp"
#include <string>
#include "sqlite3.h"


int creating_auth() {
    sqlite3* db;
    char* err_msg = 0;

    int rc = sqlite3_open(path_to_database_db, &db);
    if (rc) {
        std::cerr << "Nie można otworzyć bazy danych: " << sqlite3_errmsg(db) << std::endl;
        return rc;
    }

    const char* sql_create_table = "CREATE TABLE IF NOT EXISTS user_auth ("
        "EMAIL TEXT, "
        "LOGIN TEXT, "
        "PASSWORD TEXT);";
    rc = sqlite3_exec(db, sql_create_table, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        std::cerr << "Błąd SQL: " << err_msg << std::endl;
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return rc;
    }

    std::ifstream file(path_to_user_auth_csv);
    if (!file.is_open()) {
        std::cerr << "Nie można otworzyć pliku CSV." << std::endl;
        sqlite3_close(db);
        return 1;
    }

    std::string line;
    bool first_line = true;

    while (std::getline(file, line)) {
        if (first_line) {
            first_line = false;
            continue;
        }

        std::stringstream ss(line);
        std::string email, login, password;

        std::getline(ss, email, ',');
        std::getline(ss, login, ',');
        std::getline(ss, password, ',');

        std::string sql_insert = "INSERT INTO user_auth (EMAIL, LOGIN, PASSWORD) "
            "VALUES ('" + email + "', '" + login + "', '" + password + "');";

        rc = sqlite3_exec(db, sql_insert.c_str(), 0, 0, &err_msg);
        if (rc != SQLITE_OK) {
            std::cerr << "Błąd SQL: " << err_msg << '\n';
            sqlite3_free(err_msg);
        }
    }

    // Zakończenie
    file.close();
    sqlite3_close(db);
    return 0;
}

int creating_balance() {
    sqlite3* db;
    int rc = sqlite3_open("example.db", &db);

    int rc = sqlite3_open(path_to_database_db, &db);
    if (rc) {
        std::cerr << "Nie można otworzyć bazy danych: " << sqlite3_errmsg(db) << std::endl;
        return rc;
    }

    const auto sql_create_table = "CREATE TABLE IF NOT EXISTS user_balance ("
        "LOGIN TEXT, "
        "USD REAL, "
        "EUR REAL, "
        "PLN REAL);";
    rc = sqlite3_exec(db, sql_create_table, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        std::cerr << "Błąd SQL: " << err_msg << std::endl;
        std::cout << rc << std::endl;
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return rc;
    }

    std::ifstream file(path_to_user_balance_csv);
    if (!file.is_open()) {
        std::cerr << "Nie można otworzyć pliku CSV." << std::endl;
        sqlite3_close(db);
        return 1;
    }

    std::string line;
    bool first_line = true;

    while (std::getline(file, line)) {
        if (first_line) {
            first_line = false;
            continue;
        }

        std::stringstream ss(line);
        std::string login;
        double usd, eur, pln;

        ss >> login >> usd >> eur >> pln;

        std::string sql_insert = "INSERT INTO user_balance (LOGIN, USD, EUR, PLN) "
            "VALUES ('" + login + "', " + std::to_string(usd) + ", " + std::to_string(eur) + ", " + std::to_string(pln) + ");";

        rc = sqlite3_exec(db, sql_insert.c_str(), 0, 0, &err_msg);
        if (rc != SQLITE_OK) {
            std::cerr << "Błąd SQL: " << err_msg << '\n';
            std::cout << rc << std::endl;
            sqlite3_free(err_msg);
        }
    }

    file.close();
    sqlite3_close(db);
    return 0;
}



int main() {
    //std::thread t1(currency_update); //updating currencies in currencies.csv
    server(); //turning on server
    //creating_auth(); //creating user_auth in db from csv
    //creating_balance(); //creating user_balance in db
}
