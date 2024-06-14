#include <iostream>

using namespace std;

struct DataUser
{
    string name, username, email, password;
    DataUser *prev;
    DataUser *next;
};

DataUser *head, *tail, *cur, *newNode, *del;

int getLength()
{
    int length = 0;
    cur = head;
    while (cur != NULL)
    {
        length++;
        cur = cur->next;
    }
    return length;
}

// Fungsi untuk membuat linked list
void createDoubleLinkedList(string name, string username, string email, string password)
{
    head = new DataUser();
    head->name = name;
    head->username = username;
    head->email = email;
    head->password = password;
    head->prev = NULL;
    head->next = NULL;
    tail = head;
}

void printDoubleLinkedList()
{
    if (head == NULL)
    {
        cout << "Linked List Kosong" << endl;
        return;
    }
    else
    {
        cout << "Isi Data" << endl;
        cur = head;

        while (cur != NULL)
        {

            cout << "Nama user : " << cur->name << endl;
            cout << "Username : " << cur->username << endl;
            cout << "Email : " << cur->email << endl;
            cout << "Password :" << cur->password << "\n"
                 << endl;
            cur = cur->next;
        }
    }
}

void insertFirst(string name, string username, string email, string password)
{
    newNode = new DataUser();
    newNode->name = name;
    newNode->username = username;
    newNode->email = email;
    newNode->password = password;
    newNode->prev = NULL;
    newNode->next = head;
    head->prev = newNode;
    head = newNode;
}

void insertLast(string name, string username, string email, string password)
{
    if (head == NULL)
    {
        cout << "Double Linked List Kosong" << endl;
        return;
    }
    else
    {
        newNode = new DataUser();
        newNode->name = name;
        newNode->username = username;
        newNode->email = email;
        newNode->password = password;
        newNode->prev = tail;
        newNode->next = NULL;
        tail->next = newNode;
        tail = newNode;
    }
}

void insertMiddle(string name, string username, string email, string password)
{
    int dataLength = getLength();

    if (dataLength == 0)
    {
        cout << "Double Linked List Kosong" << endl;
        return;
    }

    int middlePosition = dataLength / 2;

    newNode = new DataUser();
    newNode->name = name;
    newNode->username = username;
    newNode->email = email;
    newNode->password = password;

    cur = head;
    for (int i = 0; i < middlePosition - 1; i++)
    {
        cur = cur->next;
    };

    newNode->next = cur->next;
    newNode->prev = cur;

    if (cur->next != NULL)
    {
        cur->next->prev = newNode;
    }

    cur->next = newNode;

    if (newNode->next == NULL)
    {
        tail = newNode;
    }
}

int main()
{
    createDoubleLinkedList("Muhamad Iqbal", "muhamadiqbal", "X1wKs@example.com", "muhamad123");
    insertFirst("Ahmad Fauzi", "ahmadfauzi", "ahmad@gmail.com.com", "ahmad123");
    insertFirst("Dadang Ramadhan", "dadangramadhan", "dadang@gmail.com", "dadang123");
    insertLast("Wawan Setiawan", "wawansetiawan", "wawan@gmail.com", "wawan123");

    printDoubleLinkedList();

    cout << "--------------------------" << "\n\n"
         << endl;

    cout
        << "Memasukkan Data user ditengah..." << "\n"
        << endl;

    insertMiddle("muhammadgalih", "mgalihpp", "mgalihpp@gmail.com", "galih123");

    printDoubleLinkedList();
}