#include <sstream>
#include <fstream>
#include <string>
#include <iostream>
#include "handling_CSV_file.h"
#include <vector>

void WriteLogsToFile_Passes(const std::string& email, const std::string& login, const std::string& password, const std::string& file_path) {

	std::ofstream file(file_path, std::ios_base::app);
	if (!file.is_open()) {
		std::cerr << "Error: Could not open file " << file_path << " for writing." << std::endl;
	}
	file << email << ',' << login << ',' << password << '\n';
	file.close();
}



void WriteLogsToFile_Currencies(const std::string& login, const std::string& euro,
	const std::string& dolar, const std::string& zloty, const std::string& file_path, bool reg) {

	std::string w = login + ',' + euro + ',' + dolar + ',' + zloty + '\n';

	if (reg) {
		std::ofstream file(file_path, std::ios_base::app);
		file << w;
		file.close();
	}
	else {
		std::ifstream infile(file_path);
		std::vector<std::string> lines;
		std::string line;

		while (std::getline(infile, line)) {
			std::stringstream ss(line);
			std::string login_infile;
			std::getline(ss, login_infile, ',');

			if (login_infile == login) {
				lines.push_back(w);
			}
		}

		infile.close();

	}
}
std::string ReadLogs(const std::string& login, const std::string& file_path) {
	std::ifstream infile(file_path);
	std::vector<std::string> lines;
	std::string line;

	while (std::getline(infile, line)) {
		std::stringstream ss(line);
		std::string login_infile;
		std::getline(ss, login_infile, ',');
		if (login_infile == login) {
			return line;
		}
	}
}



bool correct_password_check(const std::string& input_email, const std::string& input_pass) {
	const std::string& file_path = "Dane.csv";

	std::ifstream file(file_path);
	if (!file.is_open()) {
		std::cerr << "Error: Could not open file " << file_path << " for reading." << std::endl;
		return false;
	}

	std::string line;
	while (std::getline(file, line)) {
		std::stringstream ss(line);
		std::string stored_email, stored_login, stored_pass;

		std::getline(ss, stored_email, ',');
		std::getline(ss, stored_pass, ',');
		std::getline(ss, stored_login, ',');
		//std::cout << stored_email << " " << stored_login << " " << stored_pass << "////" << input_email << " " << input_pass << "s" << std::endl;
		if ((stored_email == input_email) && (stored_pass == input_pass)) {
			return true;
		}
		else if ((stored_email == input_email) && (stored_pass != input_pass)) {
			std::cout << "Podany E-mail lub hasło jest niepoprawne" << std::endl;
			file.close();
			return false;
		}
	}
	std::cout << "Uzytkownik o podanym E-mailu nie istnieje!" << std::endl;

	file.close();
	return false;
}

bool check_login_email_existence(const std::string email, const std::string& login) {
	const std::string& file_path = "Dane.csv";
	std::string line;
	std::stringstream ss(line);
	std::ifstream file(file_path);
	std::string stored_email, stored_login, stored_pass;
	while (std::getline(file, line)) {
		std::stringstream ss(line);
		std::string stored_email, stored_login, stored_pass;

		std::getline(ss, stored_email, ',');
		std::getline(ss, stored_login, ',');
		std::getline(ss, stored_pass, ',');
		if (stored_login == login || stored_email == email) {
			return true;
		}

	}
	return false;
}
