#include <iostream>
#include <string>
#include <limits>
using namespace std;

class ConservationWork
{
private:
    int workID;
    string siteName;
    string workType;
    string workDate;
    double cost;
    string status;

    static int totalRecords;

public:

    // Inline function
    inline void displayID()
    {
        cout << "Work ID: " << workID << endl;
    }

    // Function to enter record details
    void addRecord(int id)
    {
        this->workID = id;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Enter Heritage Site Name: ";
        getline(cin, this->siteName);

        cout << "Enter Conservation Work Type: ";
        getline(cin, this->workType);

        cout << "Enter Work Date (DD-MM-YYYY): ";
        getline(cin, this->workDate);

        do
        {
            cout << "Enter Estimated Cost: ";
            cin >> this->cost;

            if (cin.fail() || this->cost < 0)
            {
                cout << "Invalid cost. Try again.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                this->cost = -1;
            }

        } while (this->cost < 0);

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Enter Status (Pending/In Progress/Completed): ";
        getline(cin, this->status);

        totalRecords++;

        cout << "\nRecord added successfully!\n";
    }

    // Friend function
    friend void displayRecord(const ConservationWork &obj);

    // Static function
    static void showTotalRecords()
    {
        cout << "\nTotal Records: " << totalRecords << endl;
    }

    // Function to get Work ID
    int getID()
    {
        return workID;
    }
};

// Static member definition
int ConservationWork::totalRecords = 0;

// Friend function definition
void displayRecord(const ConservationWork &obj)
{
    cout << "\n-----------------------------------\n";

    cout << "Work ID: " << obj.workID << endl;
    cout << "Heritage Site: " << obj.siteName << endl;
    cout << "Work Type: " << obj.workType << endl;
    cout << "Work Date: " << obj.workDate << endl;
    cout << "Estimated Cost: Rs. " << obj.cost << endl;
    cout << "Status: " << obj.status << endl;

    cout << "-----------------------------------\n";
}

int main()
{
    const int MAX = 100;

    // Array of objects
    ConservationWork records[MAX];

    // Pointer to objects
    ConservationWork *ptr = records;

    int choice;
    int id;
    int count = 0;
    bool found;

    do
    {
        cout << "\n====================================\n";
        cout << " HERITAGE SITE CONSERVATION WORK LOG\n";
        cout << "====================================\n";

        cout << "1. Add New Conservation Work\n";
        cout << "2. View All Records\n";
        cout << "3. Search Record\n";
        cout << "4. Show Total Records\n";
        cout << "5. Exit\n";

        cout << "\nEnter your choice: ";
        cin >> choice;

        if (cin.fail())
        {
            cout << "Invalid choice. Enter a number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (choice)
        {
            case 1:

                if (count >= MAX)
                {
                    cout << "Record storage is full!\n";
                    break;
                }

                cout << "Enter Work ID: ";
                cin >> id;

                if (cin.fail() || id <= 0)
                {
                    cout << "Invalid Work ID.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                }

                found = false;

                // Check duplicate Work ID
                for (int i = 0; i < count; i++)
                {
                    if (ptr[i].getID() == id)
                    {
                        found = true;
                        break;
                    }
                }

                if (found)
                {
                    cout << "Work ID already exists!\n";
                }
                else
                {
                    ptr[count].addRecord(id);
                    count++;
                }

                break;

            case 2:

                if (count == 0)
                {
                    cout << "\nNo records available.\n";
                }
                else
                {
                    cout << "\nALL CONSERVATION RECORDS\n";

                    for (int i = 0; i < count; i++)
                    {
                        displayRecord(ptr[i]);
                    }
                }

                break;

            case 3:

                cout << "Enter Work ID to search: ";
                cin >> id;

                if (cin.fail())
                {
                    cout << "Invalid Work ID.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                }

                found = false;

                for (int i = 0; i < count; i++)
                {
                    if (ptr[i].getID() == id)
                    {
                        cout << "\nRecord Found!\n";
                        displayRecord(ptr[i]);
                        found = true;
                        break;
                    }
                }

                if (!found)
                {
                    cout << "\nRecord not found!\n";
                }

                break;

            case 4:

                ConservationWork::showTotalRecords();
                break;

            case 5:

                cout << "\nThank you for using the system!\n";
                break;

            default:

                cout << "\nInvalid choice. Try again.\n";
        }

    } while (choice != 5);

    return 0;
}
