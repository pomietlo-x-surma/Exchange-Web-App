#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <iostream>
#include <thread>

using tcp = boost::asio::ip::tcp;
namespace websocket = boost::beast::websocket;

void receive_text(const std::string& wiad) {
	unsigned char split = wiad.find(" ");
	std::string login = wiad.substr(0, split);
	std::string pass = wiad.substr(split + 1, wiad.length());
	std::cout << login << " " << pass << '\n';

}



void serwer111() {
	try {
		boost::asio::io_context ioc;
		tcp::acceptor acceptor{ ioc, {tcp::v4(), 8080} };

		while (true) {
			tcp::socket socket{ ioc };
			acceptor.accept(socket);
			std::thread{ [socket = std::move(socket)]() mutable { //musi byc mutalbe xd
				try {
					websocket::stream<tcp::socket> ws{std::move(socket)};
					ws.accept();



					//petla glowna
					while (1) {
						boost::beast::multi_buffer buffer;
						ws.read(buffer);

						//tekst odebrany
						std::string odebrana_wiad = boost::beast::buffers_to_string(buffer.data());
						receive_text(odebrana_wiad);

						//tekst zwrotny
						ws.text(ws.got_text());
						ws.write(buffer.data());
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
	serwer111();
}
