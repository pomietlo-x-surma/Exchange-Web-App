#include <sstream>
#include <fstream>
#include <string>
#include <iostream>
#include "handling_CSV_file.hpp"
#include "money_converter.hpp"
#include <vector>
#include <array>
#include <unordered_map>
#include <thread>

void Currency_gen()
{
	std::ofstream outfile("currencies.csv", std::ios_base::app);
	std::array<std::string, 3> currencies = {"dollar", "euro", "zloty"};
	std::unordered_map<std::string, std::string> currencies2 = {{"dollar", "USD"}, {"euro", "EUR"}, {"zloty", "PLN"}};
	for (const auto& first : currencies)
	{
		for (const auto& second : currencies)
		{
			if (first != second)
			{
				std::string c1 = currency_comparison(first, second);
				std::string c2 = currency_comparison(first, second, true);
				outfile << currencies2[first] << " " << currencies2[second] << ',' << c1 + " " + c2 << '\n';
			}
		}
	}
	outfile.close();
}


void Currency_update()
{
	while (true)
	{
		bool found = false;
		std::ifstream infile("currencies.csv");
		std::vector<std::string> lines;
		std::string line;
		std::array<std::string, 3> currencies = {"dollar", "euro", "zloty"};
		std::unordered_map<std::string, std::string> currencies2 = {
			{"dollar", "USD"}, {"euro", "EUR"}, {"zloty", "PLN"}
		};
		for (const auto& first : currencies)
		{
			for (const auto& second : currencies)
			{
				std::cout << "currency updated!\n";
				std::this_thread::sleep_for(std::chrono::seconds(10));
				if (first != second)
				{
					while (std::getline(infile, line))
					{
						std::stringstream ss(line);
						std::string line_first, line_second;
						ss >> line_first >> line_second;

						if (line_first == first && line_second == second)
						{
							std::string c1 = currency_comparison(first, second);
							std::string c2 = currency_comparison(first, second, true);
							std::string c1_new = currencies2[c1];
							std::string c2_new = currencies2[c2];
							std::string result = first + " " + second + c1_new + " " + c2_new + '\n';
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
		std::ofstream outfile("currencies.csv", std::ios_base::trunc);
		for (const auto& updated_line : lines)
		{
			outfile << updated_line << '\n';
		}
		outfile.close();
	}
}


void WriteLogsToFile_Passes(const std::string& email, const std::string& login, const std::string& password,
                            const std::string& file_path)
{
	std::ofstream file(file_path, std::ios_base::app);
	file << email << ' ' << login << ' ' << password << '\n';
	file.close();
}


//TODO POZMIENIAC dolar na usd itp w całym pliku
void WriteLogsToFile_Currencies(const std::string& login, const std::string& dolar,
                                const std::string& euro, const std::string& zloty, const std::string& file_path,
                                bool reg)
{
	std::string new_entry = login + ',' + dolar + ' ' + euro + ' ' + zloty + '\n';
	std::cout << new_entry << '\n';
	if (reg)
	{
		std::ofstream file(file_path, std::ios_base::app);
		file << new_entry;
		file.close();
	}
	else
	{
		std::ifstream infile(file_path);
		std::vector<std::string> lines;
		std::string line;
		bool found = false;

		while (std::getline(infile, line))
		{
			std::stringstream ss(line);
			std::string login_infile;
			std::getline(ss, login_infile, ',');
			std::cout << login_infile << "Z\n";
			if (login_infile == login)
			{
				std::cout << line << "\n";
				lines.push_back(new_entry + "X");
				found = true;
			}
			else
			{
				lines.push_back(line + '\n');
			}
		}

		infile.close();

		if (found)
		{
			std::ofstream outfile(file_path, std::ios_base::trunc);
			for (const auto& updated_line : lines)
			{
				outfile << updated_line;
			}
			outfile.close();
		}
	}
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

bool check_login_email_existence(const std::string& email, const std::string& login, const std::string& file_path)
{
	;
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
