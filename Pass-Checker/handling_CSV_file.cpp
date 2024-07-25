#include <iostream>
#include <fstream>
#include <string>

bool WriteLogsToFile(const std::string& file_path, const std::string& email, const std::string& login, const std::string& password) {

    std::ofstream file;

    // Attempt to open the file in append mode
    file.open(file_path, std::ios_base::app);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << file_path << " for writing." << std::endl;
        return false;
    }

    // Writing the logs to the file
    file << email << ',' << login << ',' << password << std::endl;

    // Check for any errors during write operation
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
