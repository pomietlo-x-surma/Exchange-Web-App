#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <iostream>
#include <thread>
#include "handling_CSV_file.h"
#include "password_checker.h"


using tcp = boost::asio::ip::tcp;
namespace websocket = boost::beast::websocket;



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
	else if (pass_check(pass)!="") {
		return process_message(pass_check(pass));
	}
	else if (pass != pass_rep) {
		return process_message("Hasla sa rozne!");
	}
	WriteLogsToFile(email, login, pass);
	return "0";
}

std::string check_logging(const std::string& email, const std::string& pass) {
	std::cout << "logowanie!" << std::endl;
	if (correct_password_check(email, pass)) {
		return process_message("Witaj" + email + pass);

	}
	return process_message("5");
}

//funkcja do pobierania info od klienta
std::string receive_text(const std::string& wiad) {
	const std::string& file_path = "Dane.csv";
	std::stringstream sa(wiad);
	std::string tag, email, login, pass, pass_rep;
	std::getline(sa, tag, ',');
	std::getline(sa, email, ' ');
	if (tag == "0") {
		std::getline(sa, pass, ' ');
		return check_logging(email, pass);
	}
	if (tag == "1") {
		std::getline(sa, login, ' ');
		std::getline(sa, pass, ' ');
		std::getline(sa, pass_rep, ' ');
		return check_register(email, login, pass, pass_rep);
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
					if (se.code() != websocket::error::closed) {
						std::cerr << "Error1: " << se.code().message() << "\n";
					}
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
