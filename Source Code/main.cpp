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
    
    string response;

    cout << "Welcome to [TITLE]. Please enter the number of the function you wish to use:." << endl;
    cout << "1. Grocery Budget Tracker" << endl;
    cout << "2. Inventory Tracker" << endl;
    do {
        cout << "You: ";
        cin >> response;

        if (response != "1" && response != "2") {
            cout << "Invalid input. Please enter 1 or 2." << endl;
        }
    } while (response != "1" && response != "2");

    if (response == "1") {
        clearScreen();
        groceryBudget();
    } else if (response == "2") {
        clearScreen();
        inventoryTracker();
    }
    return 0;
}   
