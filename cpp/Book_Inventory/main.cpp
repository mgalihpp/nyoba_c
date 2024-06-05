#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <stdexcept>
#include "inventory.cpp"

int main()
{
    Inventory inventory;

    // Adding some books to the inventory
    inventory.addBook(std::make_shared<Book>("The Great Gatsby", "F. Scott Fitzgerald", 10.99, 5));
    inventory.addBook(std::make_shared<Book>("1984", "George Orwell", 8.99, 10));
    inventory.addBook(std::make_shared<Book>("To Kill a Mockingbird", "Harper Lee", 12.99, 7));

    // Display the current inventory
    std::cout << "Current Inventory:" << std::endl;
    inventory.display();

    // save the inventory file
    std::string filename = "inventory.txt";
    try
    {
        inventory.saveToFile(filename);
        std::cout << "Inventory saved to" << filename << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error saving inventory" << e.what() << std::endl;
    };

    // Load the inventory from the file
    try
    {
        inventory.loadFromFile(filename);
        std::cout << "Inventory loaded from " << filename << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error loading inventory: " << e.what() << std::endl;
    }

    // Display the loaded inventory
    std::cout << "Loaded Inventory:" << std::endl;
    inventory.display();

    return 0;
}