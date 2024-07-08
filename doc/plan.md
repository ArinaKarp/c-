1. cpp
2. gcc -> g++ -> a.out
3. compilation unit -> hpp files
4. CMake
5. github
======

https://www.bogotobogo.com/cplusplus/memoryallocation.php
https://en.wikipedia.org/wiki/Data_segment

1. memory, stack, heap, memory allocations 
2. arrays. static + dinamic array
3. pointers and addresses

ДЗ: задача на литкоде twoSum

========

https://cpp-python-nsu.inp.nsk.su/textbook/sec3/ch4
https://metanit.com/cpp/tutorial/4.6.php

1. functions, pass arguments to functions
https://metanit.com/cpp/tutorial/5.1.php
2. structures + classes: incapsulation, inheritance, polymorphism. 

ДЗ: реализовать паттерн стратегия

========

https://education.yandex.ru/handbook/cpp/article/templates
1. templates
https://metanit.com/cpp/tutorial/7.1.php --> вся глава
2. stl containers
https://habr.com/ru/articles/182920/
https://metanit.com/cpp/tutorial/11.1.php
https://metanit.com/cpp/tutorial/11.2.php
https://metanit.com/cpp/tutorial/15.3.php
3. cpp standarts, C++11, lambdas, auto, unique_ptr, shared_ptr
4. что такое паттерн Декоратор

ДЗ: подключиться к бд sqlite и прочитать "select * from test_messages;" через интерфейс С++ или любую его обертку. 
Доп: В коде использовать std::unique_ptr для объекта подключения к бд
Доп2: Отключение от бд сделать через кастомный деструктор std::unique_ptr
========

многопоточка

разница между процессом и потоком. https://moodle.kstu.ru/mod/page/view.php?id=49
что такое контекст. Какие данные общие (шарятся) между 
 * процессами: то что есть в ОС
 * потоками: то что есть в контексте процесса

https://radioprog.ru/post/1402
https://habr.com/ru/companies/otus/articles/549814/
как в коде создать поток 
состояние гонки
примитивы синхронизации
что такое дедлок

https://cpp-kt.github.io/cpp-notes/26_multithreading.html

ДЗ: https://leetcode.com/problemset/concurrency/

==========

https://www.boost.org/doc/libs/1_85_0/doc/html/boost_asio/examples.html
https://www.boost.org/doc/libs/1_41_0/doc/html/boost_asio/using.html
https://blog.skillfactory.ru/glossary/asinhronnoe-programmirovanie/
https://habr.com/ru/articles/192284/
1. Boost, asio
2. Разобрать пример синхронного кода
3. Разобрать асинхронный код

ДЗ: 
1. Простой вариант чата с синхронной отправкой/передачей сообщений
2. Простой вариант чата с асинхронной отправкой/передачей сообщений
"простой вариант" предполагает, что ip получателя и отправителя известны и захардкожены или внесены в конфигурационный файл (вариант с конфигурационным файлом предпочтительнее)

==========

основной источник: https://www.youtube.com/watch?v=7FQwAjELMek&list=WL&index=109
материалы : https://github.com/vinniefalco/CppCon2018
https://www.boost.org/doc/libs/1_67_0/libs/beast/doc/html/index.html

рассматриваем websocket + boost.beast

1. что такое websocket отличие от http
https://habr.com/ru/sandbox/171066/
https://blog.skillfactory.ru/glossary/websocket/
https://appmaster.io/ru/blog/veb-soket-protiv-traditsionnogo-http
2. что за зверь boost.beast
https://www.boost.org/doc/libs/1_67_0/libs/beast/doc/html/beast/using_websocket.html
3. рисуем схему того, как будет работать наш чат. Схема для сервера и клиента: https://disk.astralinux.ru/s/pN5d9KFdK3mdAY8

дз: реализовать сервер, который будет работать с этим клиентом: https://www.boost.org/doc/libs/1_81_0/libs/beast/example/websocket/server/chat-multi/chat_client.html

===========

как дебажить с параметрами с помощью launch.json и settings.json

использование дев контейнеров
https://code.visualstudio.com/docs/devcontainers/create-dev-container

============

Итоги: что нужно дополнить в данном плане / что посмотреть дальше
1. Больше про правильное именование переменных и функций
2. Больше про codestyle
3. Больше про умные указатели
4. Больше про различные идиомы и паттерны
5. Выбрать более простой и низкоуровневый финальный проект, чтобы меньше использовать примеры и больше писать руками
6. Больше использования различных инструментов, например, gdb и valgrind (как планировалось изначально, но ушло на второй план).
7. Больше ООП.
8. Меньше кода библиотек, он бывает слишком сложным для начинающих (да и для продолжающих иногда тоже).
9. Можно было остановиться на коде который использует низкоуровневые сетевые примитивы и получает http запросы.