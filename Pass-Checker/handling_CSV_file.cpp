#include <iostream>
#include <fstream>
#include <string>

bool WriteLogsToFile(const std::string& file_path, const std::string& server_name, const std::string& login, const std::string& password) {

    std::ofstream file;

    // Attempt to open the file in append mode
    file.open(file_path, std::ios_base::app);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << file_path << " for writing." << std::endl;
        return false;
    }

    // Write the logs to the file
    file << server_name << ',' << login << ',' << password << std::endl;

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
