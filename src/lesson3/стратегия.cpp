#include <iostream>
using namespace std;
class Username
{
public:
 Username(string name): name{name}
 {}
 virtual void write() const
 {
    cout<< "Username:" << name << endl;
 }
 private:
    string name;
};
class Member: public Username
{
public:
    Member(string name,  string group): Username{name}, group{group}
    {}
    void write() const
    {
        Username::write();
        cout << "Member group: " << group << endl;

    }
private:
    string group;
};

int main()
{
    Username test01 {"Test user01"};
    Username* username {&test01};
    username->write();

    Member admin {"Test admin", "admin"};
    username = &admin;
    username->write();
}
