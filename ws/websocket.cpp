#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <iostream>
#include <thread>
#include "baza_danych.h"
using tcp = boost::asio::ip::tcp;
namespace websocket = boost::beast::websocket;



//funkcja wysylajaca do klienta
std::string process_message(const std::string& received_message) {
	return "Echo: " + received_message;
}


//funkcja do pobierania info od klienta
std::string receive_text(const std::string& wiad) {
	unsigned char split = wiad.find(" ");
	std::string login = wiad.substr(0, split);
	std::string pass = wiad.substr(split + 1, wiad.length());   //rozdzielanie stringa
	std::cout << login << " " << pass << '\n';
	std::unordered_map<std::string, std::string>::iterator it = logging.find(login); //tworzenie iteratora do loginu 
	if (it != logging.end() && (logging[login] == pass)) { //jesli login isnieje (istnieje iterator), przyrównaj go z hasłem w bazie
		return process_message("istnieje");
	}
	return process_message("nie istnieje");
}




void serwer() {
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
						std::cerr << "Error: " << se.code().message() << "\n";
					}
				}
			} }.detach();
		}
	}
	catch (std::exception const& e) {
		std::cerr << "Error: " << e.what() << "\n";
	}
}

int main() {
	serwer();
}
