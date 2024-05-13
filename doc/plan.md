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

1. Boost, asio
2. Разобрать пример синхронного кода
3. Разобрать асинхронный код

ДЗ: 
1. Простой вариант чата с синхронной отправкой/передачей сообщений
2. Простой вариант чата с асинхронной отправкой/передачей сообщений
"простой вариант" предполагает, что ip получателя и отправителя известны и захардкожены или внесены в конфигурационный файл (вариант с конфигурационным файлом предпочтительнее)
