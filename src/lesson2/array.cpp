#include <iostream>

// new / delete
// malloc, calloc, realloc / free

int global_stack_array[10];

int size = 10;
int *global_heap_array = new int[size];
int *size_addr = &size;
int &size_ref = size;

static int global_static_array[10];


// by value
// by reference 
// by pointer
void change_local_array(int *temp) {
    temp[0] = -1;
    static int a = 0;
    a++;
}

void foo() {
    int local = 1;
    int array[8000];
}

// array[10]
// array ... 0 1 2 3



int main() {

    int a = 100;
    // std::cin >> a;
    int *local_heap_array = new int[a];
    // for (int element = 0; element < a; element++) {
    //     local_heap_array[element] = 1337;
    // }

    // for (int element = 0; element < a; element++) {
    //     std::cout << local_heap_array[element] << std::endl;
    // }

    // int local_stack_array[3] = {1,2,3};

    // change_local_array(local_stack_array);
    // std::cout << local_stack_array[0] << std::endl;
    delete[] local_heap_array;
    delete[] global_heap_array;
    // foo();
}