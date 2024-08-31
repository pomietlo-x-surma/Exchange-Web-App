#include <iostream>
#include "../modules/server_file.hpp"
#include <thread>
#include "../modules/handling_CSV_file.hpp"

int main(){
	//std::thread t1(Currency_gen); //generating new currencies to currencies.csv
	//std::thread t1(Currency_update); //updating currencies in currencies.csv
	server();
}
