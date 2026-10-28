#include <iostream>
#include <cstdlib>

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
    cout << "3. Quit Program" << endl;
    do {
        cout << "You: ";
        cin >> response;
        if (response != "1" && response != "2" && response != "3") {
            cout << "Invalid input. Please enter a number (1-3)." << endl;
        }
    } while (response != "1" && response != "2" && response != "3");

    if (response == "1") {
        clearScreen();
        groceryBudget();
    } else if (response == "2") {
        clearScreen();
        inventoryTracker();
    } else if (response == "3") {
        clearScreen();
        cout << "Goodbye!" << endl;
    }
    return 0;
}  
