#include "../modules/handling_db.hpp"
#include <thread>

int main() {
    std::thread t1(currency_generation); //updating currencies in currencies.csv
    //server(); //turning on server
}
