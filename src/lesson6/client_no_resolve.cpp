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
            std::cout << "Сообщение сервера: " << &buf << std::endl;
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
        boost::asio::ip::address addr = boost::asio::ip::make_address(server_address);
        boost::asio::ip::tcp::endpoint endpoint(addr, server_port);
        tcp::socket socket(io_context);

        socket.connect(endpoint);

        communicate(socket);
    } catch (std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }

    return 0;
}
