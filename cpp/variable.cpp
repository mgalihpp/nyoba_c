#include <iostream>

int main()
{
    int age = 25;          // Integer variable
    double height = 5.9;   // Double variable
    char initial = 'J';    // Character variable
    bool isStudent = true; // Boolean variable

    std::cout << "Age: " << age << std::endl;
    std::cout << "Height: " << height << std::endl;
    std::cout << "Initial: " << initial << std::endl;
    std::cout << "Is Student: " << std::boolalpha << isStudent << std::endl;

    return 0;
}
