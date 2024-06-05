#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <stdexcept>
#include "book.cpp"

class Inventory
{
private:
    std::vector<std::shared_ptr<Book>> books;

public:
    void addBook(const std::shared_ptr<Book> &book)
    {
        books.push_back(book);
    };

    void display() const
    {
        for (const auto &book : books)
        {
            book->display();
        }
    }

    void saveToFile(const std::string &filename) const
    {
        std::ofstream file(filename);

        if (!file)
        {
            throw std::runtime_error("Unable to open file for writing");
        }

        for (const auto &book : books)
        {
            file << book->getTitle() << "\n"
                 << book->getAuthor() << "\n"
                 << book->getPrice() << "\n"
                 << book->getQuantity() << "\n";
        };

        file.close();
    };

    void loadFromFile(const std::string &filename)
    {
        std::ifstream file(filename);

        if (!file)
        {
            throw std::runtime_error("Unable to open file for reading");
        }

        books.clear();

        std::string title, author;
        double price;
        int quantity;

        while (file >> std::ws && std::getline(file, title) && std::getline(file, author) && file >> price >> quantity)
        {
            file.ignore();
            books.push_back(std::make_shared<Book>(title, author, price, quantity));
        }
        file.close();
    }
};