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
    
    char response;

    cout << "Welcome to [TITLE]. Please select a function." << endl;
    cout << "1. Grocery Budget Tracker" << endl;
    cout << "2. Inventory Tracker" << endl;
    cout << "You: ";
    cin >> response;

    do {
        cout << "Invalid input. Please select 1 or 2!" << endl;
        cout << "You: ";
        cin >> response;
    } while (response != '1' && response != '2');

    switch(response) {
        case '1':
            clearScreen();
            groceryBudget();
            break;
        case '2':
            clearScreen();
            inventoryTracker();
    }
    return 0;
}   
