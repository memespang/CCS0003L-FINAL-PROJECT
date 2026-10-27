#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

void clearScreen() { // CLEAR TERMINAL
    cout << "\033[1;1H\033[2J";
}

void groceryBudget() { // GROCERY BUDGET TRACKER
    cout << "You selected Grocery Budget Tracker!";
}

void inventoryTracker() { // INVENTORY TRACKER FUNCTION
    cout << "You selected Inventory Tracker!";
}

int main() { // MENU SCREEN
    
    int response;

    cout << "Welcome to [TITLE]. Please select a function." << endl;
    cout << "1. Grocery Budget Tracker" << endl;
    cout << "2. Inventory Tracker" << endl;
    cout << "You: ";
    cin >> response;

    switch (response) {
        case 1:
            clearScreen();
            groceryBudget();
            break;
        case 2:
            clearScreen();
            inventoryTracker();
            break;
    }
    return 0;
}
