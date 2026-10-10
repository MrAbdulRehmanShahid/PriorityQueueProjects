#include <iostream>
using namespace std;
// Book Request Node
struct BookRequestNode
{
    int studentID;
    string studentName;
    int bookID;
    string bookTitle;
    int priority;
    BookRequestNode* next;
};

// Priority Queue Class
class PriorityQueue
{
private:
    BookRequestNode* front;
    BookRequestNode* rear;
    int count;

public:
    // Constructor
    PriorityQueue()
    {
        front = nullptr;
        rear = nullptr;
        count = 0;
    }

    // Add request according to priority
    void Add(BookRequestNode* request)
    {
        request->next = nullptr;

        if (front == nullptr)
        {
            front = request;
            rear = request;
        }
        else if (request->priority < front->priority)
        {
            request->next = front;
            front = request;
        }
        else
        {
            BookRequestNode* current = front;

            while (current->next != nullptr &&
                   current->next->priority <= request->priority)
            {
                current = current->next;
            }

            request->next = current->next;
            current->next = request;

            if (request->next == nullptr)
            {
                rear = request;
            }
        }

        count++;
    }

    // Remove highest-priority request
    BookRequestNode* Remove()
    {
        if (front == nullptr)
        {
            return nullptr;
        }

        BookRequestNode* request = front;
        front = front->next;

        if (front == nullptr)
        {
            rear = nullptr;
        }

        request->next = nullptr;
        count--;

        return request;
    }

    // Check queue status
    bool IsEmpty()
    {
        return front == nullptr;
    }

    bool IsNotEmpty()
    {
        return front != nullptr;
    }

    // Display all requests
    void PrintQueue()
    {
        BookRequestNode* current = front;

        while (current != nullptr)
        {
            cout << "\nStudent ID: "
                 << current->studentID << endl;
            cout << "Student Name: "
                 << current->studentName << endl;
            cout << "Book ID: "
                 << current->bookID << endl;
            cout << "Book Title: "
                 << current->bookTitle << endl;
            cout << "Priority: "
                 << current->priority << endl;
            cout << "-----------------------------\n";

            current = current->next;
        }
    }

    // Copy Constructor: make a separate copy of each node
    PriorityQueue(const PriorityQueue& other)
    {
        front = nullptr;
        rear = nullptr;
        count = 0;

        BookRequestNode* current = other.front;

        while (current != nullptr)
        {
            BookRequestNode* newNode = new BookRequestNode;

            newNode->studentID = current->studentID;
            newNode->studentName = current->studentName;
            newNode->bookID = current->bookID;
            newNode->bookTitle = current->bookTitle;
            newNode->priority = current->priority;
            newNode->next = nullptr;

            Add(newNode);
            current = current->next;
        }
    }

    // Assignment Operator
    PriorityQueue& operator=(const PriorityQueue& other)
    {
        if (this == &other)
        {
            return *this;
        }

        // Delete current nodes
        while (front != nullptr)
        {
            BookRequestNode* temp = front;
            front = front->next;
            delete temp;
        }

        rear = nullptr;
        count = 0;

        // Copy nodes from the other queue
        BookRequestNode* current = other.front;

        while (current != nullptr)
        {
            BookRequestNode* newNode = new BookRequestNode;

            newNode->studentID = current->studentID;
            newNode->studentName = current->studentName;
            newNode->bookID = current->bookID;
            newNode->bookTitle = current->bookTitle;
            newNode->priority = current->priority;
            newNode->next = nullptr;

            Add(newNode);
            current = current->next;
        }

        return *this;
    }

    // Destructor
    ~PriorityQueue()
    {
        while (front != nullptr)
        {
            BookRequestNode* temp = front;
            front = front->next;
            delete temp;
        }

        rear = nullptr;
    }
};

// Create a new book request
BookRequestNode* CreateRequest(
    int studentID,
    string studentName,
    int bookID,
    string bookTitle,
    int priority)
{
    BookRequestNode* request = new BookRequestNode;

    request->studentID = studentID;
    request->studentName = studentName;
    request->bookID = bookID;
    request->bookTitle = bookTitle;
    request->priority = priority;
    request->next = nullptr;

    return request;
}

// Main Function
int main()
{
    PriorityQueue requests;
    int choice;

    do
    {
        cout << "\n===== Library Book Request System =====\n";
        cout << "1. Add Book Request\n";
        cout << "2. Process Highest Priority Request\n";
        cout << "3. Display All Requests\n";
        cout << "4. Check Queue Status\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";

        if (!(cin >> choice))
        {
            cout << "Invalid input. Please enter a number.\n";
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        switch (choice)
        {
            case 1:
            {
                int studentID, bookID, priority;
                string studentName, bookTitle;

                cout << "Enter Student ID: ";
                if (!(cin >> studentID))
                {
                    cout << "Invalid Student ID.\n";
                    cin.clear();
                    cin.ignore(10000, '\n');
                    break;
                }
                cin.ignore(10000, '\n');
                cout << "Enter Student Name: ";
                getline(cin, studentName);
                cout << "Enter Book ID: ";
                if (!(cin >> bookID))
                {
                    cout << "Invalid Book ID.\n";
                    cin.clear();
                    cin.ignore(10000, '\n');
                    break;
                }
                cin.ignore(10000, '\n');
                cout << "Enter Book Title: ";
                getline(cin, bookTitle);
                cout << "Enter Priority (1=Urgent, 2=Assignment, 3=Normal): ";
                if (!(cin >> priority))
                {
                    cout << "Invalid priority input.\n";
                    cin.clear();
                    cin.ignore(10000, '\n');
                    break;
                }
                if (priority < 1 || priority > 3)
                {
                    cout << "Priority must be 1, 2, or 3.\n";
                    break;
                }
                requests.Add(CreateRequest(
                    studentID, studentName,
                    bookID, bookTitle, priority));
                cout << "Book request added successfully.\n";
                break;
            }
            case 2:
            {
                BookRequestNode* processed = requests.Remove();
                if (processed == nullptr)
                {
                    cout << "Queue is empty. Nothing to process.\n";
                }
                else
                {
                    cout << "\n===== Processed Request =====\n";
                    cout << "Student ID: " << processed->studentID << endl;
                    cout << "Student Name: " << processed->studentName << endl;
                    cout << "Book ID: " << processed->bookID << endl;
                    cout << "Book Title: " << processed->bookTitle << endl;
                    cout << "Priority: " << processed->priority << endl;
                    delete processed;
                }
                break;
            }
            case 3:
                if (requests.IsEmpty())
                {
                    cout << "No pending requests.\n";
                }
                else
                {
                    cout << "\n===== All Pending Requests =====\n";
                    requests.PrintQueue();
                }
                break;
            case 4:
                if (requests.IsEmpty())
                {
                    cout << "Queue Status: EMPTY\n";
                }
                else if (requests.IsNotEmpty())
                {
                    cout << "Queue Status: NOT EMPTY\n";
                }
                break;

            case 5:
                cout << "Exiting the system...\n";
                break;
            default:
                cout << "Invalid choice. Select a number from 1 to 5.\n";
        }

    } while (choice != 5);

    return 0;
}

