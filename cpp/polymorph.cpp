#include <iostream>

class Animal {
public:
    virtual void speak() { // Virtual function
        std::cout << "Animal speaks" << std::endl;
    }
};

class Dog : public Animal {
public:
    void speak() override { // Override function
        std::cout << "Dog barks" << std::endl;
    }
};

int main() {
    Animal* animal = new Dog(); // Polymorphism
    animal->speak(); // Calls Dog's speak method

    delete animal;
    return 0;
}
