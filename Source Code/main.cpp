#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

void groceryBudget() {
    cout << "You selected Grocery Budget Tracker!";
}

void inventoryTracker() {
    cout << "You selected Inventory Tracker!";
}

int main() {
    
    int response;

    cout << "Welcome to [TITLE]. Please select a function." << endl;
    cout << "1. Grocery Budget Tracker" << endl;
    cout << "2. Inventory Tracker" << endl;
    cout << "You: ";
    cin >> response;

    switch (response) {
        case 1:
            groceryBudget();
            break;
        case 2:
            inventoryTracker();
            break;
    }
    return 0;
}
