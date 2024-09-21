#include <sstream>
#include <fstream>
#include <string>
#include <iostream>
#include "handling_db.hpp"
#include "money_converter.hpp"
#include <array>
#include <thread>
#include "sqlite3.h"


bool is_file_empty(const std::string& path){
	std::ifstream file(path, std::ios::binary | std::ios::ate);
	return file.tellg() == 0;

}

//This function generates "currencies.csv" and writes starting currencies e.g. PLN USD, 3.9 [base64]
bool database_preparing(const std::string& sql_query, sqlite3** db, sqlite3_stmt** stmt) {
	int rc = sqlite3_open(path_to_database_db, db);
	if (rc != SQLITE_OK) {
		std::cerr << "Cannot open database: " << sqlite3_errmsg(*db) << '\n';
		return false;
	}
	rc = sqlite3_prepare_v2(*db, sql_query.c_str(), -1, stmt, nullptr);
	if (rc != SQLITE_OK) {
		std::cerr << "sqlite3 error: " << sqlite3_errmsg(*db) << '\n';
		sqlite3_close(*db);
		return false;
	}
	return true;
}

[[noreturn]] void currency_generation() {
	
	std::array<std::string, 3> currencies = { "USD", "EUR", "PLN" };
	while (true) {
		std::this_thread::sleep_for(std::chrono::seconds(10));
		for (const auto& first : currencies) {
			for (const auto& second : currencies) {
				if (first != second) {
					std::string c1 = currency_comparison(first, second);
					std::string c2 = currency_comparison(first, second, true);
					std::string combinedValue = c1 + " " + c2;

					std::string currKey = first + " " + second;

					std::string insertOrReplaceSQL = "INSERT OR REPLACE INTO currencies (curr, value) VALUES (?, ?);";

					sqlite3* db = nullptr;
					sqlite3_stmt* stmt = nullptr;

					if (!database_preparing(insertOrReplaceSQL, &db, &stmt)) {
						std::cerr << "Database preparation failed for query: " << insertOrReplaceSQL << std::endl;
						continue;
					}

					sqlite3_bind_text(stmt, 1, currKey.c_str(), -1, SQLITE_TRANSIENT);
					sqlite3_bind_text(stmt, 2, combinedValue.c_str(), -1, SQLITE_TRANSIENT);

					int rc = sqlite3_step(stmt);
					if (rc != SQLITE_DONE) {
						std::cerr << "Error executing query for " << currKey << ": " << sqlite3_errmsg(db) << std::endl;
					}

					sqlite3_finalize(stmt);
					sqlite3_close(db);
				}
			}
		}
	}
}





//Writing email, login and password to a new-created user
void write_logs_to_file_user_auth(const std::string& email, const std::string& login, const std::string& password)
{
	sqlite3* db;
	sqlite3_stmt* stmt;

	int rc = sqlite3_open(path_to_database_db, &db);

	const auto sql_insert = "INSERT INTO user_auth (EMAIL, LOGIN, PASSWORD) VALUES (?, ?, ?);";
	rc = sqlite3_prepare_v2(db, sql_insert, -1, &stmt, 0);

	sqlite3_bind_text(stmt, 1, email.c_str(), -1, SQLITE_STATIC);
	sqlite3_bind_text(stmt, 2, login.c_str(), -1, SQLITE_STATIC);
	sqlite3_bind_text(stmt, 3, password.c_str(), -1, SQLITE_STATIC);

	rc = sqlite3_step(stmt);
	sqlite3_finalize(stmt);
	sqlite3_close(db);
}
void appending_user_balance(const std::string& login, const std::string& dollar, const std::string& euro, const std::string& zloty){
	sqlite3* db = nullptr;
	sqlite3_stmt* stmt = nullptr;

	if(!database_preparing("INSERT INTO user_balance (LOGIN, USD, EUR, PLN) VALUES (?,?,?,?)", &db, &stmt)) {
		return;
	}
	sqlite3_bind_text(stmt, 1, login.c_str(), -1, SQLITE_STATIC);
	sqlite3_bind_text(stmt, 2, dollar.c_str(), -1, SQLITE_STATIC);
	sqlite3_bind_text(stmt, 3, euro.c_str(), -1, SQLITE_STATIC);
	sqlite3_bind_text(stmt, 4, zloty.c_str(), -1, SQLITE_STATIC);

	int rc = sqlite3_step(stmt);
	if (rc != SQLITE_DONE) {
		std::cerr << "Błąd przy wstawianiu danych: " << sqlite3_errmsg(db) << '\n';
	}

	sqlite3_finalize(stmt);
	sqlite3_close(db);
}



//writing balance of a new user or updating its balance
void updating_user_balance(const std::string& login, const std::string& dollar, const std::string& euro, const std::string& zloty){
	sqlite3* db = nullptr;
	sqlite3_stmt* stmt=nullptr;

	if (!database_preparing("UPDATE user_balance SET USD = ? , EUR = ? , PLN = ? WHERE LOGIN = ? ;",&db, &stmt)) {
		std::cout << "error\n";
	}
	else {
		sqlite3_bind_text(stmt, 1, dollar.c_str(), -1, SQLITE_STATIC);
		sqlite3_bind_text(stmt, 2, euro.c_str(), -1, SQLITE_STATIC);
		sqlite3_bind_text(stmt, 3, zloty.c_str(), -1, SQLITE_STATIC);
		sqlite3_bind_text(stmt, 4, login.c_str(), -1, SQLITE_STATIC);
	}
	int rc = sqlite3_step(stmt);
	if (rc != SQLITE_DONE) {
		std::cerr << "sqlite error:  " << sqlite3_errmsg(db) << '\n';
	}
	sqlite3_finalize(stmt);
	sqlite3_close(db);
}

std::string read_logs_currencies(const std::string& currency) {
	sqlite3* db = nullptr;
	sqlite3_stmt* stmt = nullptr;
	std::string result = "";

	std::string selectSQL = "SELECT value FROM currencies WHERE curr = ?;";

	if (!database_preparing(selectSQL, &db, &stmt)) {
		std::cerr << "Failed to prepare the SQL statement.\n";
		return "";
	}

	sqlite3_bind_text(stmt, 1, currency.c_str(), -1, SQLITE_TRANSIENT);

	int rc = sqlite3_step(stmt);
	if (rc == SQLITE_ROW) {
		result = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)); // Read the first column (value)
	}
	else if (rc != SQLITE_DONE) {
		std::cerr << "Error executing query: " << sqlite3_errmsg(db) << std::endl;
	}

	sqlite3_finalize(stmt);
	sqlite3_close(db);

	return result;
}

std::string read_logs_user_balance(const std::string& logs)
{
	sqlite3* db = nullptr;
	sqlite3_stmt* stmt = nullptr;
	std::string result;

	std::string sql_query = "SELECT * FROM user_balance WHERE LOGIN = ?;";

	if (!database_preparing(sql_query, &db, &stmt)) {
		return "error";
	}

	sqlite3_bind_text(stmt, 1, logs.c_str(), -1, SQLITE_STATIC);

	int rc = sqlite3_step(stmt);
	if (rc == SQLITE_ROW) {
		std::string login = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
		double usd = sqlite3_column_double(stmt, 1);
		double eur = sqlite3_column_double(stmt, 2);
		double pln = sqlite3_column_double(stmt, 3);
		result = std::to_string(usd) + " "+ std::to_string(eur) + " "+ std::to_string(pln);
		std::cout << result << '\n';
	}
	else if (rc == SQLITE_DONE) {
		result = "No matching records found";
	}
	else {
		result = "Error occurred";
	}

	sqlite3_finalize(stmt);
	sqlite3_close(db);

	return result;
}



std::string correct_password_check(const std::string& input_email, const std::string& input_pass)
{
	sqlite3* db = nullptr;
	sqlite3_stmt* stmt = nullptr;
	std::string result;

	std::string sql_query = "SELECT * FROM user_auth WHERE EMAIL = ? AND PASSWORD = ?;";

	if (!database_preparing(sql_query, &db, &stmt)) {
		return "error\n";
	}
		sqlite3_bind_text(stmt, 1, input_email.c_str(), -1, SQLITE_STATIC);
		sqlite3_bind_text(stmt, 2, input_pass.c_str(), -1, SQLITE_STATIC);
		int rc = sqlite3_step(stmt);
		if (rc == SQLITE_ROW) {
			const unsigned char* login = sqlite3_column_text(stmt, 1);
			result = std::string(reinterpret_cast<const char*>(login));
		}
		else {
			result = "";
		}
	sqlite3_finalize(stmt);
	sqlite3_close(db);
	return result;
}

//checking if a user already exists
bool check_login_email_existence(const std::string& email, const std::string& login)
{
	sqlite3* db = nullptr;
	sqlite3_stmt* stmt = nullptr;
	bool exists = false;
	if (!database_preparing("SELECT * FROM user_auth WHERE EMAIL = ? OR LOGIN = ? LIMIT 1;", &db, &stmt)) {
		return false;
	}

	sqlite3_bind_text(stmt, 1, email.c_str(), -1, SQLITE_STATIC);
	sqlite3_bind_text(stmt, 2, login.c_str(), -1, SQLITE_STATIC);

	if (sqlite3_step(stmt) == SQLITE_ROW) {
		exists = true;
	}

	sqlite3_finalize(stmt);
	sqlite3_close(db);
	return exists;
}
