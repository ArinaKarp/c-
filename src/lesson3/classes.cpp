#include <iostream>
#include <vector>
 
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

class Person
{
public:
    std::string name;
    std::string surname;
    virtual void talk() {
        std::cout << "I'm just a person\n";
    }

    virtual ~Person() {};
};

class Developer: public Person
{  
public:
    void talk() override {
        std::cout << "I'm a C++ developer\n";
    }
};

int main()
{
    // PersonStruct person;
    // // устанавливаем значения полей класса
    // person.name = "Bob";
    // person.age = 42;
    // // получаем значения полей
    // // std::string username = person.name;
    // // unsigned userage = person.age;
    // // выводим полученные данные на консоль
    // // std::cout << "Name: " << username << "\tAge: " << userage << std::endl;
    // person.print();

    std::vector<Person *> team;

    team.push_back(new Person());
    team.push_back(new Person());
    team.push_back(new Person());
    team.push_back(new Developer());
    
    for (auto &member : team) {
        member->talk();
    }

}