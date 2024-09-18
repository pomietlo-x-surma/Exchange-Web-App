#include <fstream>
#include <iostream>
#include <sstream>
#include "../modules/server_file.hpp"
#include <thread>
#include "../modules/handling_CSV_file.hpp"
#include <string>
#include "sqlite3.h"

int main() {
    currency_generation(); //updating currencies in currencies.csv
    server(); //turning on server
}
