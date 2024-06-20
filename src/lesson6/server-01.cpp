#include <iostream>
#include <boost/asio.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>

using boost::asio::ip::tcp;

void communicate(tcp::socket& socket) {
    try {
        while(true) {
            // Сервер получает сообщение от клиента
            boost::asio::streambuf buf;
            boost::asio::read_until(socket, buf, "\n");
            std::istream is(&buf);
            std::string client_message;
            std::getline(is, client_message);
            std::cout << "Сообщение клиента: " << client_message << std::endl;

            // Сервер отправляет сообщение клиенту
            std::cout << "Сервер введите сообщение: ";
            std::string server_message;
            std::getline(std::cin, server_message);
            server_message += "\n";
            boost::asio::write(socket, boost::asio::buffer(server_message));
        }
    } catch (std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }
}

int main() {
    try {
        // Чтение конфигурационного файла
        boost::property_tree::ptree pt;
        boost::property_tree::ini_parser::read_ini("main.config", pt);
        std::string address = pt.get<std::string>("server.address");
        int port = pt.get<int>("server.port");

        boost::asio::io_context io_context;
        tcp::acceptor acceptor(io_context, tcp::endpoint(boost::asio::ip::make_address(address), port));
        tcp::socket socket(io_context);

        std::cout << "Ожидание подключения клиента..." << std::endl;
        acceptor.accept(socket);
        std::cout << "Клиент подключен." << std::endl;

        communicate(socket);
    } catch (std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }

    return 0;
}
