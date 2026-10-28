#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <numeric>
#include <limits>

using namespace std;

void wait_for_enter() { // WAITS FOR THE USER TO PRESS ENTER TO CONTINUE THE PROGRAM
    cout << "Press Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void clearScreen() { // CLEAR TERMINAL
    system("cls");
}

void groceryBudget() { // GROCERY BUDGET TRACKER
    double totalBudget, price;
    int quantity;
    string item;
    vector<string> groceryList;
    vector<double> totalPrice; 
    vector<int> quantityList;
    bool isRunning = true;

    cout << "Please enter your grocery budget: ";
    cin >> totalBudget;

    while (isRunning) {
        clearScreen();
        cout << "Remaining Budget: " << totalBudget << endl;
        cout << "--------------------------" << endl;

        cout << "Enter item (Q to quit): ";
        getline(cin >> ws, item);
        if (item == "q" || item == "Q") {
            clearScreen();
            cout << "----------SUMMARY----------" << endl;
            for (size_t i = 0; i < size(groceryList); i++) {
                cout << quantityList[i] << "x " << groceryList[i] << "\t" << totalPrice[i] << endl;
            }

            cout << "Total:\t" << accumulate(totalPrice.begin(), totalPrice.end(), 0.0);

            break;
        }else {
            cout << "Enter unit price: ";
            cin >> price;
            cout << "Enter quantity: ";
            cin >> quantity;
            price *= quantity;
            if (price > totalBudget) {
                cout << "Item has exceeded the budget!" << endl;
                wait_for_enter();
            }else {
                totalBudget -= price;
                groceryList.push_back(item);
                quantityList.push_back(quantity);
                totalPrice.push_back(price);
            }
            
        }
    }

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