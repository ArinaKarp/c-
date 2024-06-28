//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

//------------------------------------------------------------------------------
//
// Example: WebSocket server, asynchronous
//
//------------------------------------------------------------------------------

#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/dispatch.hpp>
#include <boost/asio/strand.hpp>
#include <algorithm>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <vector>

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace websocket = beast::websocket; // from <boost/beast/websocket.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

//------------------------------------------------------------------------------

// Report a failure
void
fail(beast::error_code ec, char const* what)
{
    std::cerr << what << ": " << ec.message() << "\n"; // Выводит сообщения об ошибках на консоль
}

// Echoes back all received WebSocket messages
class session : public std::enable_shared_from_this<session> //std::enable_shared_from_this является вспомогательным классом, который позволяет объекту получить std::shared_ptr на самого себя.
{
    websocket::stream<beast::tcp_stream> ws_; // создан обьект ws_  для хранения и управления состоянием WebSocket соединения
    beast::flat_buffer buffer_; // создается обьект buffer_ для хранения данных, поступающих и отправляемых по WebSocket соединению.

public:
    // Take ownership of the socket
    explicit                    // explicit запрещает неявные преобразования типов. Это значит, что объекты класса должны быть созданы явно.
    session(tcp::socket&& socket)
        : ws_(std::move(socket)) //значение из socket передается в ws_
    {
    }

    // Get on the correct executor
    void
    run()
    {
        // We need to be executing within a strand to perform async operations
        // on the I/O objects in this session. Although not strictly necessary
        // for single-threaded contexts, this example code is written to be
        // thread-safe by default.
        net::dispatch(ws_.get_executor(),
            beast::bind_front_handler(
                &session::on_run,
                shared_from_this()));
    }

    // Start the asynchronous operation
    void
    on_run()
    {
        //  Устанавливаем рекомендуемые настройки таймаута для WebSocket-стрима
        ws_.set_option(
            websocket::stream_base::timeout::suggested(
                beast::role_type::server));

        //  Устанавливаем декоратор для изменения заголовка "Server" в ответе WebSocket
        ws_.set_option(websocket::stream_base::decorator(
            [](websocket::response_type& res)
            {
                res.set(http::field::server,
                    std::string(BOOST_BEAST_VERSION_STRING) +
                        " websocket-server-async");
            }));
        // Асинхронно принимаем WebSocket-соединение
        ws_.async_accept(
            beast::bind_front_handler(
                &session::on_accept,
                shared_from_this()));
    }
 // Метод, вызываемый при успешном принятии WebSocket-соединения
    void
    on_accept(beast::error_code ec)
    {
        if(ec)
            return fail(ec, "accept");  // В случае ошибки выводим сообщение и завершаем выполнение метода

        // Read a message
        do_read();
    }

    void
    do_read()
    {
        // читаем сообщение в буфер
        ws_.async_read(
            buffer_,
            beast::bind_front_handler(
                &session::on_read,
                shared_from_this()));
    }
 // Метод, вызываемый при завершении асинхронного чтения данных из WebSocket
    void
    on_read(
        beast::error_code ec,
        std::size_t bytes_transferred)
    {
        boost::ignore_unused(bytes_transferred);  // Игнорируем неиспользуемый параметр

        // This indicates that the session was closed
        if(ec == websocket::error::closed)
            return;

        if(ec)
            return fail(ec, "read"); // В случае ошибки чтения выводим сообщение и завершаем выполнение метода

        //  Эхо-ответ на полученное сообщение
        ws_.text(ws_.got_text()); // Определяем формат сообщения
        ws_.async_write(
            buffer_.data(),
            beast::bind_front_handler(
                &session::on_write,
                shared_from_this()));
    }

    void
    on_write(
        beast::error_code ec,
        std::size_t bytes_transferred)
    {
        boost::ignore_unused(bytes_transferred); // Игнорируем неиспользуемый параметр

        if(ec)
            return fail(ec, "write");  // В случае ошибки записи выводим сообщение и завершаем выполнение метода

        // // Очищаем буфер
        buffer_.consume(buffer_.size());

        //  Выполняем новое чтение данных
        do_read();
    }
};

//------------------------------------------------------------------------------

// Принимает входящие соединения и запускает сессии
class listener : public std::enable_shared_from_this<listener>
{
    net::io_context& ioc_; // Ссылка на io_context для управления вводом/выводом
    tcp::acceptor acceptor_;     // Acceptor для принятия входящих соединений

public:
// Инициализация listener с io_context и endpoint

    listener(
        net::io_context& ioc,
        tcp::endpoint endpoint)
        : ioc_(ioc)
        , acceptor_(ioc)
    {
        beast::error_code ec;

        // Открываем acceptor для выбранного протокола
        acceptor_.open(endpoint.protocol(), ec);
        if(ec)
        {
            fail(ec, "open");  // В случае ошибки выводим сообщение об ошибке и выходим
            return;
        }

       // Разрешаем повторное использование адреса
        acceptor_.set_option(net::socket_base::reuse_address(true), ec);
        if(ec)
        {
            fail(ec, "set_option");  // В случае ошибки выводим сообщение об ошибке и выходим
            return;
        }

        // Привязываем acceptor к указанному адресу и порту
        acceptor_.bind(endpoint, ec);
        if(ec)
        {
            fail(ec, "bind");  // В случае ошибки выводим сообщение об ошибке и выходим
            return;
        }

       // Начинаем прослушивание входящих соединений
        acceptor_.listen(
            net::socket_base::max_listen_connections, ec);
        if(ec)
        {
            fail(ec, "listen");  // В случае ошибки выводим сообщение об ошибке и выходим
            return;
        }
    }

   // Начинаем принимать входящие соединения
    void
    run()
    {
        do_accept(); // Запускаем процесс принятия входящих соединений
    }

private:
 // Асинхронно принимает соединения
    void do_accept()
    {
         // Принимаем еще одно соединение
        acceptor_.async_accept(
            net::make_strand(ioc_),
            beast::bind_front_handler(
                &listener::on_accept,
                shared_from_this()));
    }

    void
    on_accept(beast::error_code ec, tcp::socket socket)
    {
        if(ec)
        {
            fail(ec, "accept"); // В случае ошибки выводим сообщение об ошибке
        }
        else
        {

            std::make_shared<session>(std::move(socket))->run(); // Создаем новую сессию и запускаем ее
        }


        do_accept(); // Принимаем следующее входящее соединение
    }
};

//------------------------------------------------------------------------------

int main(int argc, char* argv[])
{
    // Проверяем аргументы командной строки
    if (argc != 4)
    {
        std::cerr <<
            "Usage: websocket-server-async <address> <port> <threads>\n" <<
            "Example:\n" <<
            "    websocket-server-async 0.0.0.0 8080 1\n";
        return EXIT_FAILURE;
    }
    auto const address = net::ip::make_address(argv[1]);  // Получаем адрес для прослушивания
    auto const port = static_cast<unsigned short>(std::atoi(argv[2])); // Получаем порт для прослушивания
    auto const threads = std::max<int>(1, std::atoi(argv[3]));  // Количество потоков для работы сервера

    //Создаем io_context для всех операций ввода/вывода
    net::io_context ioc{threads};

    //  Создаем и запускаем прослушивающий порт
    std::make_shared<listener>(ioc, tcp::endpoint{address, port})->run();

    // Запускаем io_context с указанным числом потоков
    std::vector<std::thread> v; // Создаем вектор для хранения объектов потоков
    v.reserve(threads - 1); // Резервируем место в векторе для (threads - 1) потоков
    for(auto i = threads - 1; i > 0; --i)
        v.emplace_back(
        [&ioc]
        {
            ioc.run(); // Запускаем главный поток для выполнения io_context
        });
    ioc.run();

    return EXIT_SUCCESS; // Успешно завершаем

}
