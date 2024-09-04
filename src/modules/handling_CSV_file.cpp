#include <sstream>
#include <fstream>
#include <string>
#include <iostream>
#include "handling_CSV_file.hpp"
#include "money_converter.hpp"
#include <vector>
#include <array>
#include <thread>
#include <sqlite3.h>


bool is_file_empty(const std::string& file_path) {
	std::ifstream infile(file_path, std::ios::ate | std::ios::binary);
	return infile.tellg() == 0;
}

//This function generates "currencies.csv" and writes starting currencies e.g. PLN USD, 3.9 [base64]
void Currency_gen(){
	std::cout << "generating...\n";
	std::ofstream outfile(path_to_currencies_csv, std::ios_base::app);
	std::array<std::string, 3> currencies = {"USD", "EUR", "PLN"};
	for (const auto& first : currencies)
	{
		for (const auto& second : currencies)
		{
			if (first != second)
			{
				std::string c1 = currency_comparison(first, second);
				std::string c2 = currency_comparison(first, second, true);
				outfile << first << " " << second << ',' << c1 + " " + c2 << '\n';
			}
		}
	}
	outfile.close();
	std::cout << "Done generating currencies!\n";
}


//This function updates every row without creating new file every 10s (using a thread)
void Currency_update()
{
	while (true)
	{
		if (is_file_empty(path_to_currencies_csv)) {
			Currency_gen();
		}

		bool found = false;
		std::ifstream infile(path_to_currencies_csv);
		std::vector<std::string> lines;
		std::string line;
		std::array<std::string, 3> currencies = { "dollar", "euro", "zloty" };
		for (const auto& first : currencies)
		{
			for (const auto& second : currencies)
			{
				std::this_thread::sleep_for(std::chrono::seconds(10));
				if (first != second)
				{
					while (std::getline(infile, line))
					{
						// Czytanie pliku
						std::stringstream ss(line);
						std::string line_first, line_second;
						ss >> line_first >> line_second;
						if (line_first == first && line_second == second)
						{
							// Aktualizacja danych walut
							std::string c1 = currency_comparison(first, second);
							std::string c2 = currency_comparison(first, second, true);
							std::string result = first + " " + second + c1 + " " + c2 + '\n';
							lines.push_back(result);
							found = true;
						}
						else
						{
							lines.push_back(line);
						}
					}
				}
			}
		}
		infile.close();

		// Zapisywanie zaktualizowanych danych do pliku
		std::ofstream outfile(path_to_currencies_csv, std::ios_base::trunc);
		for (const auto& updated_line : lines)
		{
			outfile << updated_line << '\n';
		}
		outfile.close();
	}
}


//Writing email, login and password to a new-created user
void WriteLogsToFile_Passes(const std::string& email, const std::string& login, const std::string& password,
                            const std::string& file_path)
{
	sqlite3* db;
	sqlite3_stmt* stmt;

	int rc = sqlite3_open(path_to_database_db, &db);

	const char* sql_insert = "INSERT INTO user_auth (EMAIL, LOGIN, PASSWORD) VALUES (?, ?, ?);";
	rc = sqlite3_prepare_v2(db, sql_insert, -1, &stmt, 0);

	sqlite3_bind_text(stmt, 1, email.c_str(), -1, SQLITE_STATIC);
	sqlite3_bind_text(stmt, 2, login.c_str(), -1, SQLITE_STATIC);
	sqlite3_bind_text(stmt, 3, password.c_str(), -1, SQLITE_STATIC);

	rc = sqlite3_step(stmt);

	sqlite3_finalize(stmt);
	sqlite3_close(db);

	std::ofstream file(file_path, std::ios_base::app);
	file << email << ' ' << login << ' ' << password << '\n';
	file.close();

}

//writing balance of a new user or updating its balance
void WriteLogsToFile_Currencies(const std::string& login, const std::string& dolar,
                                const std::string& euro, const std::string& zloty, const std::string& file_path,
                                bool reg)
{
	sqlite3* db;
	sqlite3_stmt* stmt;
	int rc = sqlite3_open(path_to_database_db, &db);

	std::string new_entry = login + ',' + dolar + ' ' + euro + ' ' + zloty + '\n';
	if (reg)
	{
		const char* sql_insert = "INSERT INTO user_balance (LOGIN, \"USD\", \"EUR\", \"PLN\") VALUES (?, ?, ?, ?);";
		rc = sqlite3_prepare_v2(db, sql_insert, -1, &stmt, 0);
		sqlite3_bind_text(stmt, 1, login.c_str(), -1, SQLITE_STATIC);
		sqlite3_bind_text(stmt, 2, dolar.c_str(), -1, SQLITE_STATIC);
		sqlite3_bind_text(stmt, 3, euro.c_str(), -1, SQLITE_STATIC);
		sqlite3_bind_text(stmt, 4, zloty.c_str(), -1, SQLITE_STATIC);
		rc = sqlite3_step(stmt);
		sqlite3_finalize(stmt);
		if (rc != SQLITE_DONE) {
			std::cerr << "Error executing SQL statement: " << sqlite3_errmsg(db) << std::endl;
		}
		std::ofstream file(file_path, std::ios_base::app);
		file << new_entry;
		file.close();
	}
	else
	{
		const char* sql_update = R"(
            UPDATE user_balance 
            SET USD = ?, EUR = ?, PLN = ? 
            WHERE LOGIN = ?;
        )";

		rc = sqlite3_prepare_v2(db, sql_update, -1, &stmt, 0);
		if (rc != SQLITE_OK) {
			std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
			sqlite3_close(db);
			return;
		}

		sqlite3_bind_text(stmt, 1, dolar.c_str(), -1, SQLITE_STATIC);
		sqlite3_bind_text(stmt, 2, euro.c_str(), -1, SQLITE_STATIC);
		sqlite3_bind_text(stmt, 3, zloty.c_str(), -1, SQLITE_STATIC);
		sqlite3_bind_text(stmt, 4, login.c_str(), -1, SQLITE_STATIC);

		rc = sqlite3_step(stmt);
		if (rc != SQLITE_DONE) {
			std::cerr << "Error executing SQL update statement: " << sqlite3_errmsg(db) << std::endl;
		}

		sqlite3_finalize(stmt);
	}
	sqlite3_close(db);
}


std::string ReadLogs(const std::string& login, const std::string& file_path)
{
	std::ifstream infile(file_path);
	std::string line, log;

	while (std::getline(infile, line))
	{
		std::stringstream ss(line);
		std::string login_infile;
		std::getline(ss, login_infile, ',');
		std::getline(ss, log);
		if (login_infile == login)
		{
			std::getline(ss, log);
			return log;
		}
	}

	return "";
}


std::string correct_password_check(const std::string& input_email, const std::string& input_pass,
                                   const std::string& file_path)
{
	;
	std::ifstream file(file_path);
	std::string line;
	while (std::getline(file, line))
	{
		std::stringstream ss(line);
		std::string stored_email, stored_login, stored_pass;
		ss >> stored_email >> stored_login >> stored_pass;
		if ((stored_email == input_email) && (stored_pass == input_pass))
		{
			file.close();
			return stored_login;
		}
	}
	file.close();
	return "";
}

//checking if a user already exists
bool check_login_email_existence(const std::string& email, const std::string& login, const std::string& file_path)
{
	std::string line, stored_email, stored_login, stored_pass;
	std::ifstream file(file_path);
	while (std::getline(file, line))
	{
		std::stringstream ss(line);
		ss >> stored_email >> stored_login >> stored_pass;
		if (stored_login == login || stored_email == email)
		{
			return true;
		}
	}
	return false;
}
