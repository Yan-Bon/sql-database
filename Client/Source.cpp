#include <boost/asio.hpp>
#include <iostream>
#include <string>

using boost::asio::ip::tcp;

void run_client(const std::string& host, short port) {
	try {

		boost::asio::io_context io_context;

	
		tcp::socket socket(io_context);
		tcp::resolver resolver(io_context);
		boost::asio::connect(socket, resolver.resolve(host, std::to_string(port)));

		std::cout << "Connected to server " << host << ":" << port << "\n";

		while (true) {
			std::cout << "Enter message (or \"exit\"): ";
			std::string message;
			std::getline(std::cin, message);

			if (message == "exit") {
				break;
			}

	
			boost::asio::write(socket, boost::asio::buffer(message));

	
			char reply[2048];
			std::size_t reply_length = socket.read_some(boost::asio::buffer(reply));

			std::cout << "Server response: ";
			std::cout.write(reply, reply_length);
			std::cout << "\n";
		}
	}
	catch (std::exception& e) {
		std::cerr << "Client error: " << e.what() << std::endl;
	}
}

int main() {
	const std::string host = "127.0.0.1";
	const short port = 12345;

	run_client(host, port);

	return 0;
}
