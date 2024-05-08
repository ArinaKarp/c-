#include <iostream>
 
struct PersonStruct 
{
// public:
    std::string name;
    unsigned age;
    void print() 
    {
        print_P();
        // std::cout << "Name: " << name << "\tAge: " << age << std::endl;
    }
// private:
    void print_P() 
    {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        std::cout << "Name: " << name << "\tAge: " << age << std::endl;
    }
};

class PersonClass 
{
// public:
    std::string name;
    unsigned age;
    void print() 
    {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        std::cout << "Name: " << name << "\tAge: " << age << std::endl;
    }
};


int main()
{
    PersonStruct person;
    // устанавливаем значения полей класса
    person.name = "Bob";
    person.age = 42;
    // получаем значения полей
    // std::string username = person.name;
    // unsigned userage = person.age;
    // выводим полученные данные на консоль
    // std::cout << "Name: " << username << "\tAge: " << userage << std::endl;
    person.print();
}