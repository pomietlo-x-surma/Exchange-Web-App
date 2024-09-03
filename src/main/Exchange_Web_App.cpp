#include <iostream>
#include "../modules/server_file.hpp"
#include <thread>
#include "../modules/handling_CSV_file.hpp"
#include <sqlite3.h>

//int main(){
//	//std::thread t1(Currency_update); //updating currencies in currencies.csv
//	server(); //turning on server
//}

int main() {
    sqlite3* db;
    int rc = sqlite3_open("example.db", &db);

    if (rc) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        return rc;
    }
    else {
        std::cout << "Opened database successfully." << std::endl;
    }

    sqlite3_close(db);
    return 0;
}
