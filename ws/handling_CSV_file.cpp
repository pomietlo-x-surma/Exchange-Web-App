#include <sstream>
#include <fstream>
#include <string>
#include <iostream>
#include "handling_CSV_file.h"


bool WriteLogsToFile(const std::string& email, const std::string& login, const std::string& password, const std::string& file_path) {

	std::ofstream file(file_path, std::ios_base::app);
	if (!file.is_open()) {
		std::cerr << "Error: Could not open file " << file_path << " for writing." << std::endl;
		return false;
	}

	file << email << ',' << login << ',' << password << std::endl;

	if (file.fail()) { //ta funckja to jest chyba nie potrzebna
		std::cerr << "Error: Failed to write to file " << file_path << "." << std::endl;
		file.close();
		return false;
	}

	file.close();
	if (file.fail()) { //ta chyba też
		std::cerr << "Error: Failed to close file " << file_path << "." << std::endl;
		return false;
	}

	return true;
}
bool WriteUser(const std::string& email, const std::string& login, const std::string& password,
			   const std::string& euro, const std::string& euro_count, const std::string& dolar, const std::string& dolar_count,
			   const std::string& zloty, const std::string& zloty_count, const std::string& file_path ) {

	std::ofstream file(file_path, std::ios_base::app);
	if (!file.is_open()) {
		std::cerr << "Error: Could not open file " << file_path << " for writing." << std::endl;
		return false;
	}

	file << email << ',' << login << ',' << password << std::endl;

	if (file.fail()) { //ta funckja to jest chyba nie potrzebna
		std::cerr << "Error: Failed to write to file " << file_path << "." << std::endl;
		file.close();
		return false;
	}

	file.close();
	if (file.fail()) { //ta chyba też
		std::cerr << "Error: Failed to close file " << file_path << "." << std::endl;
		return false;
	}

	return true;
}





//ta funkcja i ta  check_login_email_existence mają dużo części wspólnych 
//więc ja bym albo zrobił 3cią funkcję która to upraszcza albo zrobił
// jedną funkcję z połączonymi elementami
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
		}//spr czy user wprowadził poprawne dane podczas logowania
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
