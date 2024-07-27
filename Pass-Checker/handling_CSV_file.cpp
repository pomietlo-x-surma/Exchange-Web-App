#include <sstream>
#include <fstream>
#include <string>
#include <iostream>
#include "handling_CSV_file.h"



bool EnsureFileExists(const std::string& file_path) {
    std::ifstream file(file_path);
    if (!file) {
        // Plik nie istnieje, więc go utwórz
        std::ofstream create_file(file_path);
        if (!create_file) {
            std::cerr << "Error: Could not create file " << file_path << std::endl;
            return false;
        }
        create_file.close();
    }
    return true;
}

bool WriteLogsToFile(const std::string& file_path, const std::string& email, const std::string& login, const std::string& password) {
    if (!EnsureFileExists(file_path)) {
        return false;
    }

    std::ofstream file(file_path, std::ios_base::app);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << file_path << " for writing." << std::endl;
        return false;
    }

    file << email << ',' << login << ',' << password << std::endl;

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

bool correct_password_check(const std::string& file_path, const std::string& email, const std::string& input_login, const std::string& input_pass) {
    if (!EnsureFileExists(file_path)) {
        return false;
    }

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
        std::getline(ss, stored_login, ',');
        std::getline(ss, stored_pass, ',');

        if (stored_login == input_login || stored_email == email) {
            if (stored_pass != input_pass) {
                std::cout << "Podany email/login lub hasło jest niepoprawne" << std::endl;
                file.close();
                return false;
            }
            else {
                std::cout << "Użytkownik z podanym loginem/emailem istnieje" << std::endl;
                file.close();
                return true;
            }
        }
    }

    file.close();
    return false;
}
