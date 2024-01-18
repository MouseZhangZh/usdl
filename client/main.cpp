//
// Created by Mouse Zhang on 2024/1/18.
//

#include <iostream>
#include <string>

#include "boost/asio.hpp"

int main() {
    try {
        boost::asio::io_service io_service;
        boost::asio::ip::tcp::resolver resolver(io_service);
        boost::asio::ip::tcp::resolver::query query("localhost", "12345");
        boost::asio::ip::tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
        boost::asio::ip::tcp::socket socket(io_service);
        boost::asio::connect(socket, endpoint_iterator);

        for (;;) {
            std::cout << "Enter message: ";
            std::string message;
            std::getline(std::cin, message);

            boost::asio::write(socket, boost::asio::buffer(message));

            char reply[512] = { 0 };
            size_t reply_length = boost::asio::read(socket, boost::asio::buffer(reply, message.size()));
            std::cout << "Reply is: ";
            std::cout.write(reply, reply_length);
            std::cout << "\n";
        }
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}
