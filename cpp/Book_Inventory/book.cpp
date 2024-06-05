#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <stdexcept>

class Book
{
private:
    std::string title;
    std::string author;
    double price;
    int quantity;

public:
    Book(std::string title, std::string author, double price, int quantity)
        : title(title), author(author), price(price), quantity(quantity){};

    void display() const
    {
        std::cout << 'Title' << title
                  << ', Author' << author
                  << ', Price' << price
                  << ', Quantity' << quantity
                  << std::endl;
    };

    std::string getTitle() const { return title; };
    std::string getAuthor() const { return author; };
    double getPrice() const { return price; };
    int getQuantity() const { return quantity; };

    void setQuantity(int quantity) { this->quantity = quantity; };
};