#include "../modules/handling_db.hpp"
#include "../modules/server_file.hpp"
#include <thread>

int main() {
    std::thread t1(currency_generation); //updating currencies in database.db
    server(); //turning on server
}
