#include <chrono>
#include <iostream>
#include <thread>
#include <mutex>


void foo(int param)
{
    // simulate expensive operation
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "param: " << param << std::endl;
    std::cout << std::this_thread::get_id() << std::endl;
}


void bar()
{
    // simulate expensive operation
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << std::this_thread::get_id() << std::endl;
}

// RAII resource acquation is initialization
void example_jthread() {
    std::thread t([](){
        while (true) {
            std::string input;
            std::cin >> input;
            if (input == "stop")
                break;
        }
    });
    std::cout << "print 1\n";
    std::cout << "print 2\n";
    t.join();
}

void example_1() {
    std::cout << "starting first helper...\n";
    std::thread helper1(foo, 1337);
 
    std::cout << "starting second helper...\n";
    std::thread helper2(bar);
    // bad function -> boom
    std::cout << "waiting for helpers to finish..." << std::endl;
    helper1.join();
    helper2.join();
 
    std::cout << "done!\n";
}


void example_2() {
    unsigned long long g_count = 0;
    std::mutex m1; 
    // mutual exclusion

    

    std::thread t1([&]()
    {
        for(auto i = 0; i < 1'000'000; ++i) {
            std::lock_guard<std::mutex> lg(m1);
            ++g_count;
        }
            
    });
    
    std::thread t2([&]()
    {
        for(auto i = 0; i < 1'000'000; ++i) {
            std::lock_guard<std::mutex> lg(m1);
            ++g_count;
        }
    });
    
    t1.join();
    t2.join();
    
    std::cout << g_count << std::endl;
}


int main()
{
    // example_1();
    example_2();
    // example_jthread();

}