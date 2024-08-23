#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <iostream>
#include <thread>
#include "handling_CSV_file.h"
#include "password_checker.h"
#include "money_converter.h"
#include <unordered_map>
#include <string>
#include <map>
#include <fstream>
#include <iomanip> 
#include <array>
#include <chrono>


using tcp = boost::asio::ip::tcp;
namespace websocket = boost::beast::websocket;

std::unordered_map<std::string, std::string> currencies = { {"PLN","zloty"}, {"EUR","euro"}, {"USD","dollar"} };



std::string to_string_with_precision(double value, char precision = 2) {
	std::ostringstream out;
	out << std::fixed << std::setprecision(precision) << value;
	return out.str();
}

//funkcja wysylajaca do klienta
std::string process_message(const std::string& received_message) {
	return received_message;
}
std::string check_register(const std::string& email, const std::string& login, const std::string& pass, const std::string& pass_rep) {
	if (!(email_check(email) && login_check(login))) {
		return process_message("bledny E-mail lub haslo!");
	}
	else if (check_login_email_existence(email, login)) {
		return process_message("podany E-mail lub login juz istnije!");
	}
	else if (pass_check(pass) != "") {
		return process_message(pass_check(pass));
	}
	else if (pass != pass_rep) {
		return process_message("Hasla sa rozne!");
	}
	WriteLogsToFile_Passes(email, login, pass, "Dane.csv");
	WriteLogsToFile_Currencies(login, "100", "0.0", "0.0", "Users.csv", true);
	return "0"+login;
}

std::string check_logging(const std::string& email, const std::string& pass) {
	if (correct_password_check(email, pass)!="") {
		return process_message(correct_password_check(email, pass));

	}
	return process_message("5");
}



//0
std::string login_user(const std::string& message, const std::string& file_path = "Dane.csv") {
	std::stringstream sa(message);
	std::string email, pass;
	sa >> email >> pass;
	return check_logging(email, pass);
}

//1
std::string register_user(const std::string& message, const std::string& file_path = "Dane.csv") {;
	std::stringstream sa(message);
	std::string email, login, pass, pass_rep;
	sa >> email >> login >> pass >> pass_rep;
	return check_register(email, login, pass, pass_rep);
}

//3
std::string exchange_rate(const std::string& message) {
	std::stringstream sa(message);
	std::cout << message << "L\n";
	std::string currency1, currency2, value, value_result;
	sa >> currency1 >> currency2 >> value;
	if (value == "") {
		if (currency1 == currency2) {
			return "Z1.0";
		}
		return "Z" + ReadLogs(currency1 + " " + currency2, "currencies.csv");
	}
	if (currency1 == currency2) {
		return "ZZ" + to_string_with_precision(stold(value) / 10);
	}
	std::stringstream os(ReadLogs(currency1 + " " + currency2, "currencies.csv"));
	std::getline(os, value_result, ' ');
	return "ZZ" + to_string_with_precision(stold(value_result) * stold(value) / 10);
}


//4
std::string account_balance(const std::string& message) {
	std::string log, usd, pln, eur;
	std::string result = ReadLogs(message, "Users.csv");
	std::istringstream(result) >> usd >> eur >> pln;
	std::cout << "git 4\n";
	return "W  USD: " + usd + "  EUR: " + eur + "  PLN: " + pln + '\n';
}

//6
std::string exchange(const std::string& message) {
	std::stringstream sa(message);
	std::string login, currency1, currency2, value;
	sa >> login >> currency1 >> currency2 >> value;
	if (currency1 != currency2) {
		std::string usd, pln, eur;
		std::map<std::string, long double> saldo = { {"USD", 0.0}, {"EUR", 0.0}, {"PLN", 0.0} };
		std::string waluta11 = currencies[currency1];
		std::string waluta22 = currencies[currency2];
		std::istringstream(ReadLogs(login, "Users.csv")) >> usd >> eur >> pln;
		long double usd_value = stold(usd), eur_value = stold(eur), pln_value = stold(pln), wart = stold(value);
		saldo["USD"] = usd_value; saldo["EUR"] = eur_value; saldo["PLN"] = pln_value;
		if (saldo[currency1] >= wart) {
			saldo[currency1] -= wart;
			saldo[currency2] += wart * stold(ReadLogs(currency1 + " " + currency2, "currencies.csv"));
		}
		else {
			return "ENie masz wystarczajacej srodkow na koncie!\n";
		}
		WriteLogsToFile_Currencies(login, to_string_with_precision(saldo["USD"]), to_string_with_precision(saldo["EUR"]), to_string_with_precision(saldo["PLN"]), "Users.csv", false
		);
		return "W  USD: " + to_string_with_precision(saldo["USD"]) + "  EUR: " + to_string_with_precision(saldo["EUR"]) + "  PLN: " + to_string_with_precision(saldo["PLN"]);
	}
	else if (currency1 == currency2) {
		return "Y" + value;
	}
}





std::string receive_text(const char& id, const std::string& message) {
	std::cout << id << "," << message << '\n';
	switch (id) {
		case '0': return login_user(message);
		case '1': return register_user(message);
		case '3': return exchange_rate(message);
		case '4': return account_balance(message);
		case '6': return exchange(message);
	}
}




void serwer() {
	std::cout << "Rozpoczynanie pracy serwera!\n";
	try {
		boost::asio::io_context ioc;
		tcp::acceptor acceptor{ ioc, {tcp::v4(), 8080} };

		while (true) {
			tcp::socket socket{ ioc };
			acceptor.accept(socket);
			std::thread{ [socket = std::move(socket)]() mutable {
				try {
					websocket::stream<tcp::socket> ws{ std::move(socket) };
					ws.accept();

					//main loop
					while (1) {
						boost::beast::multi_buffer buffer;
						ws.read(buffer);

						//tekst odebrany
						std::string received_message = boost::beast::buffers_to_string(buffer.data());
						char id = received_message[0];
						received_message=received_message.substr(2);
						std::string response_message = receive_text(id, received_message);

						//tekst zwrotny
						ws.text(ws.got_text());
						ws.write(boost::asio::buffer(response_message));
					}
				}
				catch (boost::system::system_error const& se) {
					if (se.code() != websocket::error::closed) {}
				}
			} }.detach();
		}
	}
	catch (std::exception const& e) {
		std::cerr << "Error2: " << e.what() << "\n";
	}
}

int main() {
	std::cout << "Start generacji111!\n";
	//Currency_gen();
	//std::thread t1(Currency_update);
	serwer();
}
