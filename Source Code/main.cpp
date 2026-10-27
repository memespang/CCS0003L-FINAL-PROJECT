
#include <iostream>
#include <cstdlib>
#include <limits>

using namespace std;

void clearScreen() { // CLEAR TERMINAL
    system("cls");
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

    while (true) {
        cout << "You: ";

        if (!(cin >> response)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Invalid input! Please enter 1 or 2!" << endl;
            continue;
        }

        if (response != 1 && response != 2) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Please enter 1 or 2!" << endl;
            continue;
        }

        break;
    }

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
