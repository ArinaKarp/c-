#include <iostream>
#include <boost/asio.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>

using boost::asio::ip::tcp;

void communicate(tcp::socket& socket) {
    try {
        while(true) {
            // Клиент отправляет сообщение серверу
            std::cout << "Клиент введите сообщение: ";
            std::string client_message;
            std::getline(std::cin, client_message);
            client_message += "\n";
            boost::asio::write(socket, boost::asio::buffer(client_message));

            // Клиент получает сообщение от сервера
            boost::asio::streambuf buf;
            boost::asio::read_until(socket, buf, "\n");
            std::istream is(&buf);
            std::string server_message;
            std::getline(is, server_message);
            std::cout << "Сообщение сервера: " << server_message << std::endl;
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
        std::string server_address = pt.get<std::string>("client.server_address");
        int server_port = pt.get<int>("client.server_port");

        boost::asio::io_context io_context;
        tcp::resolver resolver(io_context);
        tcp::resolver::results_type endpoints = resolver.resolve(server_address, std::to_string(server_port));
        tcp::socket socket(io_context);

        boost::asio::connect(socket, endpoints);

        communicate(socket);
    } catch (std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }

    return 0;
}
