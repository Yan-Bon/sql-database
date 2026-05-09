#pragma once
#include <boost/asio.hpp>
#include <iostream>
#include <thread>
#include <string>
#include <vector>
#include "QueryIntepreter.h"
using boost::asio::ip::tcp;
#define BUFFER_SIZE 3000000
#define DEBUG
class TcpServer {
public:
	MasterStorage* storage;
	TcpServer(boost::asio::io_context& io_context, short port, MasterStorage* ms)
		: acceptor_(io_context, tcp::endpoint(tcp::v4(), port)), storage(ms) {
		start_accept();
		std::cout << "\n - TCP Server constructed. Start accepted";
	}

private:
	void start_accept() {
		acceptor_.async_accept(
			[this](boost::system::error_code ec, tcp::socket socket) {
				if (!ec) {
					std::thread(&TcpServer::handle_client, this, std::move(socket)).detach();
				}
				start_accept();
			});
	}

	void handle_client(tcp::socket socket) {
		std::string remote_ip_port = socket.remote_endpoint().address().to_string() + ":" + std::to_string(socket.remote_endpoint().port());
		std::cout << "\nClient handler thread created : " << remote_ip_port << std::endl;
			char data[BUFFER_SIZE];
			int requestsCount = 0;
			std::size_t length;
			QueryInterpreter qi(*storage);
			while (true) {
				if (!socket.is_open())
					return;
#ifndef DEBUG
				try {
#endif
					try {
						length = socket.read_some(boost::asio::buffer(data));
					}
					catch (std::exception& ex) {
						std::cout << "! - Socket error occured. Connection established with : " << remote_ip_port;
						return;
					}
					std::string request = data;


				std::cout << "Request by " << remote_ip_port << " : ";
				for (int i = 0; i < length; ++i) {
					std::cout << data[i];
					data[i] = '\0';
				}
				std::cout << std::endl;
				std::string command = request.substr(0,length);
				++requestsCount;
				qi.execute(command);
				std::string jsonSdbResponse = qi.RESPONSE();
				boost::asio::write(socket, boost::asio::buffer(jsonSdbResponse, jsonSdbResponse.size()));	
#ifndef DEBUG
			}
			catch (std::exception& ex) {
				std::cout << "\n! - Exception : " << ex.what();
			}
#endif
			}
	}
	tcp::acceptor acceptor_;
};
