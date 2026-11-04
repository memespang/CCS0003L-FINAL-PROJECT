#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <numeric>
#include <limits>

using namespace std;

void IDgeneration (vector<int>& ID, int dateDay, int dateMonth, int dateYear) {
    // Generate a unique ID based on the current date and a random number
    srand(time(0)); // Seed for random number generation
    int randomNum = rand() % 10000; // Random number between 0 and 9999
    int newID = (dateYear * 10000) + (dateMonth * 100) + dateDay + randomNum;
    ID.push_back(newID);
    cout << "Your laundry ID is: " << newID << endl;
    
    
    

}

int main() {

    int choiceMenu = 0;
    int choiceC1;//Exit or proceed with washing service
    int choiceC1_1;//Add another service or return to menu
    vector<int> ID;
    //Constants for laundry services
    int dateDay;
    int dateMonth;
    int dateYear;
    int PhoneNum;
    double LaundryQty;
    float weight;
    
    while (choiceMenu != 4) {

        cout << "Please select a service:" << endl;
        cout << "1. Washing" << endl;
        cout << "2. Laundry status" << endl; 
        cout << "3. History (staff Only)" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choiceMenu;

        switch (choiceMenu) {
            case 1:

            system("cls"); // Clear the console screen

            cout << "You selected Washing service." << endl;
            cout << "Would you like to proceed with the washing service? (1 for Yes, 2 for No): ";
            cin >> choiceC1;

            system("cls");

            if (choiceC1 == 1) {
                int choiceC1_1 = 1;
                while (choiceC1_1 == 1) {

                        cout << "Please enter the date (DD MM YYYY): ";
                        cin >> dateDay >> dateMonth >> dateYear;
                        cout << "Please enter quantity of items: ";
                        cin >> LaundryQty;
                        cout << "Measured weight: ";
                        cin >> weight;
                        cout << "Please enter your phone number: ";
                        cin >> PhoneNum;
                        // clear screen
                        system("cls");
                        cout << "Laundry service request submitted successfully!" << endl;
                        IDgeneration(ID, dateDay, dateMonth, dateYear);

                        cout << "Would you like to add another service? (1 for Yes, 2 for No): ";
                        cin >> choiceC1_1;

                        if (choiceC1_1 == 2) {
                            cout << "Returning to main menu." << endl;
                            break;
                        } else if (choiceC1_1 != 1) {
                            cout << "Invalid choice. Returning to main menu." << endl;
                            break;
                        }
                    }
                }

                else if (choiceC1 == 2) {
                    cout << "Cancelling the washing service." << endl;
                    cin.get(); // Wait for user input before clearing the screen
                    
                    system("cls");
                } else {
                    cout << "Invalid choice. Please select a valid option." << endl;
                    cin.get(); // Wait for user input before clearing the screen

                    system("cls");
                }

                system("cls");

                break;

            case 2: {
                cout << "You selected Laundry status service." << endl;
                cout << "Please enter the laundry ID: ";
                int searchID;
                cin >> searchID;

                // Search for the ID in the vector
                bool found = false;
                for (int id : ID) {
                    if (id == searchID) {
                        found = true;
                        break;
                    }
                }

                if (found) {
                    cout << "Laundry item found!" << endl;
                    system("pause"); 
                    break;
                } else {
                    cout << "Laundry item not found." << endl;
                    system("pause"); 
                    break;
                }
                
            }

            case 3:
                cout << "You selected History service." << endl;
                system("cls");
                break;

            case 4:
                cout << "Exiting the program." << endl;
                exit(0);

            default:

                cout << "Invalid choice. Please select a valid service." << endl;
                system("cls");
                break;
        }

    }

}
