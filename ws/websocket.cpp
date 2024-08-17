#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <iostream>
#include <thread>
#include "handling_CSV_file.h"
#include "password_checker.h"
#include "money_converter.h"
#include "User.h"
#include <unordered_map>
#include <string>


using tcp = boost::asio::ip::tcp;
namespace websocket = boost::beast::websocket;


//funkcja wysylajaca do klienta
std::string process_message(const std::string& received_message) {
	std::cout << received_message << std::endl;
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
	WriteLogsToFile_Currencies(login, "0.0", "0.0", "0.0", "Users.csv", true);
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
	if (tag == "0" || tag == "1") { //TODO przerobić na switch/case
		std::string email, login, pass, pass_rep;
		std::getline(sa, email, ' ');
		if (tag == "0") {
			std::getline(sa, pass, ' ');
			return check_logging(email, pass);
		}
		else if (tag == "1") {
			std::getline(sa, login, ' ');
			std::getline(sa, pass, ' ');
			std::getline(sa, pass_rep, ' ');

			return check_register(email, login, pass, pass_rep);
		}
	}
	else if (tag == "3") {
		std::string waluta1, waluta2;
		//std::string all = "";
		std::getline(sa, waluta1, ' ');
		std::getline(sa, waluta2, ' ');
		waluta1 = currencies[waluta1];
		waluta2 = currencies[waluta2];
		//std::cout << currency_comparison(waluta1, waluta2, true) << std::endl;
		if (waluta2 == waluta1) {
			return "Z"+currency_comparison("zloty", "euro") + "1.0";
		}
		else {
			return "Z"+currency_comparison(waluta1, waluta2) + " " + currency_comparison(waluta1, waluta2, true);
		}
	}
	else if (tag == "4") {
		std::string em, log, usd, pln, eur, res;
		std::getline(sa, em, ',');
		std::getline(sa, log, ',');
		std::string result = ReadLogs(log, "Users.csv");
		std::istringstream(result) >> usd >> eur >> pln;
		std::cout << result << std::endl;
		return "  USD: " + usd + "  EUR: " + eur + "  PLN: " + pln + '\n';
	}
	else if (tag == "6") {
		std::string log, waluta1, waluta2, wartosc;
		sa >> log >> waluta1 >> waluta2 >> wartosc;
		if (waluta1 == waluta2) {
			return "1.0";
		}
		else if ((waluta1 != waluta2) && waluta2 != "") {
			std::string usd, pln, eur, login1;
			waluta1 = currencies[waluta1];
			waluta2 = currencies[waluta2];
			std::string value = ReadLogs(login1, "Users.csv");
			std::stringstream sd(value);
			std::getline(sd, log, ',');
			std::istringstream(value) >> usd >> eur >> pln;
			long double wart = stold(wartosc);
			if (waluta1 == "zloty" && stold(pln) <= wart) {
				return "W" + std::to_string(wart * stold(currency_comparison(waluta1, waluta2)));
			}
			else if (waluta1 == "euro" && stold(eur) <= wart) {
				return "W" + std::to_string(wart * stold(currency_comparison(waluta1, waluta2)));
			}
			else if (waluta1 == "dollar" && stold(usd) <= wart) {
				return "W" + std::to_string(wart * stold(currency_comparison(waluta1, waluta2)));
			}
			else {
				return "ENie masz wystarczajacej srodkow na koncie!\n";
			}
			

		}
		else {
			return "blad\n";
		}
	}
	return "blad";
}




void serwer() { //zrobić hermetyzację tej funkcji
	std::cout << "Rozpoczynanie pracy serwera!\n";
	try {
		boost::asio::io_context ioc;
		tcp::acceptor acceptor{ ioc, {tcp::v4(), 8080} };

		while (true) {
			tcp::socket socket{ ioc };
			acceptor.accept(socket);
			std::thread{ [socket = std::move(socket)]() mutable { //musi byc mutable xd
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
	serwer();
}
