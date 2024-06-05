#include <iostream>

int main() {
    int number = 10;
    int* ptr = &number; // Pointer to number

    std::cout << "Number: " << number << std::endl;
    std::cout << "Pointer Address: " << ptr << std::endl;
    std::cout << "Pointer Value: " << *ptr << std::endl; // Dereference pointer

    return 0;
}
