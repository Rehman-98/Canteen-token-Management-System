#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <fstream>

using namespace std;

struct Order
{
    int token;
    string items;
    int totalBill;
};

queue<Order> orders;
stack<Order> servedOrders;

string food[5] =
{
    "Burger",
    "Pizza",
    "Fries",
    "Biryani",
    "Cold Drink"
};

int price[5] = {250, 500, 150, 300, 100};
int foodCount[5] = {0};

int tokenNumber = 1;

// Save active orders
void saveOrderToFile(Order customer)
{
    ofstream file("orders.txt", ios::app);

    if(file.is_open())
    {
        file << customer.token << "|"
             << customer.items << "|"
             << customer.totalBill
             << endl;

        file.close();
    }
}

// Save served customers
void saveServedToFile(Order customer)
{
    ofstream file("served.txt", ios::app);

    if(file.is_open())
    {
        file << customer.token << "|"
             << customer.items << "|"
             << customer.totalBill
             << endl;

        file.close();
    }
}

void showMenu()
{
    cout << "\n========== FOOD MENU ==========\n";

    for(int i = 0; i < 5; i++)
    {
        cout << i + 1
             << ". "
             << food[i]
             << " - Rs. "
             << price[i]
             << endl;
    }
}

void buyToken()
{
    Order customer;

    customer.token = tokenNumber++;
    customer.totalBill = 0;
    customer.items = "";

    char more = 'y';

    while(more == 'y' || more == 'Y')
    {
        int choice, qty;

        showMenu();

        cout << "\nEnter Food Choice: ";
        cin >> choice;

        if(choice < 1 || choice > 5)
        {
            cout << "\nInvalid Choice\n";
            continue;
        }

        cout << "Enter Quantity: ";
        cin >> qty;

        customer.items += food[choice - 1];
        customer.items += " ";

        customer.totalBill += price[choice - 1] * qty;

        // Count quantity for recommendation
        foodCount[choice - 1] += qty;

        cout << "\nDo You Want To Buy Another Item? (y/n): ";
        cin >> more;
    }

    orders.push(customer);

    saveOrderToFile(customer);

    cout << "\n========== TOKEN GENERATED ==========\n";
    cout << "Token Number : " << customer.token << endl;
    cout << "Total Bill   : Rs. " << customer.totalBill << endl;
}

void viewActiveTokens()
{
    if(orders.empty())
    {
        cout << "\nNo Active Tokens\n";
        return;
    }

    queue<Order> temp = orders;

    cout << "\n========== ACTIVE TOKENS ==========\n";

    while(!temp.empty())
    {
        Order customer = temp.front();

        cout << "Token : "
             << customer.token
             << " | Items : "
             << customer.items
             << " | Bill : Rs. "
             << customer.totalBill
             << endl;

        temp.pop();
    }
}

void searchToken()
{
    int token;
    bool found = false;

    cout << "\nEnter Token Number: ";
    cin >> token;

    queue<Order> temp = orders;

    while(!temp.empty())
    {
        Order customer = temp.front();

        if(customer.token == token)
        {
            cout << "\n========== TOKEN FOUND ==========\n";

            cout << "Token Number : "
                 << customer.token
                 << endl;

            cout << "Items : "
                 << customer.items
                 << endl;

            cout << "Bill : Rs. "
                 << customer.totalBill
                 << endl;

            found = true;
            break;
        }

        temp.pop();
    }

    if(found == false)
    {
        cout << "\nToken Not Found\n";
    }
}

void serveCustomer()
{
    if(orders.empty())
    {
        cout << "\nNo Customers Waiting\n";
        return;
    }

    Order customer = orders.front();

    cout << "\n========== SERVING CUSTOMER ==========\n";

    cout << "Token Number : "
         << customer.token
         << endl;

    cout << "Items : "
         << customer.items
         << endl;

    cout << "Bill : Rs. "
         << customer.totalBill
         << endl;

    servedOrders.push(customer);

    saveServedToFile(customer);

    orders.pop();
}

void viewServedCustomers()
{
    if(servedOrders.empty())
    {
        cout << "\nNo Served Customers Yet\n";
        return;
    }

    stack<Order> temp = servedOrders;

    cout << "\n========== SERVED CUSTOMERS ==========\n";

    while(!temp.empty())
    {
        Order customer = temp.top();

        cout << "Token : "
             << customer.token
             << " | Items : "
             << customer.items
             << " | Bill : Rs. "
             << customer.totalBill
             << endl;

        temp.pop();
    }
}

void aiRecommendation()
{
    int best = 0;

    for(int i = 1; i < 5; i++)
    {
        if(foodCount[i] > foodCount[best])
        {
            best = i;
        }
    }

    cout << "\n========== AI FOOD RECOMMENDATION ==========\n";

    cout << "Recommended Item : "
         << food[best]
         << endl;

    cout << "Reason : Most Frequently Ordered Item\n";
}

void viewOrdersFile()
{
    ifstream file("orders.txt");

    string line;

    cout << "\n========== ORDERS FILE ==========\n";

    while(getline(file, line))
    {
        cout << line << endl;
    }

    file.close();
}

void viewServedFile()
{
    ifstream file("served.txt");

    string line;

    cout << "\n========== SERVED FILE ==========\n";

    while(getline(file, line))
    {
        cout << line << endl;
    }

    file.close();
}

int main()
{
    int choice;

    do
    {
        cout << "\n=====================================\n";
        cout << " CANTEEN TOKEN MANAGEMENT SYSTEM\n";
        cout << "=====================================\n";

        cout << "1. View Menu\n";
        cout << "2. Buy Token\n";
        cout << "3. View Active Tokens\n";
        cout << "4. Search Token Number\n";
        cout << "5. Serve Customer\n";
        cout << "6. View Served Customers\n";
        cout << "7. AI Food Recommendation\n";
        cout << "8. View Orders File\n";
        cout << "9. View Served File\n";
        cout << "10. Exit\n";

        cout << "\nEnter Choice: ";
        cin >> choice;

        switch(choice)
        {
            case 1:
                showMenu();
                break;

            case 2:
                buyToken();
                break;

            case 3:
                viewActiveTokens();
                break;

            case 4:
                searchToken();
                break;

            case 5:
                serveCustomer();
                break;

            case 6:
                viewServedCustomers();
                break;

            case 7:
                aiRecommendation();
                break;

            case 8:
                viewOrdersFile();
                break;

            case 9:
                viewServedFile();
                break;

            case 10:
                cout << "\nThank You For Using The System\n";
                break;

            default:
                cout << "\nInvalid Choice\n";
        }

    } while(choice != 10);

    return 0;
}