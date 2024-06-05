#include <iostream>

class Person {
private:
    std::string name;
    int age;

public:
    Person(std::string name, int age) : name(name), age(age) {} // Constructor

    void display() {
        std::cout << "Name: " << name << ", Age: " << age << std::endl;
    }
};

int main() {
    Person person("John", 30); // Create an object
    person.display(); // Call method
    return 0;
}
