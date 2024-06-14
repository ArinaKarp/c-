class Foo {
public:
    Foo() {}
    std::mutex m1;

    std::thread first(function<void()> printFirst) {
        std::lock_guard<std::mutex> lg(m1);
        // printFirst() outputs "first". Do not change or remove this line.
        printFirst();
    }
    first.join();
    std::thread second(function<void()> printSecond) {
  
        std::lock_guard<std::mutex> lg(m1);
        // printSecond() outputs "second". Do not change or remove this line.
        printSecond();
    }

    std::thread third(function<void()> printThird) {
        second.join();
        // printThird() outputs "third". Do not change or remove this line.
        printThird();
    }
};
