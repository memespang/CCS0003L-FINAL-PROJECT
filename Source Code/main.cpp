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

void groceryBudget(vector<string> & Invchoice, vector<float> & Invprice, vector<int> & Invquantity, vector<string> & groceryList, vector<double> & totalPrice, vector<int> & quantityList) { // GROCERY BUDGET TRACKER
    
    double totalBudget;
    int quantity;
    string item;
    bool isRunning = true;
    float price; 

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
            for (size_t i = 0; i < groceryList.size(); i++) {
                cout << quantityList[i] << "x " << groceryList[i] << "\t" << totalPrice[i] << endl;
            }

            cout << "Total:\t" << accumulate(totalPrice.begin(), totalPrice.end(), 0.0) << endl;
            wait_for_enter();

            break;
        } else {
            cout << "Enter unit price: ";
            cin >> price;
            cout << "Enter quantity: ";
            cin >> quantity;
            
            float bulkPrice = price * quantity;

            if (bulkPrice > totalBudget) {
                cout << "Item has exceeded the budget!" << endl;
                wait_for_enter();
            } 

            else {
                totalBudget -= bulkPrice;
                groceryList.push_back(item);
                quantityList.push_back(quantity);
                totalPrice.push_back(bulkPrice);

                Invchoice.push_back(item);
                Invprice.push_back(price); // Saves in inventory tracker
                Invquantity.push_back(quantity);
            }
        }
    }
}

void inventoryTracker(vector<string> & Invchoice, vector<float> & Invprice, vector<int> & Invquantity, vector<string> & groceryList, vector<int> & quantityList) {// INVENTORY TRACKER FUNCTION
    cout << "You selected Inventory Tracker!" << endl;
    string tempInput;
    float tempprice = 0.0f;
    int tempquantity = 0;
    string choice;

    if (Invchoice.empty()) {
        cout << "\nNo products have been added yet." << endl;
    } else {
        cout << "\nHere are the products you have added so far:\n" << endl;
        for (size_t i = 0; i < Invchoice.size(); i++) {
            cout << "Product: " << Invchoice[i] << " | Price: " << Invprice[i] << " peso" << " | Quantity: " << Invquantity[i] << endl;
        }
    }

    cout << "\nWould you like to Add (Y) or Exit (N)? ";
    cin >> choice;

    while (choice == "Y" || choice == "y") {
        cout << "\nEnter product Name: ";
        getline(cin >> ws, tempInput);

        Invchoice.push_back(tempInput);

        cout << "\nPrice: ";
        cin >> tempprice;
        Invprice.push_back(tempprice);



        cout << "\nEnter quantity: ";
        cin >> tempquantity;

        Invquantity.push_back(tempquantity);

        if (Invchoice.size() > 1) {
            for (size_t i = 0; i < Invchoice.size() - 1; i++) {
                if (Invchoice[i] == tempInput) {
                    Invquantity[i] += tempquantity;
                    Invprice[i] = tempprice;
                    Invchoice.pop_back();
                    Invquantity.pop_back();
                    Invprice.pop_back();
                    break;
                }
            }
        }

        for (size_t i = 0; i < groceryList.size(); i++) {
            if (tempInput == groceryList[i]) {
                quantityList[i] += tempquantity; 
                break;
            }
        }

        cout << "\nWould you like to Add (Y) or Exit (N)? ";
        cin >> choice;
    }

    if (choice == "N" || choice == "n") {

        clearScreen();

        cout << "\nHere are the products you have added so far:\n" << endl;
        for (size_t i = 0; i < Invchoice.size(); i++) {
            cout << "Product: " << Invchoice[i] << " | Price: " << Invprice[i] << " peso" << " | Quantity: " << Invquantity[i] << endl;
        }

        wait_for_enter();
    }

    while (choice != "Y" && choice != "y" && choice != "N" && choice != "n") {
        clearScreen();
        cout << "Invalid input. Please enter 'Y' to add or 'N' to exit." << endl;
        cout << "\nWould you like to Add (Y) or Exit (N)? ";
        cin >> choice;
    }
}

int main() { // MENU SCREEN

    vector<string> Invchoice;
    vector<float> Invprice; // Inventory price tracker
    vector<int> Invquantity;

    vector<string> groceryList;
    vector<double> totalPrice; //grocery budget tracker
    vector<int> quantityList;

    string response;

    while (response != "3") {
        clearScreen();
        cout << "Welcome to [TITLE]. Please enter the number of the function you wish to use:" << endl;
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
            groceryBudget(Invchoice, Invprice, Invquantity, groceryList, totalPrice, quantityList);
        } else if (response == "2") {
            clearScreen();
            inventoryTracker(Invchoice, Invprice, Invquantity, groceryList, quantityList);
        } else if (response == "3") {
            clearScreen();
            cout << "Goodbye!" << endl;
            return 0;
        }
    }
}
