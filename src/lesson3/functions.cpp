#include <iostream>
#include <vector>


using namespace std;

void value_func(vector<int> val) {
    val.push_back(999);
    cout << __PRETTY_FUNCTION__ << "\n";
}

void pointer_func(vector<int> *ptr) {
    ptr->push_back(999);
    cout << __PRETTY_FUNCTION__ << "\n";
}

void reference_func(vector<int> &ref) {
    ref.push_back(999);
    cout << __PRETTY_FUNCTION__ << "\n";
}

void const_reference_func(const vector<int> &ref) {
    // ref.push_back(999);
    for (auto &i: ref) {
        printf("%d ", i);
    }
    cout << "\n" << __PRETTY_FUNCTION__ << "\n";
}

int main() {
    vector<int> value_vector(100000, 1);
    auto *func_ptr = value_func;
    // auto *func_ptr = pointer_func;
    // auto *func_ptr = reference_func;
    // auto *func_ptr = const_reference_func;
    func_ptr(value_vector);
    cout << "Resuting value: " << value_vector.back() << endl;

}