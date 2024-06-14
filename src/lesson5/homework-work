class Foo {
public:
    Foo() {}
    int cnt = 1;
    std::mutex m;
    void first(function<void()> printFirst) {

        // printFirst() outputs "first". Do not change or remove this line.
        printFirst();
    }

    void second(function<void()> printSecond) {
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        // printSecond() outputs "second". Do not change or remove this line.
        printSecond();
    }

    void third(function<void()> printThird) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        // printThird() outputs "third". Do not change or remove this line.
        printThird();
    }
};
