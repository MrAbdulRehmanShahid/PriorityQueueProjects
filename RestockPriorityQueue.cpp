#include <iostream>
using namespace std;
// Node for a warehouse restock request
struct RestockNode
{
    int itemID;
    string itemName;
    int quantityNeeded;
    int priority;
    RestockNode* next;
};
class RestockQueue
{
private:
    RestockNode* front;
    RestockNode* rear;
    int count;
public:
    RestockQueue()
    {
        front = NULL;
        rear = NULL;
        count = 0;
    }
    // Add a request according to priority
    void Add(RestockNode* request)
    {
        request->next = NULL;

        if (front == NULL)
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
            RestockNode* current = front;

            while (current->next != NULL &&
                   current->next->priority <= request->priority)
            {
                current = current->next;
            }

            request->next = current->next;
            current->next = request;

            if (request->next == NULL)
            {
                rear = request;
            }
        }

        count++;
    }
    RestockNode* Remove()
    {
        if (front == NULL)
        {
            return NULL;
        }

        RestockNode* request = front;
        front = front->next;

        if (front == NULL)
        {
            rear = NULL;
        }

        request->next = NULL;
        count--;

        return request;
    }
    bool IsEmpty()
    {
        return front == NULL;
    }
    bool IsNotEmpty()
    {
        return front != NULL;
    }

    // Display all restock requests
    void PrintQueue()
    {
        RestockNode* current = front;

        while (current != NULL)
        {
            cout << "\nItem ID: " << current->itemID << endl;
            cout << "Item Name: " << current->itemName << endl;
            cout << "Quantity Needed: "
                 << current->quantityNeeded << endl;
            cout << "Priority: " << current->priority;

            if (current->priority == 1)
            {
                cout << " (Critical Stock)";
            }
            else if (current->priority == 2)
            {
                cout << " (Low Stock)";
            }
            else
            {
                cout << " (Routine Restock)\n";
            }

            cout << "-----------------------------\n";

            current = current->next;
        }
    }

    // Destructor: release remaining nodes
    ~RestockQueue()
    {
        while (front != NULL)
        {
            RestockNode* temp = front;
            front = front->next;
            delete temp;
        }

        rear = NULL;
    }
};

// Create a restock request
RestockNode* CreateRestockRequest(
    int itemID,
    string itemName,
    int quantityNeeded,
    int priority)
{
    RestockNode* request = new RestockNode;

    request->itemID = itemID;
    request->itemName = itemName;
    request->quantityNeeded = quantityNeeded;
    request->priority = priority;
    request->next = NULL;

    return request;
}

// Main Function
int main()
{
    RestockQueue requests;
    int choice;

    do
    {
        cout << "\n===== Warehouse Restock System =====\n";
        cout << "1. Add Restock Request\n";
        cout << "2. Process Most Urgent Request\n";
        cout << "3. Display All Requests\n";
        cout << "4. Check Queue Status\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";

        if (!(cin >> choice))
        {
            cout << "Invalid input. Enter a number.\n";
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        switch (choice)
        {
            case 1:
            {
                int itemID, quantityNeeded, priority;
                string itemName;

                cout << "Enter Item ID: ";
                if (!(cin >> itemID))
                {
                    cout << "Invalid Item ID.\n";
                    cin.clear();
                    cin.ignore(10000, '\n');
                    break;
                }

                cin.ignore(10000, '\n');

                cout << "Enter Item Name: ";
                getline(cin, itemName);

                cout << "Enter Quantity Needed: ";
                if (!(cin >> quantityNeeded))
                {
                    cout << "Invalid quantity.\n";
                    cin.clear();
                    cin.ignore(10000, '\n');
                    break;
                }

                if (quantityNeeded <= 0)
                {
                    cout << "Quantity must be greater than zero.\n";
                    break;
                }

                cout << "Priority (1=Critical, 2=Low, 3=Routine): ";

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

                requests.Add(CreateRestockRequest(
                    itemID, itemName, quantityNeeded, priority));

                cout << "Restock request added successfully.\n";
                break;
            }

            case 2:
            {
                RestockNode* processed = requests.Remove();

                if (processed == NULL)
                {
                    cout << "No restock requests to process.\n";
                }
                else
                {
                    cout << "\n===== Request Being Processed =====\n";
                    cout << "Item ID: " << processed->itemID << endl;
                    cout << "Item Name: " << processed->itemName << endl;
                    cout << "Quantity Needed: "<< processed->quantityNeeded << endl;
                    cout << "Priority: " << processed->priority << endl;
                    delete processed;
                }
                break;
            }
            case 3:
                if (requests.IsEmpty())
                {
                    cout << "No pending restock requests.\n";
                }
                else
                {
                    cout << "\n===== Pending Restock Requests =====\n";
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
                cout << "Exiting Warehouse Restock System...\n";
                break;
            default:
                cout << "Invalid choice. Select a number from 1 to 5.\n";
        }
    } while (choice != 5);
    return 0;
}
