#include <iomanip>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

using namespace std;

// kada customer may name at id
struct Customer {
    int id;
    string name;
    string contactNumber;
};

struct Service {
    string name;
    double ratePerKilo;
};

struct LaundryOrder {
    int id;
    int customerID;
    string serviceName;
    double weight;
    double totalBill;
    string dateReceived;
    string pickupDate;
    string status;
};

// stored in memory lang to, wala agad yan pag nag-exit ka sa program
vector<Customer> customers;
vector<LaundryOrder> orders;
//preset values
vector<Service> services = {
    {"Wash and Fold", 50.00},
    {"Wash and Iron", 70.00},
    {"Dry Cleaning", 100.00}
};

int nextCustomerID = 1;
int nextOrderID = 1;

// Function declarations
void clearTerminal();
bool readInput(const string& prompt, string& input);
string getRequiredText(const string& prompt);
int getInteger(const string& prompt, int minimum, int maximum);
double getPositiveNumber(const string& prompt);
int findCustomerIndex(int customerID);
int findOrderIndex(int orderID);
void addCustomer();
void viewCustomers();
void deleteCustomer();
void showServices();
void editServiceRates();
void createOrder();
void displayOrders();
void printReceipt();
void showMainMenu();

int main() {
    int choice;

    do {
        showMainMenu();
        choice = getInteger("Choose an option: ", 0, 7);

        // Stop cleanly if the input stream closes; Q simply shows the menu again.
        if (choice == -1) {
            if (!cin) {
                break;
            }
            continue;
        }

        switch (choice) {
            case 1:
                addCustomer();
                break;
            case 2:
                viewCustomers();
                break;
            case 3:
                deleteCustomer();
                break;
            case 4:
                createOrder();
                break;
            case 5:
                displayOrders();
                break;
            case 6:
                printReceipt();
                break;
            case 7:
                editServiceRates();
                break;
            case 0:
                clearTerminal();
                cout << "Goodbye! Data is not saved and will be lost when the program closes.\n";
                break;
        }
    } while (choice != 0);

    return 0;
}

// Function definitions
void clearTerminal() {
    system("cls");

}

// Every input helper uses this reader so Q works at every prompt.
bool readInput(const string& prompt, string& input) {
    cout << prompt;

    if (!getline(cin, input)) {
        return false;
    }

    if (input == "q" || input == "Q") {
        clearTerminal();
        cout << "Input cancelled. Returning to the main menu.\n";
        return false;
    }

    return true;
}

string getRequiredText(const string& prompt) {
    string value;

    while (true) {
        // Empty string means cancelled; a blank entry is still rejected below.
        if (!readInput(prompt, value)) {
            return "";
        }

        if (!value.empty()) {
            return value;
        }

        cout << "This field cannot be empty. Please try again.\n";
    }
}

int getInteger(const string& prompt, int minimum, int maximum) {
    string input;

    while (true) {
        if (!readInput(prompt, input)) {
            return -1;
        }

        try {
            size_t charactersRead = 0;
            int value = stoi(input, &charactersRead);
            bool wholeInputIsNumber = charactersRead == input.length();

            if (wholeInputIsNumber && value >= minimum && value <= maximum) {
                return value;
            }
        } catch (...) {
            // Show the same message for non-numeric and out-of-range input.
        }

        cout << "Enter a whole number from " << minimum
             << " to " << maximum << ".\n";
    }
}

double getPositiveNumber(const string& prompt) {
    string input;

    while (true) {
        if (!readInput(prompt, input)) {
            return -1;
        }

        try {
            size_t charactersRead = 0;
            double value = stod(input, &charactersRead);
            bool wholeInputIsNumber = charactersRead == input.length();

            if (wholeInputIsNumber && value > 0) {
                return value;
            }
        } catch (...) {
            // Ask again if the input cannot be converted to a number.
        }

        cout << "Enter a number greater than zero.\n";
    }
}
int findCustomerIndex(int customerID) {
    for (int index = 0; index < static_cast<int>(customers.size()); index++) {
        if (customers[index].id == customerID) {
            return index;
        }
    }

    return -1;
}

int findOrderIndex(int orderID) {
    for (int index = 0; index < static_cast<int>(orders.size()); index++) {
        if (orders[index].id == orderID) {
            return index;
        }
    }

    return -1;
}

void addCustomer() {
    clearTerminal();
    Customer customer;
    customer.name = getRequiredText("Customer name (Q to cancel): ");
    if (customer.name.empty()) {
        return;
    }

    customer.contactNumber = getRequiredText("Contact number (Q to cancel): ");
    if (customer.contactNumber.empty()) {
        return;
    }

    customer.id = nextCustomerID;
    customers.push_back(customer);
    nextCustomerID++;
    clearTerminal();
    cout << "Customer added. Customer ID: " << customer.id << "\n";
}

void viewCustomers() {
    clearTerminal();
    if (customers.empty()) {
        cout << "There are no customer records.\n";
        return;
    }

    cout << "\nCUSTOMERS\n";
    for (const Customer& customer : customers) {
        cout << "ID: " << customer.id
             << " | Name: " << customer.name
             << " | Contact: " << customer.contactNumber << "\n";
    }
}

void deleteCustomer() {
    viewCustomers();
    if (customers.empty()) {
        return;
    }

    int customerID = getInteger("Enter the customer ID to delete (Q to cancel): ", 1,
                                numeric_limits<int>::max());
    if (customerID == -1) {
        return;
    }

    int customerIndex = findCustomerIndex(customerID);

    if (customerIndex == -1) {
        clearTerminal();
        cout << "Customer not found.\n";
        return;
    }

    // Keep customers with orders so those orders still have a valid customer.
    for (const LaundryOrder& order : orders) {
        if (order.customerID == customerID) {
            clearTerminal();
            cout << "This customer has an order and cannot be deleted.\n";
            return;
        }
    }

    customers.erase(customers.begin() + customerIndex);
    clearTerminal();
    cout << "Customer deleted.\n";
}

void showServices() {
    clearTerminal();
    cout << "\nAVAILABLE SERVICES\n";

    for (int index = 0; index < static_cast<int>(services.size()); index++) {
        cout << index + 1 << ". " << services[index].name
             << " - P" << fixed << setprecision(2)
             << services[index].ratePerKilo << " per kilo\n";
    }
}

void editServiceRates() {
    showServices();

    int serviceChoice = getInteger("Choose the service to edit (Q to cancel): ", 1,
                                   static_cast<int>(services.size()));
    if (serviceChoice == -1) {
        return;
    }

    double newRate = getPositiveNumber("Enter the new price per kilo (Q to cancel): ");
    if (newRate == -1) {
        return;
    }

    services[serviceChoice - 1].ratePerKilo = newRate;

    cout << services[serviceChoice - 1].name
         << " is now P" << fixed << setprecision(2)
         << newRate << " per kilo.\n";
}
void createOrder() {
    if (customers.empty()) {
        clearTerminal();
        cout << "Add a customer before creating an order.\n";
        return;
    }

    viewCustomers();
    int customerID = getInteger("Enter the customer ID for this order (Q to cancel): ", 1,
                                numeric_limits<int>::max());
    if (customerID == -1) {
        return;
    }

    if (findCustomerIndex(customerID) == -1) {
        clearTerminal();
        cout << "Customer not found.\n";
        return;
    }

    showServices();
    int serviceChoice = getInteger("Choose a service (Q to cancel): ", 1,
                                   static_cast<int>(services.size()));
    if (serviceChoice == -1) {
        return;
    }

    double weight = getPositiveNumber("Enter the laundry weight in kilos (Q to cancel): ");
    if (weight == -1) {
        return;
    }

    LaundryOrder order;
    order.customerID = customerID;
    order.serviceName = services[serviceChoice - 1].name;
    order.weight = weight;
    order.totalBill = weight * services[serviceChoice - 1].ratePerKilo;
    order.dateReceived = getRequiredText("Date received (YYYY-MM-DD, Q to cancel): ");
    if (order.dateReceived.empty()) {
        return;
    }

    order.pickupDate = getRequiredText("Pick-up date (YYYY-MM-DD, Q to cancel): ");
    if (order.pickupDate.empty()) {
        return;
    }

    order.status = "Received";

    order.id = nextOrderID;
    orders.push_back(order);
    nextOrderID++;
    clearTerminal();
    cout << "Order created. Order ID: " << order.id
         << " | Total bill: P" << fixed << setprecision(2)
         << order.totalBill << "\n";
}

void displayOrders() {
    clearTerminal();
    if (orders.empty()) {
        cout << "There are no laundry orders.\n";
        return;
    }

    cout << "\nALL LAUNDRY ORDERS\n";
    for (const LaundryOrder& order : orders) {
        int customerIndex = findCustomerIndex(order.customerID);
        string customerName = customers[customerIndex].name;

        cout << "Order ID: " << order.id
             << " | Customer: " << customerName
             << " | Service: " << order.serviceName
             << " | Weight: " << order.weight << " kg"
             << " | Total: P" << fixed << setprecision(2) << order.totalBill
             << " | Received: " << order.dateReceived
             << " | Pick-up: " << order.pickupDate
             << " | Status: " << order.status << "\n";
    }
}

void printReceipt() {
    clearTerminal();
    if (orders.empty()) {
        cout << "There are no laundry orders.\n";
        return;
    }
    displayOrders();
    int orderID = getInteger("Enter the order ID for the receipt (Q to cancel): ", 1,
                             numeric_limits<int>::max());
    if (orderID == -1) {
        return;
    }

    int orderIndex = findOrderIndex(orderID);

    if (orderIndex == -1) {
        clearTerminal();
        cout << "Order not found.\n";
        return;
    }

    const LaundryOrder& order = orders[orderIndex];
    int customerIndex = findCustomerIndex(order.customerID);
    const Customer& customer = customers[customerIndex];

    clearTerminal();
    cout << "\n========== LAUNDRY RECEIPT ==========\n";
    cout << "Order ID: " << order.id << "\n";
    cout << "Customer: " << customer.name << "\n";
    cout << "Contact: " << customer.contactNumber << "\n";
    cout << "Service: " << order.serviceName << "\n";
    cout << "Weight: " << order.weight << " kg\n";
    cout << "Date received: " << order.dateReceived << "\n";
    cout << "Pick-up date: " << order.pickupDate << "\n";
    cout << "Status: " << order.status << "\n";
    cout << "Total bill: P" << fixed << setprecision(2) << order.totalBill << "\n";
    cout << "=====================================\n";
}

void showMainMenu() {
    cout << "\n===== LAUNDRY MANAGEMENT SYSTEM =====\n";
    cout << "1. Add customer\n";
    cout << "2. View customers\n";
    cout << "3. Delete customer\n";
    cout << "4. Create laundry order\n";
    cout << "5. Display all orders\n";
    cout << "6. Print order receipt\n";
    cout << "7. Edit service rates\n";
    cout << "0. Exit\n";
}
