#include <iostream>
#include <vector>


template <class T>
T max(T x, T y) {
    return x > y ? x : y;
}

int main() {
    std::cout << max(1, 2) << std::endl;
    std::cout << max(1.0, 1.5) << std::endl;

    int number = 0; 
    int *pointer = nullptr;
    auto l1 = [](){
        return 1;
    };
    auto l2 = []() {
        return 2;
    };
    auto lambda = [&](int param){
        number += param; 
        std::cout << "I'm lambda\n";
        return number;
    };
    std::cout << lambda(5) << std::endl;
    std::cout << number << std::endl;

    // std::cout << max(l1(), l2()) << std::endl;
    // std::vector<int> vec;
    // for (const auto &i: vec) {
    //     // do smth with i
    // }
}