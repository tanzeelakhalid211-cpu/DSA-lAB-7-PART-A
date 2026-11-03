#include <iostream>
#include <string>
using namespace std;

struct dNode
{
    int bookID;
    string title;
    dNode* left;
    dNode* right;

    dNode(int id, string name)
    {
        bookID = id;
        title = name;
        left = nullptr;
        right = nullptr;
    }
};

class DoublyLinkedList
{
private:
    dNode* head;
    dNode* tail;
    dNode* current;

public:
    DoublyLinkedList()
    {
        head = tail = current = nullptr;
    }

    // Insert at the end
    void InsertRight(dNode* node)
    {
        if (node == nullptr)
            return;

        node->left = tail;
        node->right = nullptr;

        if (tail != nullptr)
            tail->right = node;
        else
            head = node;

        tail = node;

        if (current == nullptr)
            current = node;
    }

    // Move to next book
    void Next()
    {
        if (current != nullptr && current->right != nullptr)
            current = current->right;
        else
            cout << "No next book!\n";
    }

    // Move to previous book
    void Previous()
    {
        if (current != nullptr && current->left != nullptr)
            current = current->left;
        else
            cout << "No previous book!\n";
    }

    // Display current book
    void PrintCurrent()
    {
        if (current == nullptr)
        {
            cout << "Session is empty!\n";
            return;
        }

        cout << "Current Book: "
             << current->bookID << " - "
             << current->title << endl;
    }

    // Insert after current
    void InsertAfterCurrent(dNode* node)
    {
        if (node == nullptr)
            return;

        if (current == nullptr)
        {
            InsertRight(node);
            return;
        }

        node->left = current;
        node->right = current->right;

        if (current->right != nullptr)
            current->right->left = node;
        else
            tail = node;

        current->right = node;
    };

    // Remove current book
    dNode* RemoveCurrent()
    {
        if (current == nullptr)
            return nullptr;

        dNode* removed = current;
        dNode* previous = current->left;
        dNode* next = current->right;

        if (previous != nullptr)
            previous->right = next;
        else
            head = next;

        if (next != nullptr)
            next->left = previous;
        else
            tail = previous;

        current = (next != nullptr) ? next : previous;

        removed->left = nullptr;
        removed->right = nullptr;

        return removed;
    }

    // Display forward
    void PrintForward()
    {
        if (head == nullptr)
        {
            cout << "Session is empty!\n";
            return;
        }

        cout << "\nBooks from First to Last:\n";

        for (dNode* node = head; node != nullptr;
             node = node->right)
        {
            cout << node->bookID << " - "
                 << node->title;

            if (node == current)
                cout << " [CURRENT]";

            cout << endl;
        }
    }

    // Display backward
    void PrintBackward()
    {
        if (tail == nullptr)
        {
            cout << "Session is empty!\n";
            return;
        }

        cout << "\nBooks from Last to First:\n";

        for (dNode* node = tail; node != nullptr;
             node = node->left)
        {
            cout << node->bookID << " - "
                 << node->title;

            if (node == current)
                cout << " [CURRENT]";

            cout << endl;
        }
    }

    // Destructor
    ~DoublyLinkedList()
    {
        dNode* node = head;

        while (node != nullptr)
        {
            dNode* next = node->right;
            delete node;
            node = next;
        }
    }
};

int main()
{
    DoublyLinkedList session;

    // Initial books
    session.InsertRight(new dNode(101, "Data Structures"));
    session.InsertRight(new dNode(102, "Database Systems"));
    session.InsertRight(new dNode(103, "Operating Systems"));

    int choice, id;
    string title;

    do
    {
        cout << "\n===== LIBRARY BORROWING SYSTEM =====\n";
        cout << "1. Display Current Book\n";
        cout << "2. Move to Next Book\n";
        cout << "3. Move to Previous Book\n";
        cout << "4. Insert Book at the End\n";
        cout << "5. Insert Book After Current Book\n";
        cout << "6. Remove Current Book\n";
        cout << "7. Display Session First to Last\n";
        cout << "8. Display Session Last to First\n";
        cout << "9. Exit\n";

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            session.PrintCurrent();
            break;

        case 2:
            session.Next();
            session.PrintCurrent();
            break;

        case 3:
            session.Previous();
            session.PrintCurrent();
            break;

        case 4:
            cout << "Enter Book ID: ";
            cin >> id;

            cin.ignore();

            cout << "Enter Book Title: ";
            getline(cin, title);

            session.InsertRight(new dNode(id, title));
            cout << "Book inserted successfully!\n";
            break;

        case 5:
            cout << "Enter Book ID: ";
            cin >> id;

            cin.ignore();

            cout << "Enter Book Title: ";
            getline(cin, title);

            session.InsertAfterCurrent(new dNode(id, title));
            cout << "Book inserted after current book!\n";
            break;

        case 6:
        {
            dNode* removed = session.RemoveCurrent();

            if (removed != nullptr)
            {
                cout << "Removed Book: "
                     << removed->title << endl;

                delete removed;
            }
            else
                cout << "No book to remove!\n";

            break;
        }

        case 7:
            session.PrintForward();
            break;

        case 8:
            session.PrintBackward();
            break;

        case 9:
            cout << "Exiting Library System...\n";
            break;

        default:
            cout << "Invalid choice!\n";
        }

    } while (choice != 9);

    return 0;
}
