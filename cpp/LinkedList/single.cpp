#include <iostream>

using namespace std;

struct Buku
{
    string judul, pengarang;
    int tahunTerbit;

    Buku *next;
};

Buku *head, *tail, *cur;

int getLength()
{
    int length = 0;
    Buku *current = head;
    while (current != nullptr)
    {
        length++;
        current = current->next;
    }
    return length;
}

void CreateSingleLinkedList(string judul, string pengarang, int Tb)
{
    head = new Buku();
    head->judul = judul;
    head->pengarang = pengarang;
    head->tahunTerbit = Tb;
    head->next = NULL;
    tail = head;
}

void PrintSingleLinkedList()
{
    cur = head;
    while (cur != NULL)
    {
        cout << "Judul Buku : " << cur->judul << endl;
        cout << "Pengarang : " << cur->pengarang << endl;
        cout << "Tahun Terbit : " << cur->tahunTerbit << endl;
        cur = cur->next;

        
        cout << "" << endl;
    }
}

void insertFirst(string judul, string pengarang, int Tb)
{
    Buku *newNode = new Buku();
    newNode->judul = judul;
    newNode->pengarang = pengarang;
    newNode->tahunTerbit = Tb;
    newNode->next = head;
    head = newNode;
};

void insertLast(string judul, string pengarang, int Tb)
{
    Buku *newNode = new Buku();
    newNode->judul = judul;
    newNode->pengarang = pengarang;
    newNode->tahunTerbit = Tb;
    newNode->next = NULL;
    tail->next = newNode;
    tail = newNode;
}

void InsertMiddle(string judul, string pengarang, int Tb)
{
    Buku *newNode = new Buku();
    newNode->judul = judul;
    newNode->pengarang = pengarang;
    newNode->tahunTerbit = Tb;

    int dataLength = getLength() / 2;

    cur = head;
    int count = 1;
    while (count < dataLength && cur != NULL)
    {
        cur = cur->next;
        count++;
    }

    if (cur != NULL)
    {
        newNode->next = cur->next;
        cur->next = newNode;
        if (newNode->next == NULL)
        {
            tail = newNode;
        }
    }
    else
    {
        cout << "The previous node is null." << endl;
    }
}

int main()
{
    CreateSingleLinkedList("The Lord of the Rings", "J.R.R. Tolkien", 1954);
    insertFirst("Harry Potter", "J.K. Rowling", 1997);
    insertFirst("Ini testing", "mgalihpp", 2024);
    insertLast("The World of Ice and Fire", "George R.R. Martin", 1974);

    PrintSingleLinkedList();

    cout << "--------------------------" << endl;

    cout << "Memasukkan buku baru ditengah..." << endl;
    InsertMiddle("Cinco de Mayo", "Miguel de Cervantes", 1610);
    PrintSingleLinkedList();

    cout << "--------------------------" << endl;

    return 0;
}
