#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <iostream>
#include <thread>
#include "handling_CSV_file.h"
#include "password_checker.h"
#include "money_converter.h"
#include "server_message_processing.hpp"
#include <unordered_map>
#include <string>
#include <map>
#include <fstream>
#include <iomanip> 
#include <array>
#include <chrono>


using tcp = boost::asio::ip::tcp;
namespace websocket = boost::beast::websocket;

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
