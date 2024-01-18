//
// Created by Mouse Zhang on 2024/1/18.
//

#include <iostream>

#include "boost/asio.hpp"

int main() {
    try {
        boost::asio::io_service io_service;
        boost::asio::ip::tcp::acceptor acceptor(io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 12345));

        for (;;) {
            boost::asio::ip::tcp::socket socket(io_service);
            acceptor.accept(socket);

            boost::system::error_code error;
            for (;;) {
                char data[512] = { 0 };
                size_t length = socket.read_some(boost::asio::buffer(data), error);
                if (error == boost::asio::error::eof)
                    break; // Connection closed cleanly by peer.
                else if (error)
                    throw boost::system::system_error(error); // Some other error.

                std::cout << "Receive message: " << data << std::endl;
                boost::asio::write(socket, boost::asio::buffer(data, length));
            }
        }
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}