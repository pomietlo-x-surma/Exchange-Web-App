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

using tcp = boost::asio::ip::tcp;
namespace websocket = boost::beast::websocket;





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

//funkcja do pobierania info od klienta
std::string receive_text(const std::string& wiad) {
	std::unordered_map<std::string, std::string> currencies = { {"PLN","zloty"}, {"EUR","euro"}, {"USD","dollar"} };
	std::cout << wiad << std::endl;
	const std::string& file_path = "Dane.csv";
	std::stringstream sa(wiad);
	std::string tag;
	std::getline(sa, tag, ',');
	if (tag == "0" || tag == "1") {
		std::string email, login, pass, pass_rep;
		sa >> email;
		if (tag == "0") {
			sa >> pass;
			return check_logging(email, pass);
		}
		else if (tag == "1") {

			sa >> login >> pass >> pass_rep;

			return check_register(email, login, pass, pass_rep);
		}
	}
	else if (tag == "3") {
		std::string waluta1, waluta2;
		sa >> waluta1 >> waluta2;
		if (waluta2 == waluta1) {
			return "Z"+currency_comparison("PLN", "EUR") + "1.0";
		}
		else {
			return "Z"+ReadLogs(waluta1 + " " + waluta2, "currencies.csv");
		}
	}
	else if (tag == "4") {
		std::string em, log, usd, pln, eur, res;
		std::getline(sa, log, ',');
		std::string result = ReadLogs(log, "Users.csv");
		std::istringstream(result) >> usd >> eur >> pln;
		return "  USD: " + usd + "  EUR: " + eur + "  PLN: " + pln + '\n';
	}
	else if (tag == "6") {
		std::string log, waluta1, waluta2, wartosc;
		sa >> log >> waluta1 >> waluta2 >> wartosc;
		if (waluta1!=waluta2) {
			std::string usd, pln, eur;
			std::map<std::string, long double> saldo = { {"USD", 0}, {"EUR", 0}, {"PLN", 0} };
			std::string waluta11 = currencies[waluta1];
			std::string waluta22 = currencies[waluta2];
			std::string value = ReadLogs(log, "Users.csv");
			std::stringstream sd(value);
			std::istringstream(value) >> usd >> eur >> pln;
			long double usd_value = stold(usd), eur_value = stold(eur), pln_value = stold(pln), wart = stold(wartosc);
			saldo["USD"] = usd_value; saldo["EUR"] = eur_value; saldo["PLN"] = pln_value;
			if (saldo[waluta1] >= wart) {
				saldo[waluta1] -= wart;
				saldo[waluta2] += wart * stold(ReadLogs(waluta1 + " " + waluta2, "currencies.csv"));
			}
			else {
				return "ENie masz wystarczajacej srodkow na koncie!\n";
			}
			WriteLogsToFile_Currencies(log, to_string_with_precision(saldo["USD"]), to_string_with_precision(saldo["EUR"]), to_string_with_precision(saldo["PLN"]), "Users.csv", false
			);
			return "W  USD: "  + to_string_with_precision(saldo["USD"]) + "  EUR: " + to_string_with_precision(saldo["EUR"]) + "  PLN: " + to_string_with_precision(saldo["PLN"]);
		}
		else if (waluta1 != waluta2) {
			return "Y" + wartosc;
		}
		else {
			return "blad\n";
		}
	}
	return "blad";
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

					//petla glowna
					while (1) {
						boost::beast::multi_buffer buffer; //tworzenie bufora
						ws.read(buffer);

						//tekst odebrany
						std::string odebrana_wiad = boost::beast::buffers_to_string(buffer.data());
						//receive_text(odebrana_wiad); //wyswietlenie odebranej wiadomosci

						std::string response_message = receive_text(odebrana_wiad);

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
	//std::cout << "Start generacji!\n";
	//Currency_gen();
	//std::thread t1(Currency_update);
	serwer();
}
